#set page( 
 margin: 2.5cm,
)

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
  #text(size: 24pt)[Sprawozdanie z laboratorium 5 \ Grupa 1 Piątek 9:15 ]

  #v(7cm)

  // --- Author section ---
  #text(size: 18pt)[
    #table(columns:(1fr,1fr),stroke:none,table.header(table.cell(colspan: 2)[Autorzy:]),[
Daniel Gościński 280878],[ Łukasz Duda 280916],)//     Autorzy: \
//   Daniel Gościński 280878\
//   Łukasz Duda 280916\
//   Jakub Watała 281106\
//   Michał Górny 280888\
//   Krystian Zientara 280872
  ]
  #v(2cm)

  // --- Instructor section ---
  #text(size: 18pt)[Prowadzący: \
    dr inż. Przemysław Ryba
  ]
]
#pagebreak()
#set page(
  margin: 2.5cm,
)
#set page(margin:2cm)
#set text(size:14pt,hyphenate: false)
#set par(justify: true, spacing: 1em)
= Odpowiedzi na pytania
// #text(fill:green)[Vlan 1]\
== Część 3
=== Krok 2
==== Podpunkt B
*Wdróż i zweryfikuj EtherChannel między przełącznikami.\
Sprawdź, czy ustawienia trunk pozostały poprawne.\ *
Co oznacza port „Po1”?
#text(fill:green)[]\
=== Krok 3
*Ręcznie skonfiguruj interfejs trunk F0/5 na S1.*\
Co się stanie, jeśli G0/0/1 na R1 jest nieaktywny?\
#text(fill:green)[]\
== Część 5
=== Krok 1
*Wykonaj testy z PC-A.*
==== Podpunkt A
Ping z hosta PC-A do jego domyślnej bramy.
#text(fill:green)[]\
==== Podpunkt B
Ping z PC-A do PC-B.
#text(fill:green)[]\
==== Podpunkt C
Ping z PC-A do S2.
#text(fill:green)[]\
=== Krok 2
Wykonaj test z PC-B.
#text(fill:green)[]\
==== Podpunkt A
*Z wiersza polecenia na PC-B wykonaj tracert do adresu PC-A.*\
Wynik:\
#text(fill:green)[]\
Jakie pośrednie adresy IP są pokazane w wynikach?\
#text(fill:green)[]\