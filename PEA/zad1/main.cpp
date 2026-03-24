#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
const int INF = 2147483647; 
class Graph {
private:
    int** matrix = nullptr;
    int N;
// Zmienne globalne do zapamiętania globalnie najlepszego wyniku
int globalMinCostRNN = INF;
int* globalBestPathRNN = nullptr;
int globalStartNode = -1; 
public:
    Graph(int cities);
    ~Graph();
    
    void setEdge(int from, int to, int weight);
    int getEdge(int from, int to) const;
    void getGraphfromFile(const std::string& filename);
    void generateRandomGraph(int cities, int minWeight, int maxWeight);
    void printGraph();
    void swapElements(int& a, int& b);
    void reverseArray(int* arr, int start, int end);
    bool generateNextPermutation(int* arr, int size);
    void runBruteForce(const Graph& g, int startNode = 0);
    int getN() const;
    void exploreTieBreakingNN(const Graph& g, int currentNode, int startNode, bool* visited, 
                          int* currentPath, int step, int currentCost, 
                          int& bestCost, int* bestPath);
    void runTieBreakingNN(const Graph& g, int startNode = 0);
    void runRepetitiveNearestNeighbour(const Graph& g);
    void exploreRNNBranches(const Graph& g, int currentNode, bool* visited, int* currentPath, int step, int currentCost);
    void shuffleArray(int* arr, int size);
    void runRandomAlgorithm(const Graph& g, int K);

};

Graph::Graph(int cities) {
    N = cities;

    matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }
}

Graph::~Graph() {
    // usuniecie kazdej kolumny tablicy
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    //usuniecie tablicy
    delete[] matrix;
}

void Graph::setEdge(int from, int to, int weight) {
    matrix[from][to] = weight;
}

int Graph::getEdge(int from, int to) const {
    return matrix[from][to];
}

void Graph::getGraphfromFile(const std::string& filename) {

    int newN;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        return;
    }
    if (matrix != nullptr) {
        for (int i = 0; i < N; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    file >> newN;
    N = newN;
    matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> matrix[i][j];
        }
    }
}

void Graph::generateRandomGraph(int cities, int minWeight, int maxWeight) {
    //generacja liczb losowych
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minWeight, maxWeight);

    //jesli macierz istnieje, usuniecie
    if (matrix != nullptr) {
        for (int i = 0; i < N; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    //stworzenie nowej macierzy
    N = cities;
    matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }
    //wypelnienie macierzy losowymi wagami z zakresu minWeight-maxWeight
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) {
                matrix[i][j] = -1;
            } else {
                matrix[i][j] = dist(gen);
            }
        }
    }
}

void Graph::printGraph() {
    std::cout << "Graf o rozmiarze " << N << ":" << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}
int Graph::getN() const {
        return N;
    }

//zamiana elementow (odpowiednik std::swap)
void Graph::swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

//odwrocenie tablicy (odpowiednik std::reverse)
void Graph::reverseArray(int* arr, int start, int end) {
    while (start < end) {
        swapElements(arr[start], arr[end]);
        start++;
        end--;
    }
    }
    //generowanie
    bool Graph::generateNextPermutation(int* arr, int size) {
    int i = size - 2;
    // Szukamy pierwszego elementu od końca, który jest mniejszy od swojego prawego sąsiada
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    // Jeśli nie znaleziono, to znaczy, że sprawdziliśmy wszystkie permutacje
    if (i < 0) {
        return false;
    }

    int j = size - 1;
    // Szukamy elementu większego od arr[i] po jego prawej stronie (idąc od końca)
    while (arr[j] <= arr[i]) {
        j--;
    }

    // Zamieniamy je miejscami
    swapElements(arr[i], arr[j]);

    // Odwracamy wszystko na prawo od i
    reverseArray(arr, i + 1, size - 1);

    return true;
}
void Graph::shuffleArray(int* arr, int size) {
    for (int i = size - 1; i > 0; --i) {
        // Losujemy indeks j z zakresu od 0 do i
        // int j = rand() % (i + 1);
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(gen);
        
        // Ręczny swap
        swapElements(arr[i],arr[j]);
        // int temp = arr[i];
        // arr[i] = arr[j];
        // arr[j] = temp;
    }
}
// Główna funkcja algorytmu Brute-Force
void Graph::runBruteForce(const Graph& g, int startNode) {
    int N = g.getN();
    
    // Dynamiczna alokacja tablicy na wierzchołki, które będziemy permutować (bez startNode)
    int* verticesToVisit = new int[N - 1];
    int idx = 0;
    for (int i = 0; i < N; ++i) {
        if (i != startNode) {
            verticesToVisit[idx] = i;
            idx++;
        }
    }

    int minCost = INF;
    // Dynamiczna alokacja tablicy do zapamiętania najlepszej ścieżki
    int* bestPath = new int[N + 1]; 

    // Rozpoczęcie pomiaru czasu
    auto startTime = std::chrono::high_resolution_clock::now();

    // Główna pętla sprawdzająca każdą permutację (zastępuje rekurencję)
    do {
        int currentPathCost = 0;
        int currentNode = startNode;

        // Sumowanie kosztów dla aktualnej permutacji
        // UWAGA: Zgodnie z wytycznymi, nie przerywamy tej pętli wcześnie! (Brak Branch & Bound)
        for (int i = 0; i < N - 1; ++i) {
            int nextNode = verticesToVisit[i];
            currentPathCost += g.getEdge(currentNode, nextNode);
            currentNode = nextNode;
        }
        
        // Dodanie kosztu powrotu do miasta startowego (cykl)
        currentPathCost += g.getEdge(currentNode, startNode);   

        // Aktualizacja najlepszego rozwiązania
        if (currentPathCost < minCost) {
            minCost = currentPathCost;
            bestPath[0] = startNode;
            for (int i = 0; i < N - 1; ++i) {
                bestPath[i + 1] = verticesToVisit[i];
            }
            bestPath[N] = startNode; // zamknięcie cyklu do wypisania
        }

    } while (generateNextPermutation(verticesToVisit, N - 1));

    // Zakończenie pomiaru czasu
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    // Wypisanie wyników [cite: 50]
    std::cout << "--- Wyniki Brute-Force ---\n";
    std::cout << "Minimalny koszt: " << minCost << "\n";
    std::cout << "Najlepsza sciezka: ";
    for (int i = 0; i <= N; ++i) {
        std::cout << bestPath[i];
        if (i < N) std::cout << " -> ";
    }
    std::cout << "\nCzas wykonania: " << duration << " mikrosekund\n";

    // Zwolnienie pamięci 
    delete[] verticesToVisit;
    delete[] bestPath;
}
// Funkcja rekurencyjna obsługująca rozgałęzienia w przypadku remisów
void Graph::exploreTieBreakingNN(const Graph& g, int currentNode, int startNode, bool* visited, 
                          int* currentPath, int step, int currentCost, 
                          int& bestCost, int* bestPath) {
    int N = g.getN();

    // Warunek końcowy: wszystkie miasta zostały odwiedzone
    if (step == N) {
        int returnCost = g.getEdge(currentNode, startNode);
        if (returnCost != -1) {
            int totalCost = currentCost + returnCost;
            
            // Aktualizacja najlepszego globalnego rozwiązania
            if (totalCost < bestCost) {
                bestCost = totalCost;
                for (int i = 0; i < N; ++i) {
                    bestPath[i] = currentPath[i];
                }
                bestPath[N] = startNode; // zamknięcie cyklu
            }
        }
        return;
    }

    int minWeight = INF;

    // KROK 1: Szukamy najmniejszej wagi wśród NIEODWIEDZONYCH sąsiadów
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            int weight = g.getEdge(currentNode, i);
            if (weight != -1 && weight < minWeight) {
                minWeight = weight;
            }
        }
    }

    // Jeśli nie ma drogi do żadnego nieodwiedzonego miasta (ślepa uliczka), przerywamy
    if (minWeight == INF) return;

    // KROK 2: Rozgałęzienie - wchodzimy we WSZYSTKIE ścieżki o wadze równej minWeight
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            int weight = g.getEdge(currentNode, i);
            
            // Jeśli trafiamy na miasto z minimalną wagą (może być ich kilka!)
            if (weight == minWeight) {
                // Oznaczamy miasto jako odwiedzone na potrzeby tej gałęzi
                visited[i] = true;
                currentPath[step] = i;

                // Rekurencyjne przejście do kolejnego kroku
                exploreTieBreakingNN(g, i, startNode, visited, currentPath, step + 1, currentCost + minWeight, bestCost, bestPath);

                // BACKTRACKING: Odznaczamy miasto, aby sąsiednie gałęzie rekurencji mogły sprawdzić inne warianty
                visited[i] = false;
            }
        }
    }
}

// Funkcja startowa dla NN z remisami
void Graph::runTieBreakingNN(const Graph& g, int startNode) {
    int N = g.getN();
    
    // Dynamiczna alokacja pamięci
    bool* visited = new bool[N];
    int* currentPath = new int[N + 1];
    int* bestPath = new int[N + 1];
    
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
    }

    int bestCost = INF;

    auto startTime = std::chrono::high_resolution_clock::now();

    // Inicjalizacja stanu dla punktu startowego
    visited[startNode] = true;
    currentPath[0] = startNode;

    // Uruchomienie rekurencji obsługującej zachłanne przejścia z remisami
    exploreTieBreakingNN(g, startNode, startNode, visited, currentPath, 1, 0, bestCost, bestPath);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    // Wyświetlenie wyników
    std::cout << "--- Wyniki Tie-Breaking Nearest Neighbour ---\n";
    std::cout << "Miasto startowe: " << startNode << "\n";
    if (bestCost == INF) {
        std::cout << "Nie znaleziono zamknietego cyklu!\n";
    } else {
        std::cout << "Minimalny koszt: " << bestCost << "\n";
        std::cout << "Najlepsza sciezka: ";
        for (int i = 0; i <= N; ++i) {
            std::cout << bestPath[i];
            if (i < N) std::cout << " -> ";
        }
        std::cout << "\n";
    }
    std::cout << "Czas wykonania: " << duration << " mikrosekund\n";

    // Zwalnianie pamięci
    delete[] visited;
    delete[] currentPath;
    delete[] bestPath;
}


// Rekurencyjna funkcja eksplorująca rozgałęzienia (remisy) - realizacja wymogu z instrukcji
void Graph::exploreRNNBranches(const Graph& g, int currentNode, bool* visited, int* currentPath, int step, int currentCost) {
    int N = g.getN();

    // Warunek końcowy: odwiedziliśmy wszystkie miasta, zamykamy cykl
    if (step == N) {
        int returnCost = g.getEdge(currentNode, globalStartNode);
        if (returnCost != -1) {
            int totalCost = currentCost + returnCost;
            
            // Jeśli znaleziona ścieżka jest lepsza od dotychczasowej, aktualizujemy
            if (totalCost < globalMinCostRNN) {
                globalMinCostRNN = totalCost;
                for (int i = 0; i < N; ++i) {
                    globalBestPathRNN[i] = currentPath[i];
                }
                globalBestPathRNN[N] = globalStartNode; 
            }
        }
        return;
    }

    int minWeight = INF;

    // Faza 1: Znalezienie minimalnej wagi krawędzi wśród nieodwiedzonych sąsiadów
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            int weight = g.getEdge(currentNode, i);
            if (weight != -1 && weight < minWeight) {
                minWeight = weight;
            }
        }
    }

    // Jeśli brak drogi (ślepy zaułek), przerywamy tę gałąź
    if (minWeight == INF) return;

    // Faza 2: Rozgałęzienie - sprawdzamy KAŻDĄ krawędź o najmniejszej wadze (obsługa remisów)
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            int weight = g.getEdge(currentNode, i);
            
            // Sprawdzamy wszystkie możliwości wyboru dla minimalnej wagi
            if (weight == minWeight) {
                // Zapamiętanie węzła i pójście w wybraną ścieżkę
                visited[i] = true;
                currentPath[step] = i;

                exploreRNNBranches(g, i, visited, currentPath, step + 1, currentCost + minWeight);

                // Backtracking: cofamy się, aby sprawdzić inne krawędzie o tej samej wadze
                visited[i] = false;
            }
        }
    }
}

// Główna funkcja wywołująca algorytm RNN
void Graph::runRepetitiveNearestNeighbour(const Graph& g) {
    int N = g.getN();
    
    // Dynamiczna alokacja struktur pomocniczych
    bool* visited = new bool[N];
    int* currentPath = new int[N + 1];
    
    if (globalBestPathRNN != nullptr) {
        delete[] globalBestPathRNN;
    }
    globalBestPathRNN = new int[N + 1];
    globalMinCostRNN = INF;

    auto startTime = std::chrono::high_resolution_clock::now();

    // Algorytm Repetitive - powtarzamy poszukiwania startując z każdego możliwego miasta
    for (int startNode = 0; startNode < N; ++startNode) {
        
        // Resetowanie tablicy odwiedzin dla nowego punktu startowego
        for (int i = 0; i < N; ++i) {
            visited[i] = false;
        }

        globalStartNode = startNode;
        visited[startNode] = true;
        currentPath[0] = startNode;

        // Uruchomienie poszukiwań z uwzględnieniem remisów
        exploreRNNBranches(g, startNode, visited, currentPath, 1, 0);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    // Wyświetlenie wyników zgodnie z wymaganiami
    std::cout << "--- Wyniki RNN ---\n";
    if (globalMinCostRNN == INF) {
        std::cout << "Nie znaleziono zamknietego cyklu!\n";
    } else {
        std::cout << "Dlugosc sciezki: " << globalMinCostRNN << "\n";
        std::cout << "Ciag wierzcholkow: ";
        for (int i = 0; i <= N; ++i) {
            std::cout << globalBestPathRNN[i];
            if (i < N) std::cout << " -> ";
        }
        std::cout << "\n";
    }
    std::cout << "Czas wykonania: " << duration << " mikrosekund\n";

    // Zwolnienie pamięci
    delete[] visited;
    delete[] currentPath;
}
// Główna funkcja algorytmu losowego przyjmująca parametr K (ilość permutacji)
void Graph::runRandomAlgorithm(const Graph& g, int K) {
    int N = g.getN();
    
    // Dynamiczna alokacja pamięci [cite: 6]
    int* currentPath = new int[N];
    int* bestPath = new int[N + 1];
    int minCost = INF;

    // Inicjalizacja tablicy początkowej (np. 0, 1, 2, ..., N-1)
    for (int i = 0; i < N; ++i) {
        currentPath[i] = i;
    }

    // Inicjalizacja ziarna losowości (w main() lub tu, zależnie od architektury)
    
    auto startTime = std::chrono::high_resolution_clock::now();

    // Główna pętla wykonująca się K razy
    for (int k = 0; k < K; ++k) {
        // 1. Generowanie losowej permutacji
        shuffleArray(currentPath, N);

        int currentCost = 0;
        bool isValidPath = true;

        // 2. Sumowanie kosztu wylosowanej trasy
        for (int i = 0; i < N - 1; ++i) {
            int weight = g.getEdge(currentPath[i], currentPath[i + 1]);
            if (weight == -1) { // Brak przejścia
                isValidPath = false;
                break;
            }
            currentCost += weight;
        }

        // 3. Zamknięcie cyklu (od ostatniego do pierwszego miasta w tablicy)
        if (isValidPath) {
            int returnWeight = g.getEdge(currentPath[N - 1], currentPath[0]);
            if (returnWeight == -1) {
                isValidPath = false;
            } else {
                currentCost += returnWeight;
            }
        }

        // 4. Aktualizacja najlepszego rozwiązania
        if (isValidPath && currentCost < minCost) {
            minCost = currentCost;
            for (int i = 0; i < N; ++i) {
                bestPath[i] = currentPath[i];
            }
            bestPath[N] = currentPath[0]; // dopełnienie cyklu do wyświetlenia
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    // Wyświetlanie wyników 
    std::cout << "--- Wyniki Algorytmu Losowego ---\n";
    std::cout << "Sprawdzono permutacji: " << K << "\n";
    
    if (minCost == INF) {
        std::cout << "Nie znaleziono zadnego zamknietego cyklu!\n";
    } else {
        std::cout << "Minimalny koszt: " << minCost << "\n";
        std::cout << "Najlepsza sciezka: ";
        for (int i = 0; i <= N; ++i) {
            std::cout << bestPath[i];
            if (i < N) std::cout << " -> ";
        }
        std::cout << "\n";
    }
    std::cout << "Czas wykonania: " << duration << " mikrosekund\n";

    // Zwalnianie pamięci
    delete[] currentPath;
    delete[] bestPath;
}

int main() {
    Graph graph(0); // Inicjalizacja grafu z 0 miast
    graph.getGraphfromFile("tsp_6_1.txt");
    graph.printGraph(); // Wyświetlenie grafu
    graph.runBruteForce(graph, 0); // Uruchomienie algorytmu Brute-Force z wierzchołkiem startowym 0
    graph.runTieBreakingNN(graph, 0); // Uruchomienie algorytmu Tie-Breaking Nearest Neighbour z wierzchołkiem startowym 0
    graph.runRepetitiveNearestNeighbour(graph); // Uruchomienie algorytmu Repetitive Nearest Neighbour
    graph.runRandomAlgorithm(graph, 10000); // Uruchomienie algorytmu losowego z K=100000 permutacji
    graph.getGraphfromFile("tsp_10.txt");
    graph.runBruteForce(graph, 0); // Uruchomienie algorytmu Brute-Force z wierzchołkiem startowym 0
    graph.runTieBreakingNN(graph, 0); // Uruchomienie algorytmu Tie-Breaking Nearest Neighbour z wierzchołkiem startowym 0
    graph.runRepetitiveNearestNeighbour(graph); // Uruchomienie algorytmu Repetitive Nearest Neighbour
    graph.runRandomAlgorithm(graph, 100000); // Uruchomienie algorytmu losowego z K=100000 permutacji
    return 0;
}