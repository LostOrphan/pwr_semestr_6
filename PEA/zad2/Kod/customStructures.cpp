#include "CustomStructures.h"

Node::Node(int size) {
    N = size;
    path = new int[N + 1];
    visited = new bool[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
        path[i] = -1;
    }
    path[N] = -1;
    level = 0;
    currentCost = 0;
    lowerBound = 0;
    next = nullptr;
}

Node::~Node() {
    delete[] path;
    delete[] visited;
}

Node* Node::createChild() {
    Node* child = new Node(N);
    child->level = this->level;
    child->currentCost = this->currentCost;
    child->lowerBound = this->lowerBound;
    for (int i = 0; i < N; ++i) {
        child->path[i] = this->path[i];
        child->visited[i] = this->visited[i];
    }
    child->path[N] = this->path[N];
    return child;
}


void MyStack::push(Node* newNode) {
    newNode->next = head;
    head = newNode;
}

Node* MyStack::pop() {
    if (!head) return nullptr;
    Node* temp = head;
    head = head->next;
    temp->next = nullptr;
    return temp;
}

bool MyStack::isEmpty() const {
    return head == nullptr;
}

MyStack::~MyStack() {
    while (!isEmpty()) {
        delete pop();
    }
}

void MyQueue::push(Node* newNode) {
    newNode->next = nullptr;
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

Node* MyQueue::pop() {
    if (!head) return nullptr;
    Node* temp = head;
    head = head->next;
    if (!head) tail = nullptr; 
    temp->next = nullptr;
    return temp;
}

bool MyQueue::isEmpty() const {
    return head == nullptr;
}

MyQueue::~MyQueue() {
    while (!isEmpty()) {
        delete pop();
    }
}

// ==========================================
// METODY KLASY: MyPriorityQueue
// ==========================================
void MyPriorityQueue::push(Node* newNode) {
    newNode->next = nullptr;

    if (!head || newNode->lowerBound < head->lowerBound) {
        newNode->next = head;
        head = newNode;
    } 
    else {
        Node* current = head;
        while (current->next && current->next->lowerBound <= newNode->lowerBound) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

Node* MyPriorityQueue::pop() {
    if (!head) return nullptr;
    Node* temp = head;
    head = head->next;
    temp->next = nullptr;
    return temp;
}

bool MyPriorityQueue::isEmpty() const {
    return head == nullptr;
}

MyPriorityQueue::~MyPriorityQueue() {
    while (!isEmpty()) {
        delete pop();
    }
}