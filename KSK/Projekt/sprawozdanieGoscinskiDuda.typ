#set page(
  margin: 2.5cm,
)
#set text(lang: "pl")
#set page(header: context {
  if counter(page).get().first() > 1 [
    
    #h(1fr)
    Korporacyjne sieci komputerowe
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
  #text(size: 28pt, weight: "bold")[Korporacyjne sieci komputerowe] \ \
  #v(7cm)

  // --- Author section ---
  #text(size: 18pt)[
    #table(columns:(1fr,1fr),stroke:none,table.header(table.cell(colspan: 2)[Autorzy:]),[
Daniel Gościński 280878],[ Łukasz Duda 280916])//     Autorzy: \
//   Daniel Gościński 280878\
//   Łukasz Duda 280916\
//   Jakub Watała 281106\
//   Michał Górny 280888\
//   Krystian Zientara 280872
  ]
  #v(2cm)

  // --- Instructor section ---
  #text(size: 18pt)[Prowadzący: \
   dr inż. Arkadiusz Grzybowski
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
= Cel projektu
Projekt zakłada utworzenie rozległej sieci dla banku, uwzględniając położenie oddziałów banku. Głównym zadaniem projektu sieci jest zminimalizowanie kosztów dzierżawy kanałów transmisyjnych, oraz spełnienie założeń projektowych znajdujących się w *sekcji 2*.
= Założenia projektowe
== Struktura organizacyjna banku
Bank składa się z centrali oraz 5 oddziałów znajdujących się w miastach wojewódzkich. Lokalizacje działania banku prezentują się następująco:
#set list(marker: [--])
- Centrala: Wrocław
- Oddział wojewódzki nr.1: Bydgoszcz 
- Oddział wojewódzki nr.2: Rzeszów
- Oddział wojewódzki nr.3: Szczecin
- Oddział wojewódzki nr.4: Poznań
- Oddział wojewódzki nr.5: Olsztyn
W celach późniejszych obliczeń zakłada się odległości między miastami umieszczone w tabeli poniżej:

#figure(
table(columns: (1fr, 1fr, 1fr,1fr,1fr,1fr,1fr),column-gutter: (2.2pt,auto),row-gutter: (2.2pt,auto),
  [*Miasto*], [*Wrocław*], [*Bydgoszcz*], [*Rzeszów*], [*Szczecin*], [*Poznań*],[*Olsztyn*],

  [*Wrocław*], [0], [233.38], [370,70], [308,40], [143,84],[377,46],
  [*Bydgoszcz*], [233.38], [0], [440,54], [231,87], [108,25],[179,63],
  [*Rzeszów*], [370,70], [440,54], [0], [636,49], [440,82],[428,55],
  [*Szczecin*], [308,40], [231,87], [636,49], [0], [195,77],[393,05],
  [*Poznań*], [143,84], [108,25], [440,82], [195,77], [0],[282,68],
  [*Olsztyn*],[377,46], [179,63], [428,55], [393,05], [282,68],[0]
), caption: "Dystanse pomiędzy miastami oddziałów [km]")
== Wyposażenie oddziałów
Zarówno centrala jak i oddziały posiadają sieci lokalne wykorzystujące protokół TCP/IP oraz router służący jako przyłącze do sieci zewnętrznej.
== Założenia dotyczace ruchu sieciowego
Poniżej znajdują się dzienne natężenia ruchu podczas pracy Banku. Należy zaznaczyć, ze jeden dzień roboczy oznacz w tym przypadku 9 godzin pracy Banku:
- Odział wojewódzki - odział wojewódzki: 150MB (w jedną stronę)
- Odział wojewódzki - Centrala: 800MB (w obie strony łącznie)
== Wymagania dotyczace jakości sieci
W sieci rozległej zakłada się, że opóźnienie pakietu w sieci nie moze być większe od 0.7 s/pakietu. Równie ważne jest zapewnienie niezawodności sieci w postaci odporności na pojedynczą awarię węzła lub kanału.
== Założenia dotyczace łączy transmisyjnych
W projekcie w celach dzierżawy zakłada się wykorzystanie kanału cyfrowego o przepustowościach:
- 64 kbit/s
- 2 Mbit/s
- n x 64 kbit/s

Podczas obliczeń wykorzystywane będą poniższe cenniki dzierżawy kanałów cyfrowych:
#figure(
 
  table(
    columns: 7,
    align: center,

    [*Długość kanału*], [*Do 3 km*], [*3-20 km*], [*20-30 km*], [*30-50 km*], [*50-100 km*], [*>100 km*],

    [*Opłata stała*], [440], [580], [1952], [5600], [6400], [8000],
    [*Opłata za 1 km*], [340], [240], [176], [52], [29], [15],
  ), caption: [Opłaty miesięczne za dzierżawę kanału cyfrowego o przepustowości 64kbit/s]
)
\ \
#figure(
  
  table(
    columns: 7,
    align: center,

    [*Długość kanału*], [*Do 3 km*], [*3-20 km*], [*20-30 km*], [*30-50 km*], [*50-100 km*], [*100-200 km*],

    [*Opłata stała*], [8000], [12700], [19000], [24500], [24400], [56000],
    [*Opłata za 1 km*], [2440], [940], [625], [610], [450], [105],
  ),caption: [Opłaty miesięczne za dzierżawę kanału cyfrowego o przepustowości 2Mbit/s]
)

#figure(
  table(
    columns: 2,
    align: center,

    [*Przepustowość kanału*], [*Opłata*],

    [128 kbit/s], [2 x opłata za łącze 64 kbit/s x 0,80],
    [192 kbit/s], [3 x opłata za łącze 64 kbit/s x 0,75],
    [256 kbit/s], [4 x opłata za łącze 64 kbit/s x 0,70],
    [384 kbit/s], [6 x opłata za łącze 64 kbit/s x 0,65],
    [512 kbit/s], [8 x opłata za łącze 64 kbit/s x 0,60],
    [768 kbit/s], [12 x opłata za łącze 64 kbit/s x 0,55],
    [1024 kbit/s], [16 x opłata za łącze 64 kbit/s x 0,50],
  ),  caption: [Miesięczna opłata za dzierżawę kanałów cyfrowych o przepustowości n x 64 kbit/s]
)