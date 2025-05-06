#pragma once
#include "IPriorityQueue.h"

class PriorityQueueList : public IPriorityQueue {
private:
    struct Node {
        int value;
        int priority;
        Node* prev;
        Node* next;
        Node(int v, int p) : value(v), priority(p), prev(nullptr), next(nullptr) {}
    };
    Node* head;

public:
    PriorityQueueList();
    ~PriorityQueueList();

    void insert(int value, int priority) override;
    void remove() override;
    int peek() const override;
    void changePriority(int value, int newPriority) override;
    int size() const override;
    bool isEmpty() const override;
};


