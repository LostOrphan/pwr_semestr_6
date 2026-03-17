#set page(
  margin: 2.5cm,
)
#set page(header: context {
  if counter(page).get().first() > 1 [
    
    #h(1fr)
    Projektowanie Usług Internetowych
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
  #text(size: 28pt, weight: "bold")[Projektowanie Usług Internetowych] \ \
  #text(size: 24pt)[Aplikacja webowa do śledzenia kursów walut]
  #v(7cm)

  // --- Author section ---
  #text(size: 18pt)[
    #table(columns:(1fr,1fr),stroke:none,table.header(table.cell(colspan: 2)[Autorzy:]),[
Daniel Gościński 280878],[ Łukasz Duda 280916],
  [Michał Górny 280888],
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
    inż. Dominik Ciura
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
= Opis aplikacji
Aplikacja webowa agreguje dane wykorzystując informacje o kursach walut pozyskanych z API Narodowego Banku Polskiego, umożliwiając użytkownikom na przeglądanie kursów walut.
= Wymagania funkcjonalne
+ Rejestracja i logowanie użytkowników
+ Możliwość wyszukiwania kursów walut
+ Przeglądanie historii kursu w zadanym zakresie dat wraz z odpowiednią wizualizacją danych
+ Możliwość dodania kursu do obserwowanych, w celu szybszej możliwości podejrzenia kursu
+ Możliwość usunięcia kursu z obserwowanych
+ Możliwość porównywania różnych kursów ze sobą
+ Możliwość przeliczenia wybranego kursu dla zadanej kwoty
+ Możliwość wyboru motywu kolorystycznego aplikacji
