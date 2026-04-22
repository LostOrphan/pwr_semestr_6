#import "@preview/algorithmic:1.0.7"
#import algorithmic: style-algorithm, algorithm-figure
#show: style-algorithm
#import "@preview/zero:0.6.0": ztable
#set page(
  margin: 2.5cm,
)
#set text(lang: "pl")
#set page(header: context {
  if counter(page).get().first() > 1 [
    
    #h(1fr)
    Projektowanie Efektywnych Algorytmów
  ]
})
#set page(footer: context {
    if counter(page).get().first() > 1 [
  #h(1fr)
  #counter(page).display(
    "1/1",
    both: true,)
    ]}
)
#align(center)[
  // --- Header section ---
  #text(size: 24pt)[
  *Politechnika Wrocławska* \
  Wydział Informatyki i Telekomunikacji \
  
  ]
  // Add space before title
  #v(4cm)

  // --- Title section ---
  #text(size: 28pt, weight: "bold")[Projektowanie Efektywnych Algorytmów] \ \
  #text(size: 24pt)[Sprawozdanie z zadania nr 2] \
  #v(7cm)

  // --- Author section ---
  #text(size: 18pt)[

  Daniel Gościński 280878\

  ]
  #v(2cm)

  // --- Instructor section ---
  #text(size: 18pt)[Prowadzący: \
   dr inż. Jarosław Mierzwa
  ]
]
#pagebreak()
#set page(
  margin: 2.5cm,
)

#set heading(numbering: "1.")
#text(size:18pt)[
#outline(title: text(size: 42pt, weight: "bold")[Spis treści],
        )]
#pagebreak()
#set page(margin:2cm)
#set text(size:14pt,hyphenate: false)
#set par(justify: true, first-line-indent:(amount:2em,all:true), spacing: 1em)
#show figure.where(kind: table): set figure.caption(position: top)

#set list(marker: [--])
= Wstęp teoretyczny
Problem komiwojażera to jeden z najstarszych i dobrze znanych problemów klasy NP-trudnych. Oznacza to, że nie udało się uzyskać dla niego algorytmu, który potrafiłby znaleźć optymalne rozwiązanie w czasie wielomianowym. 

Zadanie te polega na znalezieniu najmniejszego cyklu Hamiltona w grafie ważonym@a50e4ff5-1289-3708-acd6-130ff0b48989. Wyróżniamy dwa rodzaje problemu: 
- Symetryczny: odległości między dwoma miastami są identyczne
- Asymetryczny: odległości między dwoma miastami nie są identyczne (Droga A-B ma inną wagę niż droga B-A)
Na potrzeby zadania rozważany jest wariant asymetryczny (*Asymetric Travelling Salesman Problem*).
#figure(image("przykładTSP.png", width:70%),caption: [Przykładowa wizualizacja problemu ATSP \ #text(size:10pt)[https://lopezyse.medium.com/graphs-solving-the-travelling-salesperson-problem-tsp-in-python-54ec2b315977]],supplement: [Zdjęcie])

= Opis algorytmów
Na potrzeby zadania drugiego analizowane są algorytmy wykorzystujące metodę *Podziału i Ograniczeń* (ang. *Branch-and-Bound*, BnB), która polega przeszukiwaniu drzewa reprezentujacego przestrzeń rozwiązań @pea-wykład. Zgodnie z nazwą wykorzystywane są dwa kluczowe aspekty metody:
1. *Branching*: polega na dzieleniu rozwiązań na rozłączne podzbiory
2. *Ograniczenie*: polega na pomijaniu gałęzi drzewa, o których wiadomo, że nie zawierają optymalnego rozwiązania.
Aby móc przeszukiwać przestrzeń rozwiązań należy wybrać metodę przeszukiwania. W tym zadaniu projektowym skupiono się na przeszukiwaniu wszerz (ang. Breadth-First-Search; BreadthFS), oraz na przeszukiwaniu najpierw najlepszy (ang. Best-First-Search; BestFS)

Przeszukiwanie wszerz to metoda ślepa polegająca na eksplorowaniu grafu poziom po poziomie. Zaczynając od korzenia algorytm sprawdza wszystkich swoich potomków, a następnie przechodzi kolejno do następnych poziomów drzewa. Wykorzystuje on kolejkę FIFO, zapisując w niej kolejne węzły do przeanalizowania. Ponieważ jest to algorytm ślepy, nie posiada on żadnych metod rankingu potencjału ścieżek, tylko analizuje kolejne wierzchołki aż do natknięcia się na ostatni liść. Z tego też powodu zajmuje on znaczącą ilość czasu, a kolejka w gęstym grafie może przechowywać bardzo duże ilości informacji, zajmując duże ilości pamięci podręcznej.

Przeszukiwanie najpierw-najlepszy w porównaniu do przeszukiwania wszerz wykorzystuje kolejkę priorytetową, w wyniku czego zawsze wybiera do rozwinięcia węzeł, który w danej chwili jest najbardziej obiecujący. Należy zaznaczyć, że węzeł o najtańszej ścieżce może znaleźć się na wyższym poziomie drzewa (np. po rozwinięciu jednej ścieżki koszt jej zwiększył się, w wyniku czego najmniejszy koszt ma teraz węzeł na wyższym poziomie drzewa). W wyniku działa algorytm szybko uzyskuje pierwsze legalne rozwiązanie (zgodne z zasadami ATSP), które można następnie wykorzystać jako punkt odniesienia do odcinania gorszych ścieżek. Ze względu na swoją metodę działania algorytm wykonuje się szybciej niż przeszukiwanie wszerz, co zostanie sprawdzone podczas prowadzonych badań.

W celu przyśpieszenia działania algorytmów zgodnie z zasadą *BnB* możemy wykorzystać różne metody zawężenia puli możliwych rozwiązań. Wykonuje się to poprzez wprowadzenie dolnych i górnych ograniczeń.

Górne ograniczenie (ang. Upper Bound; UB) to koszt pewnej pełnej uzyskanej ścieżki, którą następne wykorzystuje się do porównania następnych rozwiązań. Startowe UB można uzyskać poprzez np. szybkie algorytmy dające przybliżone rozwiązanie (jak np. algorytm NN wykonany w zadaniu 1). Następnie uzyskując następne rozwiązania możemy zastąpić istniejące UB nowym, jeśli jego wartość jest mniejsza. W wyniku takiego działania będziemy ciągle zawężać obszar poszukiwań ścieżki optymalnej.

Dolne ograniczenie (ang. Lower Bound; LB) to szacowanie najmniejszego możliwego kosztu, jaki możemy osiągnąć rozwijając daną ścieżkę. Istnieją różne metody szacowania LB, które różnią się jakością uzyskiwanego ograniczenia.

Posiadając oba ograniczenia możemy określić, czy dana ścieżka jest warta kontynuowania. Jeśli LB jest większe od UB, oznacza to, że najlepsza możliwa ścieżka z danego węzła i tak będzie posiadać koszt większy niż aktualnie najlepsza znana droga, a w wyniku posiadania tej wiedzy możemy analizowany węzeł porzucić
= Przykład praktyczny algorytmów
Załóżmy macierz sąsiedztwa składającą się z 4 miast o następujących wartościach:
#figure(
ztable(columns: 5, format:(none,auto),
  [], [*Miasto 0*], [*Miasto 1*], [*Miasto 2*], [*Miasto 3*],
  [*Miasto 0*],[-1],[34],[*78*],[45],
  [*Miasto 1*],[21],[-1],[56],[23],
  [*Miasto 2*],[67],[12],[-1],[89],
  [*Miasto 3*],[32],[44],[18],[-1],

), caption: "Przykładowa macierz sąsiedztwa")
Zakładamy, że zaczynamy od miasta 0. Zaczynamy od obliczenia UB przy pomocy algorytmu najbliższego sąsiada:
#text(align(center)[*0->1->3->2->0*\ Koszt: $34+23+18+67=142$])
Nastepnie obliczamy LB korzenia. W tym przypadku (oraz w implementacji algorytmów) wykorzystane zostało obliczanie LB poprzez wyliczenie najtańszej ścieżki od węzła do korzenia, pomijając ograniczenia problemu. Wynik ten może być niemozliwy do osiągnięcia, jednak jest on wystarczający na potrzeby działania algorytmu. Dokładny opis implementacji funkcji obliczającej LB znajduje się w *sekcji 4.*
#text(align(center)[Koszt: $0+(21+12+18)=51$])

+ Algorytm Best-First-Search
Do sprawdzania węzłów wykorzystywać będziemy kolejkę priorytetową

Poziom 1: rozwinięcie miasta 0

Zaczynamy od rozpisania możliwych dróg
#align(center)[#ztable(columns: 2, format:(none,auto),
  [*Ścieżka*], [*LB*], 
  [0->1],[64],
  [0->3],[78],
  [0->2],[117]
)]

Krok 1: Wybieramy 0->1 (najlepsze LB)

#align(center)[#ztable(columns: 3, format:(none,auto),
  [*Ścieżka*], [*Koszt*], [*Wartość LB*],
  [0->1->2],[90],[$90+(18)=108$],
  [0->1->3],[57],[$57+(12)=69$],

)]
Aktualny stan kolejki to: 
#align(center)[#ztable(columns: 2, format:(none,auto),
  [*Ścieżka*], [*LB*], 
  [0->1->3],[69],
  [0->3],[78],
  [0->1->2],[108],
  [0->2],[117]
)]

Krok 2: Wybieramy 0->1->3 
#align(center)[#ztable(columns: 3, format:(none,auto),
  [*Ścieżka*], [*Koszt*], [*Wartość LB*],
  [0->1->3->2],[75],[Wszystko odwiedzone],
)]

Domykamy cykl z miasta 2 do 0

Łącznie uzyskujemy koszt $75+67=142$, który jest równy z UB (brak zmian)

Aktualny stan kolejki to: 
#align(center)[#ztable(columns: 2, format:(none,auto),
  [*Ścieżka*], [*LB*], 
  [0->3],[78],
  [0->1->2],[108],
  [0->2],[117]
)]

Krok 3: Wybieramy 0->3
#align(center)[#ztable(columns: 3, format:(none,auto),
  [*Ścieżka*], [*Koszt*], [*Wartość LB*],
  [0->3->1],[89],[101],
  [0->3->2],[63],[84]
)]

Aktualny stan kolejki to:
#align(center)[#ztable(columns: 2, format:(none,auto),
  [*Ścieżka*], [*LB*], 
  [0->3->2],[84],
  [0->3->1],[101],
  [0->1->2],[108],
  [0->2],[117]
)]

Krok 4: Wyciągamy 0->3->2
#align(center)[#ztable(columns: 3, format:(none,auto),
  [*Ścieżka*], [*Koszt*], [*Wartość LB*],
  [0->3->2->1],[75], [Wszystko odwiedzone]
)]

Domykamy cykl z miasta 1 do miasta 0

Łącznie uzyskujemy koszt $75+21=96$, który jest niższy niż aktualne UB, a więc staje się ono nowym UB

#align(center)[*UB = 96*]

Aktualny stan kolejki
#align(center)[#ztable(columns: 2, format:(none,auto),
  [*Ścieżka*], [*LB*], 
  [0->3->1],[101],
  [0->1->2],[108],
  [0->2],[117]
)]
Krok 5: Wycinanie

Ponieważ uzyskaliśmy nowe UB analizujemy naszą kolejkę, a następnie wycinamy wszystkie drogi z LB większym od UB. 

Ponieważ wszystkie elementy są większe, kolejka zostaje pusta, a to oznacza, że uzyskaliśmy wynik optymalny:
#align(center)[*Ścieżka: 0 -> 3 -> 2 -> 1 -> 0; Koszt = 96*]

= Opis implementacji 
Przed przystąpieniem do wyjaśnienia implementacji należy wyjaśnić działanie dodatkowych elementów wykorzystywanych w głównych algorytmach:
+ Struktura *Node*
```cpp
struct Node {
    std::vector<int> path;     
    std::vector<bool> visited; 
    int level;                 
    int currentCost;           
    int lowerBound;            
};
```
Powyższa struktura wykorzystywana jest podczas algorytmów BnB do przechowywania informacji o częściowym rozwiązaniu w drzewie rozwiązań. Przechowuje ona kolejno:
- wektor reprezentujący dotychczasową ścieżkę rozwiązania 
- wektor przechowujący listę odwiedzonych miast
- informację na którym poziomie 
= Plan eksperymentów
= Warunki badawcze
= Wyniki eksperymentów
== Badanie wpływu rozmiaru problemu na długość wykonywania programu

== Badanie średniego błędu względnego algorytmów aproksymacyjnych

//  #figure(
// ztable(columns: 2,row-gutter: (2.2pt,auto), format:(none,auto),
//   [*Ilość wierzchołków N*], [*Średni błąd względny [%]*],
//   [10],[88.09],
//   [11],[101.88],
//   [12],[130.79],
//   [13],[146.89],
//   [14],[167.41],

// ), caption: "Średni błąd względny dla algorytmu losowego")
//  #figure(image("/sprawozdanie/RelativeErrors.png", width:100%),caption: [Średni błąd względny algorytmów aproksymacyjnych dla wybranych rozmiarów N.],supplement: [Wykres])

= Wnioski

= Literatura
#bibliography("bib.bib",title:none)