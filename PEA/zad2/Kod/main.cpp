#include "graph.h"
#include "customStructures.h"
#include <fstream>
#include <iostream>
#include <string>

int main(){
    Graph graph(0); // Inicjalizacja grafu
    int choice = -1;
    std::string filename;
    AlgorithmResult resultBFS;
    AlgorithmResult resultBestFS;
    // Menu
    while (choice != 0){
        std::cout << "\n=== ATSP zadanie 1 ===\n";
        std::cout << "1. Wczytanie danych z pliku\n";
        std::cout << "2. Wygenerowanie danych losowych\n";
        std::cout << "3. Wyswietlenie aktualnych danych\n";
        std::cout << "4. Uruchomienie algorytmu\n";
        std::cout << "5. Pomiary czasowe algorytmow BreadthFS i BestFS dla 5 rozmiarow problemu\n";
        // std::cout << "5. Badania czasowe BF (Pomiar czasu dla 7 roznych wartosci N)\n";
        // std::cout << "6. Badania bledu wzglednego (Porownanie wynikow algorytmow NN, RNN, Losowego do BF dla 5 roznych rozmiarow)\n";
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
            std::cout << "\n1. BnB: Breadth-First-Search \n2. BnB: Best-First-Search \n3. Wszystkie\nWybor: ";
            int algChoice;
            std::cin >> algChoice;
            switch (algChoice){
            case 1:
                resultBFS = graph.runBnB_BFS(graph);
                std::cout << "\n--- WYNIKI BnB: Breadth-First-Search ---\n";
                std::cout << "Koszt: " << resultBFS.cost << "\n";
                std::cout << "Czas: " << resultBFS.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultBFS.pathSize; ++i){
                    std::cout << resultBFS.path[i];
                    if (i < resultBFS.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                delete[] resultBFS.path;
                break;
            case 2:{
                resultBestFS = graph.runNN(graph, 0);
                std::cout << "\n--- WYNIKI BnB: Best-First-Search ---\n";
                std::cout << "Koszt: " << resultBestFS.cost << "\n";
                std::cout << "Czas: " << resultBestFS.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultBestFS.pathSize; ++i){
                    std::cout << resultBestFS.path[i];
                    if (i < resultBestFS.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                delete[] resultBestFS.path;
                break;
            }
            case 3:{
                resultBFS = graph.runBnB_BFS(graph);
                std::cout << "\n--- WYNIKI BnB: Breadth-First-Search ---\n";
                std::cout << "Koszt: " << resultBFS.cost << "\n";
                std::cout << "Czas: " << resultBFS.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultBFS.pathSize; ++i){
                    std::cout << resultBFS.path[i];
                    if (i < resultBFS.pathSize - 1)
                    std::cout << " -> ";
                }
                std::cout << "\n";
                std::cout<<resultBFS.aborted<<std::endl;
                delete[] resultBFS.path;

                resultBestFS = graph.runBnB_BestFS(graph);
                std::cout << "\n--- WYNIKI BnB: Best-First-Search ---\n";
                std::cout << "Koszt: " << resultBestFS.cost << "\n";
                std::cout << "Czas: " << resultBestFS.timeMicroseconds << " us\n";
                std::cout << "Sciezka: ";
                for (int i = 0; i < resultBestFS.pathSize; ++i){
                    std::cout << resultBestFS.path[i];
                    if (i < resultBestFS.pathSize - 1)
                        std::cout << " -> ";
                }
                std::cout << "\n";
                std::cout<<resultBestFS.aborted<<std::endl;
                delete[] resultBestFS.path;
                break;
            }
            default:
                std::cout << "Nieprawidlowy wybor algorytmu.\n";
            }
            break;
        case 5:{
            int startN=0;
            int weightMin, weightMax;
            int completedBFS = 0;
            int completedBestFS = 0;
            double sumTimeBFS = 0.0;
            double sumTimeBestFS = 0.0;
            double sumAbortedBFS = 0.0;
            double sumAbortedBestFS = 0.0;
            double repeatCount = 0.0;
            std::cout<<"Podaj startowy rozmiar problemu (program wykona BnB dla dla 5 kolejnych rozmiarow zaczynajac od podanego)"<<std::endl;
            std::cin>>startN;
            std::cout<<"Podaj ilosc powtorzen testowych dla danego rozmiaru problemu"<<std::endl;
            std::cin>>repeatCount;
            std::cout<<"Podaj minimalna wage krawedzi: "<<std::endl;
            std::cin>>weightMin;
            std::cout<<"Podaj maksymalna wage krawedzi: "<<std::endl;
            std::cin>>weightMax;
            std::ofstream outFile("BnB_results.csv");
            outFile<<"Algorytm,N,Czas[Milisekundy],Przerwane[%]\n";
            std::cout<<"\n=== Badania czasowe algorytmow BnB ===\n";
            for (int currentN = startN; currentN < startN + 10; currentN++){
                sumTimeBFS = 0.0;
                sumTimeBestFS = 0.0;
                sumAbortedBFS = 0.0;
                sumAbortedBestFS = 0.0;
                completedBFS = 0;
                completedBestFS = 0;
                for (int i=0; i<repeatCount; i++){
                    std::cerr<<"Rozmiar: "<<currentN<<", Iteracja: "<<i+1<<"\n";
                    graph.generateRandomGraph(currentN, weightMin, weightMax);
                    AlgorithmResult resBFS = graph.runBnB_BFS(graph);
                    AlgorithmResult resBestFS = graph.runBnB_BestFS(graph);
                    if (!resBFS.aborted) {
                        sumTimeBFS += resBFS.timeMicroseconds;
                        completedBFS++;
                    }
                    if (!resBestFS.aborted) {
                        sumTimeBestFS += resBestFS.timeMicroseconds;
                        completedBestFS++;
                    }
                    // sumTimeBFS += resBFS.timeMicroseconds;
                    // sumTimeBestFS += resBestFS.timeMicroseconds;
                    if(resBFS.aborted){
                        std::cout<<"Iteracja "<<i<<"algorytmu BreadthFS zostala przerwana (timeout)"<<std::endl;
                        sumAbortedBFS += 1.0;
                    }    
                    if(resBestFS.aborted){
                        std::cout<<"Iteracja "<<i<<"algorytmu BestFS zostala przerwana (timeout)"<<std::endl;
                        sumAbortedBestFS += 1.0;
                    }
                    delete[] resBFS.path;
                    delete[] resBestFS.path;
                }
                if(completedBFS == 0) completedBFS = 1; 
                if(completedBestFS == 0) completedBestFS = 1; 
                double avgTimeBFS = sumTimeBFS / completedBFS;
                double avgTimeBestFS = sumTimeBestFS / completedBestFS;
                double abortedPercentBFS = (sumAbortedBFS / repeatCount) * 100.0;
                double abortedPercentBestFS = (sumAbortedBestFS / repeatCount) * 100.0;
                std::cout<<"N: "<<currentN<<", BnB BFS - Sredni czas: "<<avgTimeBFS<<" us, Przerwane: "<<abortedPercentBFS<<" %\n";
                std::cout<<"N: "<<currentN<<", BnB BestFS - Sredni czas: "<<avgTimeBestFS<<" us, Przerwane: "<<abortedPercentBestFS<<" %\n";
                outFile<<"BnB BFS,"<<currentN<<","<<avgTimeBFS<<","<<abortedPercentBFS<<"\n";
                outFile<<"BnB BestFS,"<<currentN<<","<<avgTimeBestFS<<","<<abortedPercentBestFS<<std::endl;
            }
            outFile.close();
            break;
        }
        // case 5:{
        //     int startN = 0;
        //     int weightMin, weightMax;
        //     std::ofstream outFile("BF_times.csv");
        //     std::cout << "\n=== Badania czasowe Brute-Force ===\n";
        //     std::cout << "Podaj poczatkowa liczbe miast do testowania (np. 10): ";
        //     std::cin >> startN;
        //     std::cout << "Podaj minimalna wage krawedzi: ";
        //     std::cin >> weightMin;
        //     std::cout << "Podaj maksymalna wage krawedzi: ";
        //     std::cin >> weightMax;
        //     outFile << "N,Czas[Mikrosekundy]\n";
        //     for (int i = startN; i < startN + 7; i++){
        //         graph.generateRandomGraph(i, weightMin, weightMax);
        //         AlgorithmResult res = graph.runBruteForce(graph, 0);
        //         std::cout << "N: " << i << ", Czas: " << res.timeMicroseconds << " us\n";
        //         outFile << i << "," << res.timeMicroseconds << "\n";
        //         delete[] res.path;
        //     }
        //     outFile.close();
        //     break;
        // }
        // case 6:{
        //     int N;
        //     std::cout << "Podaj poczatkowa liczbe miast do testowania (np. 10): ";
        //     std::cin >> N;
        //     std::ofstream outFile("RelativeErrors.csv");
        //     std::cout << "\n=== Badania bledu wzglednego ===\n";
        //     outFile << "N,ErrorNN,ErrorRNN,ErrorRandom\n";
        //     for (int currentGraphSize = N; currentGraphSize < N + 5; currentGraphSize++){
        //         double sumErrorNN = 0.0;
        //         double sumErrorRNN = 0.0;
        //         double sumErrorRandom = 0.0;
        //         int K = 10 * currentGraphSize;
        //         for (int j = 0; j < 100; j++){
        //             graph.generateRandomGraph(currentGraphSize, 1, 100);
        //             AlgorithmResult resBF = graph.runBruteForce(graph, 0);
        //             double OPTcost = static_cast<double>(resBF.cost);

        //             AlgorithmResult resNN = graph.runNN(graph, 0);
        //             AlgorithmResult resRNN = graph.runRNN(graph);
        //             AlgorithmResult resRandom = graph.runRandomAlgorithm(graph, K);

        //             sumErrorNN += (resNN.cost - OPTcost) / OPTcost * 100.0;
        //             sumErrorRNN += (resRNN.cost - OPTcost) / OPTcost * 100.0;
        //             sumErrorRandom += (resRandom.cost - OPTcost) / OPTcost * 100.0;

        //             delete[] resBF.path;
        //             delete[] resNN.path;
        //             delete[] resRandom.path;
        //         }
        //         double avgErrorNN = sumErrorNN / 100.0;
        //         double avgErrorRNN = sumErrorRNN / 100.0;
        //         double avgErrorRandom = sumErrorRandom / 100.0;
        //         std::cout << "Wyniki dla rozmiaru N=" << currentGraphSize << ":\n";
        //         std::cout << "Sredni blad wzgledny NN: " << avgErrorNN << " %\n";
        //         std::cout << "Sredni blad wzgledny RNN: " << avgErrorRNN << " %\n";
        //         std::cout << "Sredni blad wzgledny Random: " << avgErrorRandom << " %\n";
        //         outFile << currentGraphSize << "," << avgErrorNN << "," << avgErrorRNN << "," << avgErrorRandom << "\n";
        //     }
        //     outFile.close();
        //     break;
        // }
        }
    }
    return 0;
}
