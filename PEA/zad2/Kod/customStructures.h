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
    std::vector<int> path;     // Zapisana ścieżka do tego momentu
    std::vector<bool> visited; // Pamięta, w których miastach już byliśmy
    int level;                 // Głębokość w drzewie (liczba odwiedzonych miast)
    int currentCost;           // Rzeczywisty koszt dotychczasowej trasy
    int lowerBound;            // d
};

