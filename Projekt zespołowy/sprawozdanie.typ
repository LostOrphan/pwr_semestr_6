#set page(
  margin: 2.5cm,
)
#set page(header: context {
  if counter(page).get().first() > 1 [
    
    #h(1fr)
    Projekt zespołowy
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
  #text(size: 28pt, weight: "bold")[Projekt zespołowy] \ \
  #text(size: 24pt)[Aplikacja webowa typu marketplace do publikowania ogłoszeń]
  #v(7cm)

  // --- Author section ---
  #text(size: 18pt)[
    #table(columns:(1fr,1fr),stroke:none,table.header(table.cell(colspan: 2)[Autorzy:]),[
Daniel Gościński 280878],[ Łukasz Duda 280916],
  [Jakub Watała 281106],[Michał Górny 280888],
  [Krystian Zientara 280872])
//     Autorzy: \
//   Daniel Gościński 280878\
//   Łukasz Duda 280916\
//   Jakub Watała 281106\
//   Michał Górny 280888\
//   Krystian Zientara 280872
  ]
  #v(2cm)

  // --- Instructor section ---
  #text(size: 18pt)[Prowadzący: \
    mgr inż. Weronika Borek-Marciniec
  ]
]
#pagebreak()
#set page(
  margin: 2.5cm,
)

#set heading(numbering: "1.")
#text(size:20pt)[
#outline(title: text(size: 42pt, weight: "bold")[Spis treści],
        )]
#pagebreak()
#set page(margin:2cm)
#set text(size:14pt,hyphenate: false)
#set par(justify: true, first-line-indent:(amount:2em,all:true), spacing: 1em)
= Temat i cel projektu
Tematem projektu jest aplikacja webowa, umożliwiająca użytkownikom na kupno oraz sprzedaż produktów.

Celem projektu jest utworzenie działającej aplikacji webowej poprzez współpracę większej ilości osób w grupie projektowej. Dodatkowym celem realizacji projektu jest nabycie przez zespół umiejętności pracy w grupie, wykonywania przydzielonych im zadań, tworzenia i trzymania się harmonogramu pracy, komunikacji wewnątrz zespołu oraz zdolności reagowania na wydarzenia nieplanowane w trakcie wykonywania projektu.
= Tryb współpracy
Zespół projektowy został podzielony po wspólnych ustaleniach zgodnie z~preferencjami:
+ Daniel Gościński: Lider zespołu, back-end, sprawozdanie
+ Krystian Zientara: back-end
+ Jakub Watała: front-end
+ Łukasz Duda: front-end
+ Michał Górny: baza danych
Pomimo podziału nie zakłada się ról jako absolutnych, w przypadkach szczególnych przewiduje się tymczasową zmianę ról w celu wsparcia reszty osób.

Komunikacja grupy odbywać się będzie poprzez platformę *Discord*, gdzie członkowie projektu będą komunikować się ze sobą, oraz zgłaszać będą swoje postępy lub występujące przeszkody.

Kod aplikacji będzie znajdował się w repozytorium znajdującym się na *Githubie*.

Projekt zostanie podzielony na etapy, gdzie każdy etap rozpoczynać się będzie od określenia potrzeb, celów oraz możliwych ograniczeń. Etap kończyć się będzie spotkaniem podsumowującym, w którym zespół będzie podsumowywał powierzone zadania.
= Harmonogram pracy 
//prowadzący czy prowadząca xd?
Zakłada się, że datą ukończenia projektu jest 22.06.2026, który jest nieprzekraczalną datą, w który projekt musi zostać ukończony. Kolejnym odgórnie narzuconym terminem w harmonogramie jest 11.05.2026, w którym zespół odbędzie spotkanie z opiekunem projektu w celu ocenienia realizacji projektu

Zakłada się również comiesięczne raporty z pracy nad projektem. Zespół zakłada wykonywanie tych spotkań możliwie na początku każdego miesiąca.

Poniżej został utworzony wstepny harmonogram projektu. Zakłada się możliwe zmiany/rozbudowę harmonogramu po ukończeniu pierwszego etapu projektu.
#set par(justify: true, first-line-indent:0em,hanging-indent: 1em, spacing:0.5em)
#text(size:18pt)[*Harmonogram*]
#v(0.5cm)

Etap 1. Analiza projektu, szczegółowy podział obowiązków.\ Termin ukończenia etapu: *16.03.2026*

Etap 2. Projekt architektury i bazy danych.\ Termin ukończenia etapu: *30.03.2026*

Etap 3. Implementacja podstawowych funkcji.\ Termin ukończenia etapu: *27.04.2026*

Ocena postępów w połowie semestru\
    Termin: *11.05.2026*

Etap 4. Rozbudowa funkcjonalności.\ Termin ukończenia etapu: *26.05.2026*

Etap 5. Testowanie aplikacji.\ Termin ukończenia etapu: *08.06.2026*

Etap 6. Poprawki.\ Termin ukończenia etapu: *15.06.2026*

Etap 7. Dokumentacja i prezentacja.\ Termin ukończenia etapu:  *22.06.2026*
