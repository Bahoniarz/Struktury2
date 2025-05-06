#include "PriorityQueueArray.h"
#include <stdexcept>
#include <algorithm>

void PriorityQueueArray::insert(int value, int priority) {
    data.push_back({ value, priority });
}

void PriorityQueueArray::remove() {
    if (data.empty()) throw std::runtime_error("Queue is empty");
    auto it = std::max_element(data.begin(), data.end(), [](auto& a, auto& b) {
        return a.priority < b.priority;
        });
    data.erase(it);
}

int PriorityQueueArray::peek() const {
    if (data.empty()) throw std::runtime_error("Queue is empty");
    return std::max_element(data.begin(), data.end(), [](auto& a, auto& b) {
        return a.priority < b.priority;
        })->value;
}

void PriorityQueueArray::changePriority(int value, int newPriority) {
    for (auto& node : data) {
        if (node.value == value) {
            node.priority = newPriority;
            return;
        }
    }
}

int PriorityQueueArray::size() const {
    return data.size();
}

bool PriorityQueueArray::isEmpty() const {
    return data.empty();
}

