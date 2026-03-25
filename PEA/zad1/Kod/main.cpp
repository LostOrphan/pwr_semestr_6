#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>

int main(){
    Graph graph(0); // Inicjalizacja grafu
    int choice = -1;
    std::string filename;
    AlgorithmResult resultBF;
    AlgorithmResult resultNN;
    AlgorithmResult resultRNN;
    AlgorithmResult resultRandom;
    // Menu
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
            std::cout << "Podaj poczatkowa liczbe miast do testowania (np. 10): ";
            std::cin >> N;
            std::ofstream outFile("RelativeErrors.csv");
            std::cout << "\n=== Badania bledu wzglednego ===\n";
            outFile << "N,ErrorNN,ErrorRNN,ErrorRandom\n";
            for (int currentGraphSize = N; currentGraphSize < N + 5; currentGraphSize++){
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

                    sumErrorNN += (resNN.cost - OPTcost) / OPTcost * 100.0;
                    sumErrorRNN += (resRNN.cost - OPTcost) / OPTcost * 100.0;
                    sumErrorRandom += (resRandom.cost - OPTcost) / OPTcost * 100.0;

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
