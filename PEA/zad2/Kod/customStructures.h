#pragma once
#include <vector>
// Struktura przechowujaca wyniki dzialania algorytmow
struct AlgorithmResult
{
    int cost;
    long long timeMicroseconds; // w zadaniu 2 przechowuje czas w milisekundach, nazwa nie zmieniona by nie ruszać elementów wykorzystywanych z zadania 1
    int *path;
    int pathSize;
    bool aborted;
};
// struktura przechowująca wezel drzewa rozwiazan
struct Node {
    std::vector<int> path;     // sciezka do aktualnego momentu
    std::vector<bool> visited; // lista odwiedzonych miast
    int level;                 // poziom drzewa
    int currentCost;           // rzeczywisty koszt ciezki
    int lowerBound;            // wyliczony aktualny LB
};

