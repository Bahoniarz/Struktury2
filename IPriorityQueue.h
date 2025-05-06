#pragma once

class IPriorityQueue {
public:
    virtual void insert(int value, int priority) = 0;
    virtual void remove() = 0;
    virtual int peek() const = 0;
    virtual void changePriority(int value, int newPriority) = 0;
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual ~IPriorityQueue() {}
};


