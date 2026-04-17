#pragma once

// Struktura przechowujaca wyniki dzialania algorytmow
struct AlgorithmResult
{
    int cost;
    long long timeMicroseconds;
    int *path;
    int pathSize;
};
// ==========================================
// 1. STRUKTURA WĘZŁA DRZEWA (Node)
// ==========================================
struct Node {
    int N;              // Rozmiar problemu (ilość miast)
    int* path;          // Tablica przechowująca dotychczasową ścieżkę
    bool* visited;      // Tablica bool sprawdzająca, czy miasto było odwiedzone
    int level;          // Aktualny poziom drzewa (ile miast odwiedzono)
    int currentCost;    // Rzeczywisty koszt dotychczasowej trasy
    int lowerBound;     // Obliczone dolne ograniczenie
    
    Node* next;         // Wskaźnik na następny element

    Node(int size);
    ~Node();
    Node* createChild();
};

// ==========================================
// 2. WŁASNY STOS (dla DFS) - LIFO
// ==========================================
class MyStack {
private:
    Node* head = nullptr;

public:
    void push(Node* newNode);
    Node* pop();
    bool isEmpty() const;
    ~MyStack();
};

// ==========================================
// 3. WŁASNA KOLEJKA (dla BFS) - FIFO
// ==========================================
class MyQueue {
private:
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    void push(Node* newNode);
    Node* pop();
    bool isEmpty() const;
    ~MyQueue();
};

// ==========================================
// 4. WŁASNA KOLEJKA PRIORYTETOWA (dla Best-FS)
// ==========================================
class MyPriorityQueue {
private:
    Node* head = nullptr;

public:
    void push(Node* newNode);
    Node* pop();
    bool isEmpty() const;
    ~MyPriorityQueue();
};