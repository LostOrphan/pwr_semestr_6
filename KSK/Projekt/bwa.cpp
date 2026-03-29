#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
const int INF = 2147483647;
//Struktura przechowujaca wyniki dzialania algorytmow
struct AlgorithmResult
{
    int cost;
    long long timeMicroseconds;
    int *path;
    int pathSize;
};
class Graph
{
private:
    int **matrix = nullptr;
    int N;
    //Zmienne do RNN
    int globalMinCostRNN = INF;
    int *globalBestPathRNN = nullptr;
    int globalStartNode = -1;

public:
    Graph(int cities);
    ~Graph();

    void setEdge(int from, int to, int weight);
    int getEdge(int from, int to) const;
    void getGraphfromFile(const std::string &filename);
    void generateRandomGraph(int cities, int minWeight, int maxWeight);
    void printGraph();
    void swapElements(int &a, int &b);
    void reverseArray(int *arr, int start, int end);
    bool generateNextPermutation(int *arr, int size);
    AlgorithmResult runBruteForce(const Graph &g, int startNode = 0);
    int getN() const;
    void exploreNN(const Graph &g, int currentNode, int startNode, bool *visited,
                   int *currentPath, int step, int currentCost,
                   int &bestCost, int *bestPath);
    AlgorithmResult runNN(const Graph &g, int startNode = 0);
    AlgorithmResult runRNN(const Graph &g);
    void exploreRNNBranches(const Graph &g, int currentNode, bool *visited, int *currentPath, int step, int currentCost);
    void shuffleArray(int *arr, int size);
    AlgorithmResult runRandomAlgorithm(const Graph &g, int K);
};

Graph::Graph(int cities){
    N = cities;

    matrix = new int *[N];
    for (int i = 0; i < N; ++i)
    {
        matrix[i] = new int[N];
    }
}

Graph::~Graph(){
    //Usuniecie kazdej kolumny tablicy
    for (int i = 0; i < N; ++i)
    {
        delete[] matrix[i];
    }
    //Usuniecie tablicy
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
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
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
    //Generacja liczb losowych uzywajac rozkladu jednostajnie ciaglego
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minWeight, maxWeight);

    //Jesli macierz istnieje, usuniecie
    if (matrix != nullptr){
        for (int i = 0; i < N; ++i){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    //Stworzenie nowej macierzy
    N = cities;
    matrix = new int *[N];
    for (int i = 0; i < N; ++i){
        matrix[i] = new int[N];
    }
    //Wypelnienie macierzy losowymi wagami z zakresu <minWeight;maxWeight>
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

//Zamiana elementow (implementacja std::swap)
void Graph::swapElements(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

//Odwrocenie tablicy (implementacja std::reverse)
void Graph::reverseArray(int *arr, int start, int end){
    while (start < end){
        swapElements(arr[start], arr[end]);
        start++;
        end--;
    }
}
//Generowanie następnej permutacji (implementacja std::next_permutation)
bool Graph::generateNextPermutation(int *arr, int size){
    int i = size - 2;
    //Szukamy pierwszego elementu od końca, który jest mniejszy od swojego prawego sąsiada
    while (i >= 0 && arr[i] >= arr[i + 1]){
        i--;
    }
    //Jeśli nie znaleziono, to znaczy, że sprawdziliśmy wszystkie permutacje
    if (i < 0){
        return false;
    }
    int j = size - 1;
    //Szukamy elementu większego od wczesniej zanlezionego po jego prawej stronie (idąc od końca)
    while (arr[j] <= arr[i]){
        j--;
    }
    //Zamieniamy je miejscami
    swapElements(arr[i], arr[j]);
    //Odwracamy wszystko na prawo od i
    reverseArray(arr, i + 1, size - 1);
    return true;
}
void Graph::shuffleArray(int *arr, int size){
    for (int i = size - 1; i > 0; --i){
        //Losujemy indeks j z zakresu od 0 do i
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(gen);
        //Ręczny swap
        swapElements(arr[i], arr[j]);
    }
}
//Główna funkcja algorytmu Brute-Force
AlgorithmResult Graph::runBruteForce(const Graph &g, int startNode){
    int N = g.getN();
    //Dynamiczna alokacja tablicy na wierzcholki do odwiedzenia
    int *verticesToVisit = new int[N - 1];
    //Pozycja w tablicy verticesToVisit
    int idx = 0;
    for (int i = 0; i < N; ++i){
        if (i != startNode){
            verticesToVisit[idx] = i;
            idx++;
        }
    }

    int minCost = INF;
    //Dynamiczna alokacja tablicy do zapamietania najlepszej sciezki
    int *bestPath = new int[N + 1];

    //Rozpoczęcie pomiaru czasu
    auto startTime = std::chrono::high_resolution_clock::now();

    // Główna pętla sprawdzajaca wszystkie permutacje (N-1)!
    do{
        int currentPathCost = 0;
        int currentNode = startNode;
        bool isValidPath = true;

        //Sumowanie kosztów dla aktualnej permutacji
        for (int i = 0; i < N - 1; ++i){
            int nextNode = verticesToVisit[i];
            if (g.getEdge(currentNode, nextNode) == -1){ 
                // Brak krawędzi
                isValidPath = false;
                break;
            }
            currentPathCost += g.getEdge(currentNode, nextNode);
            currentNode = nextNode;
        }
        //Dodanie kosztu powrotu do miasta startowego (cykl)
        currentPathCost += g.getEdge(currentNode, startNode);

        //Aktualizacja najlepszego rozwiązania
        if (isValidPath && currentPathCost < minCost){
            minCost = currentPathCost;
            bestPath[0] = startNode;
            for (int i = 0; i < N - 1; ++i)
            {
                bestPath[i + 1] = verticesToVisit[i];
            }
            // zamknięcie cyklu do wypisania
            bestPath[N] = startNode; 
        }

    }while(generateNextPermutation(verticesToVisit, N - 1));

    // Zakończenie pomiaru czasu
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    //Zwolnienie pamieci
    delete[] verticesToVisit;
    //Zwrot struktury wynikow
    return {minCost, duration, bestPath, N + 1};
}
//Funkcja rekurencyjna obslugujaca remisow w algorytmie NN
void Graph::exploreNN(const Graph &g, int currentNode, int startNode, bool *visited, int *currentPath, int step, int currentCost, int &bestCost, int *bestPath){
    int N = g.getN();
    //Warunek koncowy: kazde miasto odwiedzone
    if (step == N){
        int returnCost = g.getEdge(currentNode, startNode);
        if (returnCost != -1){
            int totalCost = currentCost + returnCost;

            //Aktualizacja najlepszego globalnego rozwiązania
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
    //KROK 1: Szukamy najmniejszej wagi wśród nieodwiedzonych sasiadow
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

    //KROK 2: Wchodzimy we wszystkie sciezki o najmniejszej wadze
    for (int i = 0; i < N; ++i){
        if (!visited[i]){
            int weight = g.getEdge(currentNode, i);
            //Jesli trafiamy na miasto z minimalną wagą 
            if (weight == minWeight){
                //Oznaczamy miasto jako odwiedzone na potrzeby danej gałęzi
                visited[i] = true;
                currentPath[step] = i;
                //Rekurencyjne przejscie do kolejnego kroku
                exploreNN(g, i, startNode, visited, currentPath, step + 1, currentCost + minWeight, bestCost, bestPath);
                //Backtracking: cofniecie odwiedzenia miasta, aby sprawdzic inne galezie o tej samej wadze
                visited[i] = false;
            }
        }
    }
}
//Funkcja startowa dla NN z remisami
AlgorithmResult Graph::runNN(const Graph &g, int startNode){
    int N = g.getN();
    bool *visited = new bool[N];
    int *currentPath = new int[N + 1];
    int *bestPath = new int[N + 1];
    //Wszystkie miasta jako nieodwiedzone
    for (int i = 0; i < N; ++i){
        visited[i] = false;
    }
    int bestCost = INF;

    auto startTime = std::chrono::high_resolution_clock::now();

    //Inicjalizacja stanu dla punktu startowego
    visited[startNode] = true;
    currentPath[0] = startNode;

    //Uruchomienie rekurencjej eksploracji NN
    exploreNN(g, startNode, startNode, visited, currentPath, 1, 0, bestCost, bestPath);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    //Zwalnianie pamięci
    delete[] visited;
    delete[] currentPath;
    //Zwrot struktury wyników
    return {bestCost, duration, bestPath, N + 1};
}

//Funkcja rekurencyjna obslugujaca remisy w RNN
void Graph::exploreRNNBranches(const Graph &g, int currentNode, bool *visited, int *currentPath, int step, int currentCost){
    int N = g.getN();
    //Warunek koncowy: kazde miasto odwiedzone
    if (step == N){
        int returnCost = g.getEdge(currentNode, globalStartNode);
        if (returnCost != -1){
            int totalCost = currentCost + returnCost;

            //Aktualizacja najlepszej sciezki jesli znaleziona
            if (totalCost < globalMinCostRNN){
                globalMinCostRNN = totalCost;
                for (int i = 0; i < N; ++i){
                    globalBestPathRNN[i] = currentPath[i];
                }
                globalBestPathRNN[N] = globalStartNode;
            }
        }
        return;
    }

    int minWeight = INF;

    //KROK 1: Szukamy najmniejszej wagi wśród nieodwiedzonych sasiadow
    for (int i = 0; i < N; ++i)
    {
        if (!visited[i])
        {
            int weight = g.getEdge(currentNode, i);
            if (weight != -1 && weight < minWeight)
            {
                minWeight = weight;
            }
        }
    }
    if (minWeight == INF)
        return;

    //KROK 2: Wchodzimy we wszystkie sciezki o najmniejszej wadze
    for (int i = 0; i < N; ++i){
        if (!visited[i]){
            int weight = g.getEdge(currentNode, i);
            //Jesli trafiamy na miasto z minimalną wagą 
            if (weight == minWeight){
                //Oznaczamy miasto jako odwiedzone na potrzeby danej gałęzi
                visited[i] = true;
                currentPath[step] = i;
                exploreRNNBranches(g, i, visited, currentPath, step + 1, currentCost + minWeight);
                // Backtracking: cofamy się, aby sprawdzić inne krawędzie o tej samej wadze
                visited[i] = false;
            }
        }
    }
}

//Funkcja startowa dla RNN z remisami
AlgorithmResult Graph::runRNN(const Graph &g){
    int N = g.getN();

    bool *visited = new bool[N];
    int *currentPath = new int[N + 1];
    //Jesli tablica istnieje, usuniecie
    if (globalBestPathRNN != nullptr){
        delete[] globalBestPathRNN;
    }
    globalBestPathRNN = new int[N + 1];
    globalMinCostRNN = INF;
    //Start pomiaru
    auto startTime = std::chrono::high_resolution_clock::now();

    //Algorytm uruchamiany z kazdego miasta jako punkt startu
    for (int startNode = 0; startNode < N; ++startNode){
        // Resetowanie tablicy odwiedzin dla nowego punktu startowego
        for (int i = 0; i < N; ++i){
            visited[i] = false;
        }
        globalStartNode = startNode;
        visited[startNode] = true;
        currentPath[0] = startNode;
        //Uruchomienie rekurencyjnego przeszukania dla aktualnego punktu startowego
        exploreRNNBranches(g, startNode, visited, currentPath, 1, 0);
    }
    //Koniec pomiaru
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    // Zwolnienie pamięci
    delete[] visited;
    delete[] currentPath;
    // Zwrot struktury wyników
    return {globalMinCostRNN, duration, globalBestPathRNN, N + 1};
}
//Glowna funkcja algorytmu losowego
AlgorithmResult Graph::runRandomAlgorithm(const Graph &g, int K){
    int N = g.getN();

    int *currentPath = new int[N];
    int *bestPath = new int[N + 1];
    int minCost = INF;

    for (int i = 0; i < N; ++i){
        currentPath[i] = i;
    }
    //Start pomiaru
    auto startTime = std::chrono::high_resolution_clock::now();

    //Glowna petla sprawdzajaca K losowych permutacji
    for (int k = 0; k < K; ++k){
        //Generowanie losowej permutacji
        shuffleArray(currentPath, N);

        int currentCost = 0;
        bool isValidPath = true;

        //Sumowanie kosztu wylosowanej trasy
        for (int i = 0; i < N - 1; ++i){
            int weight = g.getEdge(currentPath[i], currentPath[i + 1]);
            // Brak przejścia
            if (weight == -1){
                isValidPath = false;
                break;
            }
            currentCost += weight;
        }
        //Zamkniecie cyklu (powrot do miasta startowego)
        if (isValidPath){
            int returnWeight = g.getEdge(currentPath[N - 1], currentPath[0]);
            if (returnWeight == -1){
                isValidPath = false;
            }
            else{
                currentCost += returnWeight;
            }
        }
        //Aktualizacja najlepszego rozwiązania
        if (isValidPath && currentCost < minCost){
            minCost = currentCost;
            for (int i = 0; i < N; ++i){
                bestPath[i] = currentPath[i];
            }
            bestPath[N] = currentPath[0];
        }
    }
    //Koniec pomiaru
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    //Zwalnianie pamięci
    delete[] currentPath;
    //Zwrot struktury wyników
    return {minCost, duration, bestPath, N + 1};
}

int main()
{
    Graph graph(0); //Inicjalizacja grafu
    int choice = -1;
    std::string filename;
    AlgorithmResult resultBF;
    AlgorithmResult resultNN;
    AlgorithmResult resultRNN;
    AlgorithmResult resultRandom;
    //Menu
    while (choice != 0){
        std::cout << "\n=== ATSP zadanie 1 ===\n";
        std::cout << "1. Wczytanie danych z pliku\n";
        std::cout << "2. Wygenerowanie danych losowych\n";
        std::cout << "3. Wyswietlenie aktualnych danych\n";
        std::cout << "4. Uruchomienie algorytmu\n";
        std::cout << "5. Badania czasowe BF (Pomiar czasu dla 7 roznych wartosci N)\n";
        std::cout << "6. Badania bledu wzglednego (Porownanie wynikow algorytmow NN, RNN, Losowego do BF dla 5 roznych rozmiarow)\n"; 
        std::cout << "0. Wyjscie\n";
        std::cout << "Wybor: ";
        std::cin >> choice;
        switch (choice){
        case 1:
            std::cout << "Podaj nazwe pliku (plik musi znajdowac sie w tym samym folderze co program): ";
            std::cin >> filename;
            graph.getGraphfromFile(filename);
            break;
        case 2:{
            int cities, minWeight, maxWeight;
            std::cout << "Podaj liczbe miast: ";
            std::cin >> cities;
            std::cout << "Podaj minimalna wage: ";
            std::cin >> minWeight;
            std::cout << "Podaj maksymalna wage: ";
            std::cin >> maxWeight;
            graph.generateRandomGraph(cities, minWeight, maxWeight);
            break;
        }
        case 3:
            graph.printGraph();
            break;
        case 4:
            std::cout << "\n1. Brute-Force\n2. NN\n3. RNN\n4. Losowy\n5.Wszystkie\nWybor: ";
            int algChoice;
            std::cin >> algChoice;
            switch (algChoice){
            case 1:
                resultBF = graph.runBruteForce(graph, 0);
                std::cout << "\n--- WYNIKI BRUTE-FORCE ---\n";
                std::cout << "Koszt: " << resultBF.cost << "\n";
                std::cout << "Czas: " << resultBF.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultBF.pathSize; ++i){
                    std::cout << resultBF.path[i];
                    if (i < resultBF.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                delete[] resultBF.path;
                break;
            case 2:
                resultNN = graph.runNN(graph, 0);
                std::cout << "\n--- WYNIKI NN ---\n";
                std::cout << "Koszt: " << resultNN.cost << "\n";   
                std::cout << "Czas: " << resultNN.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultNN.pathSize; ++i){
                    std::cout << resultNN.path[i];
                    if (i < resultNN.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                delete[] resultNN.path;
                break;
            case 3:
                resultRNN = graph.runRNN(graph);
                std::cout << "\n--- WYNIKI RNN ---\n";
                std::cout << "Koszt: " << resultRNN.cost << "\n";
                std::cout << "Czas: " << resultRNN.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultRNN.pathSize; ++i){
                    std::cout << resultRNN.path[i];
                    if (i < resultRNN.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                break;
            case 4:{
                int K;
                std::cout << "Podaj liczbe permutacji do sprawdzenia: ";
                std::cin >> K;
                resultRandom = graph.runRandomAlgorithm(graph, K);
                std::cout << "\n--- WYNIKI ALGORYTMU LOSOWEGO ---\n";
                std::cout << "Koszt: " << resultRandom.cost << "\n";
                std::cout << "Czas: " << resultRandom.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultRandom.pathSize; ++i){
                    std::cout << resultRandom.path[i];
                    if (i < resultRandom.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                delete[] resultRandom.path;
                break;
            }
            case 5:{
                int K;
                std::cout << "Podaj liczbe permutacji do sprawdzenia dla algorytmu losowego: ";
                std::cin >> K;
                resultBF = graph.runBruteForce(graph, 0);
                std::cout << "\n--- WYNIKI BRUTE-FORCE ---\n";
                std::cout << "Koszt: " << resultBF.cost << "\n";
                std::cout << "Czas: " << resultBF.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultBF.pathSize; ++i){
                    std::cout << resultBF.path[i];
                    if (i < resultBF.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                delete[] resultBF.path;

                resultNN = graph.runNN(graph, 0);
                std::cout << "\n--- WYNIKI NN ---\n";
                std::cout << "Koszt: " << resultNN.cost << "\n";
                std::cout << "Czas: " << resultNN.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultNN.pathSize; ++i){
                    std::cout << resultNN.path[i];
                    if (i < resultNN.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                delete[] resultNN.path;

                resultRNN = graph.runRNN(graph);
                std::cout << "\n--- WYNIKI RNN ---\n";
                std::cout << "Koszt: " << resultRNN.cost << "\n";
                std::cout << "Czas: " << resultRNN.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultRNN.pathSize; ++i){
                    std::cout << resultRNN.path[i];
                    if (i < resultRNN.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";

                resultRandom = graph.runRandomAlgorithm(graph, K);
                std::cout << "\n--- WYNIKI ALGORYTMU LOSOWEGO ---\n";
                std::cout << "Koszt: " << resultRandom.cost << "\n";
                std::cout << "Czas: " << resultRandom.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultRandom.pathSize; ++i){
                    std::cout << resultRandom.path[i];
                    if (i < resultRandom.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                delete[] resultRandom.path;
                break;
            }
            default:
                std::cout << "Nieprawidlowy wybor algorytmu.\n";
            }
            break;
        case 5:{
            int startN = 0;
            int weightMin, weightMax;
            std::ofstream outFile("BF_times.csv");
            std::cout << "\n=== Badania czasowe Brute-Force ===\n";
            std::cout << "Podaj poczatkowa liczbe miast do testowania (np. 10): ";
            std::cin >> startN;
            std::cout << "Podaj minimalna wage krawedzi: ";
            std::cin >> weightMin;
            std::cout << "Podaj maksymalna wage krawedzi: ";
            std::cin >> weightMax;
            outFile << "N,Czas[Mikrosekundy]\n";
            for (int i = startN; i < startN + 7; i++){
                graph.generateRandomGraph(i, weightMin, weightMax);
                AlgorithmResult res = graph.runBruteForce(graph, 0);
                std::cout << "N: " << i << ", Czas: " << res.timeMicroseconds << " us\n";
                outFile << i << "," << res.timeMicroseconds << "\n";
                delete[] res.path;
            }
            outFile.close();
            break;
        }
        case 6:{
            int N;
            std::cout<<"Podaj poczatkowa liczbe miast do testowania (np. 10): ";
            std::cin >> N;
            std::ofstream outFile("RelativeErrors.csv");
            std::cout << "\n=== Badania bledu wzglednego ===\n";
            outFile << "N,ErrorNN,ErrorRNN,ErrorRandom\n";
            for (int currentGraphSize = N; currentGraphSize < N+5; currentGraphSize++){
                double sumErrorNN = 0.0;
                double sumErrorRNN = 0.0;
                double sumErrorRandom = 0.0;
                int K = 10 * currentGraphSize;
                for (int j = 0; j < 100; j++){
                    graph.generateRandomGraph(currentGraphSize, 1, 100);
                    AlgorithmResult resBF = graph.runBruteForce(graph, 0);
                    double OPTcost = static_cast<double>(resBF.cost);
                    
                    AlgorithmResult resNN = graph.runNN(graph, 0);
                    AlgorithmResult resRNN = graph.runRNN(graph);
                    AlgorithmResult resRandom = graph.runRandomAlgorithm(graph, K);

                    sumErrorNN += (resNN.cost - OPTcost) / OPTcost *100.0;
                    sumErrorRNN += (resRNN.cost - OPTcost) / OPTcost *100.0;
                    sumErrorRandom += (resRandom.cost - OPTcost) / OPTcost *100.0;

                    delete[] resBF.path;
                    delete[] resNN.path;
                    delete[] resRandom.path;

                }
                double avgErrorNN = sumErrorNN / 100.0;
                double avgErrorRNN = sumErrorRNN / 100.0;
                double avgErrorRandom = sumErrorRandom / 100.0;
                std::cout << "Wyniki dla rozmiaru N=" << currentGraphSize << ":\n";
                std::cout << "Sredni blad wzgledny NN: " << avgErrorNN << " %\n";
                std::cout << "Sredni blad wzgledny RNN: " << avgErrorRNN << " %\n";
                std::cout << "Sredni blad wzgledny Random: " << avgErrorRandom << " %\n";
                outFile << currentGraphSize << "," << avgErrorNN << "," << avgErrorRNN << "," << avgErrorRandom << "\n";
            }
            outFile.close();
            break;
        }
        }

    }
    return 0;
}