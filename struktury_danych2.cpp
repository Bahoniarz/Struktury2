#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <tuple>
#include "PriorityQueueArray.h"
#include "PriorityQueueHeap.h"
#include "PriorityQueueList.h"

using namespace std;
using namespace std::chrono;

const int repeat_count = 10;
const vector<int> sizes_to_test = { 1000,5000,10000,50000,100000 };

struct Result {
    long long insert = 0, peek = 0, change = 0, remove = 0, size = 0;
    int insertOps = 0, peekOps = 0, changeOps = 0, removeOps = 0, sizeOps = 0;
    int finalSize = 0, count = 0;

    void add(long long ins, int insOps, long long p, int pOps, long long ch, int chOps,
        long long rem, int remOps, long long sz, int szOps, int fsz) {
        insert += ins; insertOps += insOps;
        peek += p; peekOps += pOps;
        change += ch; changeOps += chOps;
        remove += rem; removeOps += remOps;
        size += sz; sizeOps += szOps;
        finalSize += fsz; count++;
    }

    void average() {
        if (insertOps) insert /= insertOps;
        if (peekOps) peek /= peekOps;
        if (changeOps) change /= changeOps;
        if (removeOps) remove /= removeOps;
        if (sizeOps) size /= sizeOps;
        if (count) finalSize /= count;
    }
};

static random_device rd;
static mt19937 gen(rd());

void prepareRandomData(vector<pair<int, int>>& data, int size) {
    uniform_int_distribution<> val_dist(1, 1000000), prio_dist(1, 1000);
    data.clear();
    for (int i = 0; i < size; i++)
        data.emplace_back(val_dist(gen), prio_dist(gen));
}

void benchmark(const string& queueName, int size, map<pair<string, int>, Result>& resMap) {
    uniform_int_distribution<> val_dist(1, 1000000), prio_dist(1, 1000);

    for (int r = 0; r < repeat_count; r++) {
        IPriorityQueue* queue;
        if (queueName == "ArrayQueue") queue = new PriorityQueueArray();
        else if (queueName == "HeapQueue") queue = new PriorityQueueHeap();
        else queue = new PriorityQueueList();

        vector<pair<int, int>> data;
        prepareRandomData(data, size);

        vector<int> vals;
        for (auto& d : data) vals.push_back(d.first);

        auto t1 = steady_clock::now();
        for (auto& p : data) queue->insert(p.first, p.second);
        auto t2 = steady_clock::now();

        int ops_count = max(1000, size / 2);

        auto t3 = steady_clock::now();
        for (int i = 0; i < ops_count; i++) if (!queue->isEmpty()) queue->peek();
        auto t4 = steady_clock::now();

        uniform_int_distribution<> id(0, vals.size() - 1);

        auto t5 = steady_clock::now();
        for (int i = 0; i < ops_count; i++)
            queue->changePriority(vals[id(gen)], prio_dist(gen));
        auto t6 = steady_clock::now();

        auto t7 = steady_clock::now();
        for (int i = 0; i < size / 4; i++) if (!queue->isEmpty()) queue->remove();
        auto t8 = steady_clock::now();

        auto t9 = steady_clock::now();
        int fsz = queue->size();
        auto t10 = steady_clock::now();

        delete queue;

        resMap[make_pair(queueName, size)].add(
            duration_cast<nanoseconds>(t2 - t1).count(), size,
            duration_cast<nanoseconds>(t4 - t3).count(), ops_count,
            duration_cast<nanoseconds>(t6 - t5).count(), ops_count,
            duration_cast<nanoseconds>(t8 - t7).count(), size / 4,
            duration_cast<nanoseconds>(t10 - t9).count(), 1,
            fsz
        );
    }
}

int main() {
    map<pair<string, int>, Result> results;

    for (int size : sizes_to_test) {
        benchmark("ArrayQueue", size, results);
        benchmark("HeapQueue", size, results);
        benchmark("ListQueue", size, results);
    }

    ofstream csv("benchmark_summary.csv");
    csv << "Queue,Size,InsertPerNs,PeekPerNs,ChangePerNs,RemovePerNs,SizeCheckNs,FinalSize\n";

    for (map<pair<string, int>, Result>::iterator it = results.begin(); it != results.end(); ++it) {
        const pair<string, int>& key = it->first;
        Result& r = it->second;
        r.average();

        csv << key.first << "," << key.second << ","
            << r.insert << "," << r.peek << "," << r.change << ","
            << r.remove << "," << r.size << "," << r.finalSize << "\n";
    }

    csv.close();
    cout << "Wyniki zapisane do benchmark_summary.csv\n";
    return 0;
}
