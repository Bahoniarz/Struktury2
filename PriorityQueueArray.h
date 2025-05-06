#pragma once
#include "IPriorityQueue.h"
#include <vector>

class PriorityQueueArray : public IPriorityQueue {
private:
    struct Node {
        int value;
        int priority;
    };
    std::vector<Node> data;

public:
    void insert(int value, int priority) override;
    void remove() override;
    int peek() const override;
    void changePriority(int value, int newPriority) override;
    int size() const override;
    bool isEmpty() const override;
};
