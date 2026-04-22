#include "graph.h"
#include "customStructures.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <queue>
#include <vector>
#include <climits> // dla INT_MAX

Graph::Graph(int cities){
    N = cities;

    matrix = new int *[N];
    for (int i = 0; i < N; ++i){
        matrix[i] = new int[N];
    }
}

Graph::~Graph(){
    // Usuniecie kazdej kolumny tablicy
    for (int i = 0; i < N; ++i){
        delete[] matrix[i];
    }
    // Usuniecie tablicy
    delete[] matrix;
}

void Graph::setEdge(int from, int to, int weight){
    matrix[from][to] = weight;
}

int Graph::getEdge(int from, int to) const{
    return matrix[from][to];
}

void Graph::getGraphfromFile(const std::string &filename){
    int newN;
    std::ifstream file(filename);
    if (!file.is_open()){
        std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
        return;
    }
    if (matrix != nullptr){
        for (int i = 0; i < N; ++i){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    file >> newN;
    N = newN;
    matrix = new int *[N];
    for (int i = 0; i < N; ++i){
        matrix[i] = new int[N];
    }
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            file >> matrix[i][j];
        }
    }
}

void Graph::generateRandomGraph(int cities, int minWeight, int maxWeight){
    // Generacja liczb losowych uzywajac rozkladu jednostajnie ciaglego
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minWeight, maxWeight);

    // Jesli macierz istnieje, usuniecie
    if (matrix != nullptr){
        for (int i = 0; i < N; ++i){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    // Stworzenie nowej macierzy
    N = cities;
    matrix = new int *[N];
    for (int i = 0; i < N; ++i){
        matrix[i] = new int[N];
    }
    // Wypelnienie macierzy losowymi wagami z zakresu <minWeight;maxWeight>
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (i == j){
                matrix[i][j] = -1;
            }
            else{
                matrix[i][j] = dist(gen);
            }
        }
    }
}

void Graph::printGraph(){
    std::cout << "Graf o rozmiarze " << N << ":" << std::endl;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            std::cout << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}
int Graph::getN() const{
    return N;
}

// Zamiana elementow (implementacja std::swap)
void Graph::swapElements(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

// Odwrocenie tablicy (implementacja std::reverse)
void Graph::reverseArray(int *arr, int start, int end){
    while (start < end)
    {
        swapElements(arr[start], arr[end]);
        start++;
        end--;
    }
}
// Generowanie następnej permutacji (implementacja std::next_permutation)
bool Graph::generateNextPermutation(int *arr, int size){
    int i = size - 2;
    // Szukamy pierwszego elementu od końca, który jest mniejszy od swojego prawego sąsiada
    while (i >= 0 && arr[i] >= arr[i + 1]){
        i--;
    }
    // Jeśli nie znaleziono, to znaczy, że sprawdziliśmy wszystkie permutacje
    if (i < 0){
        return false;
    }
    int j = size - 1;
    // Szukamy elementu większego od wczesniej zanlezionego po jego prawej stronie (idąc od końca)
    while (arr[j] <= arr[i]){
        j--;
    }
    // Zamieniamy je miejscami
    swapElements(arr[i], arr[j]);
    // Odwracamy wszystko na prawo od i
    reverseArray(arr, i + 1, size - 1);
    return true;
}
void Graph::shuffleArray(int *arr, int size){
    for (int i = size - 1; i > 0; --i){
        // Losujemy indeks j z zakresu od 0 do i
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(gen);
        // Ręczny swap
        swapElements(arr[i], arr[j]);
    }
}
// Funkcja rekurencyjna obslugujaca remisow w algorytmie NN
void Graph::exploreNN(const Graph &g, int currentNode, int startNode, bool *visited, int *currentPath, int step, int currentCost, int &bestCost, int *bestPath){
    int N = g.getN();
    // Warunek koncowy: kazde miasto odwiedzone
    if (step == N){
        int returnCost = g.getEdge(currentNode, startNode);
        if (returnCost != -1){
            int totalCost = currentCost + returnCost;

            // Aktualizacja najlepszego globalnego rozwiązania
            if (totalCost < bestCost){
                bestCost = totalCost;
                for (int i = 0; i < N; ++i){
                    bestPath[i] = currentPath[i];
                }
                // zamknięcie cyklu
                bestPath[N] = startNode;
            }
        }
        return;
    }
    int minWeight = INF;
    // KROK 1: Szukamy najmniejszej wagi wśród nieodwiedzonych sasiadow
    for (int i = 0; i < N; ++i){
        if (!visited[i]){
            int weight = g.getEdge(currentNode, i);
            if (weight != -1 && weight < minWeight){
                minWeight = weight;
            }
        }
    }
    if (minWeight == INF)
        return;

    // KROK 2: Wchodzimy we wszystkie sciezki o najmniejszej wadze
    for (int i = 0; i < N; ++i){
        if (!visited[i]){
            int weight = g.getEdge(currentNode, i);
            // Jesli trafiamy na miasto z minimalną wagą
            if (weight == minWeight){
                // Oznaczamy miasto jako odwiedzone na potrzeby danej gałęzi
                visited[i] = true;
                currentPath[step] = i;
                // Rekurencyjne przejscie do kolejnego kroku
                exploreNN(g, i, startNode, visited, currentPath, step + 1, currentCost + minWeight, bestCost, bestPath);
                // Backtracking: cofniecie odwiedzenia miasta, aby sprawdzic inne galezie o tej samej wadze
                visited[i] = false;
            }
        }
    }
}
// Funkcja startowa dla NN z remisami
AlgorithmResult Graph::runNN(const Graph &g, int startNode){
    int N = g.getN();
    bool *visited = new bool[N];
    int *currentPath = new int[N + 1];
    int *bestPath = new int[N + 1];
    // Wszystkie miasta jako nieodwiedzone
    for (int i = 0; i < N; ++i){
        visited[i] = false;
    }
    int bestCost = INF;

    auto startTime = std::chrono::high_resolution_clock::now();

    // Inicjalizacja stanu dla punktu startowego
    visited[startNode] = true;
    currentPath[0] = startNode;

    // Uruchomienie rekurencjej eksploracji NN
    exploreNN(g, startNode, startNode, visited, currentPath, 1, 0, bestCost, bestPath);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // Zwalnianie pamięci
    delete[] visited;
    delete[] currentPath;
    // Zwrot struktury wyników
    return {bestCost, duration, bestPath, N + 1, false};
}

// --------------------------------------------------------------------------------------
//                                  kod zadania 2
// --------------------------------------------------------------------------------------
// wyliczenie dolnego ograniczenia 
int Graph::calculateBound(const Node& node, const Graph& g) {
    int bound = node.currentCost;
    // Dla każdego miasta, w którym JESZCZE NIE BYLIŚMY,
    // znajdujemy najtańszą wychodzącą krawędź i dodajemy do bound.
    for (int i = 0; i < N; ++i) {
        if (!node.visited[i]) {
            int minEdge = INT_MAX;
            for (int j = 0; j < N; ++j) {
                if (i != j && g.getEdge(i, j) != -1 && g.getEdge(i, j) < minEdge) {
                    minEdge = g.getEdge(i, j);
                }
            }
            if (minEdge != INT_MAX) {
                bound += minEdge;
            }
        }
    }
    return bound;
}


AlgorithmResult Graph::runBnB_BFS(const Graph &g) {
    int N = g.getN();
    bool aborted = false;
    // --- 1. Upper Bound z NN ---
    AlgorithmResult nnResult = runNN(g, 0);
    int upperBound = nnResult.cost;

    std::vector<int> bestFinalPath;
    if (nnResult.path != nullptr && nnResult.pathSize > 0) {
        bestFinalPath.assign(nnResult.path, nnResult.path + nnResult.pathSize);
    }
    delete[] nnResult.path;

    // --- 2. Kolejka BFS ---
    std::queue<Node> q;

    // --- 3. Root ---
    Node root;
    root.level = 1;
    root.path = {0};
    root.visited.assign(N, false);
    root.visited[0] = true;
    root.currentCost = 0;
    root.lowerBound = calculateBound(root, g);

    q.push(root);

    // --- DEBUG (polecam zostawić na czas testów) ---
    // std::cout << "Root LB: " << root.lowerBound << " UB: " << upperBound << std::endl;

    // --- 4. Timer ---
    auto startTime = std::chrono::high_resolution_clock::now();

    // --- 5. BFS ---
    while (!q.empty()) {

        // timeout
        auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count() >= 300) {
            aborted = true;
            break;
        }

        Node current = q.front();
        q.pop();

        // --- PRUNING ---
        if (current.lowerBound > upperBound) {
            continue;
        }

        int currentCity = current.path.back();

        // --- LIŚĆ ---
        if (current.level == N) {
            int returnCost = g.getEdge(currentCity, 0);

            if (returnCost != -1) {
                int totalCost = current.currentCost + returnCost;

                if (totalCost < upperBound) {
                    upperBound = totalCost;
                    bestFinalPath = current.path;
                    bestFinalPath.push_back(0);
                }
            }
            continue;
        }

        // --- GENEROWANIE DZIECI ---
        for (int nextCity = 0; nextCity < N; ++nextCity) {

            if (!current.visited[nextCity]) {

                int edgeCost = g.getEdge(currentCity, nextCity);
                if (edgeCost == -1) continue;

                Node child = current;

                child.path.push_back(nextCity);
                child.visited[nextCity] = true;
                child.level++;
                child.currentCost += edgeCost;

                child.lowerBound = calculateBound(child, g);

                // pruning dziecka
                if (child.lowerBound <= upperBound) {
                    q.push(child);
                }
            }
        }
    }

    // --- 6. wynik ---
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    int *resultPath = nullptr;
    int pathSize = 0;

    if (!bestFinalPath.empty()) {
        pathSize = bestFinalPath.size();
        resultPath = new int[pathSize];
        for (int i = 0; i < pathSize; ++i) {
            resultPath[i] = bestFinalPath[i];
        }
    }

    return {upperBound, duration, resultPath, pathSize, aborted};
}
struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        return a.lowerBound > b.lowerBound; // min-heap
    }
};

AlgorithmResult Graph::runBnB_BestFS(const Graph& g) {
    int N = g.getN();
    bool aborted = false;
    // --- 1. Upper Bound z NN ---
    AlgorithmResult nnResult = runNN(g, 0);
    int upperBound = nnResult.cost;

    std::vector<int> bestFinalPath;
    if (nnResult.path != nullptr && nnResult.pathSize > 0) {
        bestFinalPath.assign(nnResult.path, nnResult.path + nnResult.pathSize);
    }
    delete[] nnResult.path;

    // --- 2. Kolejka priorytetowa ---
    std::priority_queue<Node, std::vector<Node>, CompareNode> pq;

    // --- 3. Root ---
    Node root;
    root.level = 1;
    root.path = {0};
    root.visited.assign(N, false);
    root.visited[0] = true;
    root.currentCost = 0;
    root.lowerBound = calculateBound(root, g);

    pq.push(root);

    // --- DEBUG ---
    // std::cout << "Root LB: " << root.lowerBound << " UB: " << upperBound << std::endl;

    // --- 4. Timer ---
    auto startTime = std::chrono::high_resolution_clock::now();

    // --- 5. BestFS ---
    while (!pq.empty()) {

        // timeout
        auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count() >= 300) {
            aborted=true;
            break;
        }

        // --- NAJLEPSZY WĘZEŁ ---
        Node current = pq.top();
        pq.pop();

        // 🔴 KLUCZOWA OPTYMALIZACJA:
        // jeśli najlepszy dostępny LB ≥ UB → koniec (optymalne rozwiązanie znalezione)
        if (current.lowerBound >= upperBound) {
            break;
        }

        int currentCity = current.path.back();

        // --- LIŚĆ ---
        if (current.level == N) {
            int returnCost = g.getEdge(currentCity, 0);

            if (returnCost != -1) {
                int totalCost = current.currentCost + returnCost;

                if (totalCost < upperBound) {
                    upperBound = totalCost;
                    bestFinalPath = current.path;
                    bestFinalPath.push_back(0);
                }
            }
            continue;
        }

        // --- GENEROWANIE DZIECI ---
        for (int nextCity = 0; nextCity < N; ++nextCity) {

            if (!current.visited[nextCity]) {

                int edgeCost = g.getEdge(currentCity, nextCity);
                if (edgeCost == -1) continue;

                Node child = current;

                child.path.push_back(nextCity);
                child.visited[nextCity] = true;
                child.level++;
                child.currentCost += edgeCost;

                child.lowerBound = calculateBound(child, g);

                // pruning dziecka
                if (child.lowerBound <= upperBound) {
                    pq.push(child);
                }
            }
        }
    }

    // --- 6. wynik ---
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    int *resultPath = nullptr;
    int pathSize = 0;

    if (!bestFinalPath.empty()) {
        pathSize = bestFinalPath.size();
        resultPath = new int[pathSize];
        for (int i = 0; i < pathSize; ++i) {
            resultPath[i] = bestFinalPath[i];
        }
    }

    return {upperBound, duration, resultPath, pathSize, aborted};
}