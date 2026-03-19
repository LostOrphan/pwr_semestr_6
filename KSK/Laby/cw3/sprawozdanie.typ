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
  #text(size: 24pt)[Sprawozdanie z laboratorium 3 \ Grupa 1 Piątek 9:15 ]

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
// #set heading(numbering: "1.")
= Odpowiedzi na pytania
// #text(fill:green)[Vlan 1]\
== Część 1
=== Krok 4
*Sprawdź, czy ping pomiedzy hostami PC kończą się powodzeniem.*\
Czy ping z PC-A osiągną PC-B?\
#text(fill:green)[]\
Czy ping z PC-A osiągną S1?\
#text(fill:green)[]\
Czy ping z PC-B osiągną S2?\
#text(fill:green)[]\
Czy ping z S1 osiągną S2?\
#text(fill:green)[]\
== Część 2
=== Krok 1
==== Podpunkt C
*Wydaj polecenie show vlan brief, aby wyświetlić listę sieci VLAN na S1.*\
Która to domyślna sieć VLAN?\
#text(fill:green)[Vlan 1]\
Jakie porty są przypisane do domyślnej sieci VLAN?\
#text(fill:green)[]\
=== Krok 2
==== Podpunkt C
*Wykonaj komendę show ip interface brief.*\
Jaki jest status VLAN 99? Wyjaśnij.\
#text(fill:green)[]\
==== Podpunkt G
*Użyj polecenia show vlan brief, aby sprawdzić, czy sieci VLAN są przypisane do odpowiednich
interfejsów*\
Czy ping z S1 osiągnie S2? Wyjaśnij.\
#text(fill:green)[]\
Czy ping z PC-A osiągnie PC-B? Wyjaśnij.\
#text(fill:green)[]\
== Część 3
=== Krok 2
==== Podpunkt B
*Sprawdź, czy została dokonana zmiana sieci VLAN.*\
Z którym VLAN jest teraz powiązany F0/24?
#text(fill:green)[]\
=== Krok 3
==== Podpunkt B
*Sprawdź, czy nowa sieć VLAN jest wyświetlana w tabeli VLAN.*\
Jaka jest domyślna nazwa sieci VLAN 30?
#text(fill:green)[]\
==== Podpunkt D
*Wydaj polecenie show vlan brief. F0/24 został przypisany do VLAN 30.*\
Po usunięciu VLAN 30 z bazy danych VLAN, do jakiego VLAN jest przypisany port F0/24? Co dzieje się z
ruchem przeznaczonym do hosta dołączonego do F0/24?
#text(fill:green)[]\
==== Podpunkt F
*Wydaj polecenie show vlan brief, aby określić przypisanie sieci VLAN dla F0/24.*\
Do której VLAN jest przypisany F0/24?
#text(fill:green)[]\
== Część 4
=== Krok 1
==== Podpunkt D
*Sprawdź, czy ruch VLAN przechodzi przez interfejs trunk F0/1.*\
Czy ping z S1 osiągną S2?\
#text(fill:green)[]\
Czy ping z PC-A osiągną PC-B?\
#text(fill:green)[]\
Czy ping z PC-A osiągną S1?\
#text(fill:green)[]\
Czy ping z PC-B osiągną S2?\
#text(fill:green)[]\
=== Krok 2
==== Podpunkt D
*Dlaczego chcesz ręcznie skonfigurować interfejs do trybu trunk zamiast używać DTP?*\
#text(fill:green)[]\
*Dlaczego chcesz zmienić natywną sieć VLAN na bagażniku?*\
#text(fill:green)[]\
== Część 5
=== Krok 2
==== Podpunkt D
*Aby zainicjować przełącznik z powrotem do ustawień domyślnych, jakie inne polecenia są potrzebne?*\
#text(fill:green)[]\
== Pytania refleksyjne
1. *Co jest potrzebne, aby umożliwić hostom w VLAN 10 komunikowanie się z hostami w sieci VLAN 99?*\
#text(fill:green)[]\
2.* Jakie są podstawowe korzyści, które organizacja może otrzymać poprzez efektywne wykorzystanie sieci VLAN*\
#text(fill:green)[]\