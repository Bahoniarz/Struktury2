#include "PriorityQueueList.h"
#include <stdexcept>

PriorityQueueList::PriorityQueueList() : head(nullptr) {}

PriorityQueueList::~PriorityQueueList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void PriorityQueueList::insert(int value, int priority) {
    Node* newNode = new Node(value, priority);
    newNode->next = head;
    if (head) head->prev = newNode;
    head = newNode;
}

void PriorityQueueList::remove() {
    if (!head) throw std::runtime_error("Queue is empty");

    Node* maxNode = head;
    Node* curr = head;

    while (curr) {
        if (curr->priority > maxNode->priority)
            maxNode = curr;
        curr = curr->next;
    }

    if (maxNode->prev) maxNode->prev->next = maxNode->next;
    if (maxNode->next) maxNode->next->prev = maxNode->prev;
    if (maxNode == head) head = head->next;

    delete maxNode;
}

int PriorityQueueList::peek() const {
    if (!head) throw std::runtime_error("Queue is empty");

    Node* maxNode = head;
    Node* curr = head;

    while (curr) {
        if (curr->priority > maxNode->priority)
            maxNode = curr;
        curr = curr->next;
    }
    return maxNode->value;
}

void PriorityQueueList::changePriority(int value, int newPriority) {
    Node* curr = head;
    while (curr) {
        if (curr->value == value) {
            curr->priority = newPriority;
            return;
        }
        curr = curr->next;
    }
}

int PriorityQueueList::size() const {
    int count = 0;
    Node* curr = head;
    while (curr) {
        ++count;
        curr = curr->next;
    }
    return count;
}

bool PriorityQueueList::isEmpty() const {
    return head == nullptr;
}
