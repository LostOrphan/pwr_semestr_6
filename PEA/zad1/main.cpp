#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
class Graph {
private:
    int** matrix = nullptr;
    int N;

public:
    Graph(int cities) {
        N = cities;
    

        matrix = new int*[N]; 
        for (int i = 0; i < N; ++i) {
            matrix[i] = new int[N];
        }
    }

    ~Graph() {
        // usuniecie kazdej kolumny tablicy
        for (int i = 0; i < N; ++i) {
            delete[] matrix[i];
        }
        //usuniecie tablicy 
        delete[] matrix;
    }
    
    void setEdge(int from, int to, int weight) {
        matrix[from][to] = weight;
    }

    int getEdge(int from, int to) {
        return matrix[from][to];
    }
    void getGraphfromFile(const std::string& filename) {

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
    void generateRandomGraph(int cities, int minWeight, int maxWeight) {
        // jesli macierz istnieje, usuniecie
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
                    matrix[i][j] = minWeight + rand() % (maxWeight - minWeight + 1); // Losowa waga między minWeight a maxWeight
                }
            }
        }
    }
    void printGraph() {
        std::cout << "Graf o rozmiarze " << N << ":" << std::endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                std::cout << matrix[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }
    //zamiana elementow
    void swapElements(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    //odwrocenie tablicy
    void reverseArray(int* arr, int start, int end) {
        while (start < end) {
            swapElements(arr[start], arr[end]);
            start++;
            end--;
        }
    }

};
int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicjalizacja generatora losowego
    Graph graph(0); // Inicjalizacja grafu z 0 miast
    graph.generateRandomGraph(5, 1, 10); // Generowanie losowego grafu z 5 miastami i wagami od 1 do 10
    graph.printGraph(); // Wyświetlenie grafu
    return 0;
}