#include "PriorityQueueHeap.h"
#include <stdexcept>

void PriorityQueueHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].priority > heap[parent].priority) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
        else break;
    }
}

void PriorityQueueHeap::heapifyDown(int index) {
    int size = heap.size();
    while (2 * index + 1 < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left].priority > heap[largest].priority) largest = left;
        if (right < size && heap[right].priority > heap[largest].priority) largest = right;

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            index = largest;
        }
        else break;
    }
}

void PriorityQueueHeap::insert(int value, int priority) {
    heap.push_back({ value, priority });
    heapifyUp(heap.size() - 1);
}

void PriorityQueueHeap::remove() {
    if (heap.empty()) throw std::runtime_error("Queue is empty");
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
}

int PriorityQueueHeap::peek() const {
    if (heap.empty()) throw std::runtime_error("Queue is empty");
    return heap[0].value;
}

void PriorityQueueHeap::changePriority(int value, int newPriority) {
    for (int i = 0; i < heap.size(); ++i) {
        if (heap[i].value == value) {
            int oldPriority = heap[i].priority;
            heap[i].priority = newPriority;
            if (newPriority > oldPriority)
                heapifyUp(i);
            else
                heapifyDown(i);
            return;
        }
    }
}

int PriorityQueueHeap::size() const {
    return heap.size();
}

bool PriorityQueueHeap::isEmpty() const {
    return heap.empty();
}
