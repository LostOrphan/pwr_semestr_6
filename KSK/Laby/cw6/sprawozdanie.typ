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
  #text(size: 24pt)[Sprawozdanie z laboratorium 6 \ Grupa 1 Piątek 9:15 ]

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
= Tabela adresowania
// Podsieć A (58 hostów) maska /26 (255.255.255.192) 192.168.1.1 – 192.168.1.62
// Podsieć B (28 hostów) maska /27 (255.255.255.224) 192.168.1.65 – 192.168.1.94
// Podsieć C (12 hostów) maska /28 (255.255.255.240) 192.168.1.97 – 192.168.1.110
#table(
  columns: 5,
  align: left + horizon,
[*Urządzenie*],[*Interfejs*],[*Adres IP*],[*Maksa podsieci*],[*Brama domyślna*],
[R1],
[g/0/0/0],
[10.0.0.1],
[255.255.255.252],
[nd.],
[],
[g/0/0/1],
[nd.],
[nd.],
[nd.],
[],
[g/0/0/1.100],
[#text(fill:green)[192.168.1.1]],
[#text(fill:green)[255.255.255.192]],
[nd.],
[],
[g/0/0/1.200],
[#text(fill:green)[192.168.1.65]],
[#text(fill:green)[255.255.255.224]],
[nd],
[],
[g/0/0/1.1000],
[nd.],
[nd.],
[nd],
[R2],
[g0/0/0],
[10.0.0.2],
[255.255.255.252],
[nd.],
[],
[g0/0/1],
[#text(fill:green)[192.168.1.97]],
[#text(fill:green)[255.255.255.240]],
[nd.],
[S1],
[VLAN 200],
[#text(fill:green)[192.168.1.2]],
[#text(fill:green)[255.255.255.192]],
[#text(fill:green)[192.168.1.1]],
[S2],
[VLAN 1],
[#text(fill:green)[192.168.1.66]],
[#text(fill:green)[255.255.255.254]],
[#text(fill:green)[192.168.1.65]],
[PC-A],
[karta sieciowa],
[DHCP],
[DHCP],
[DHCP],
[PC-B],
[karta sieciowa],
[DHCP],
[DHCP],
[DHCP],
)
= Odpowiedzi na pytania
// #text(fill:green)[Vlan 1]\
== Część 1
=== Krok 8
==== Podpunkt b
*Sprawdź, czy sieci VLAN są przypisane do odpowiednich interfejsów.*\
Dlaczego interfejs F0/5 jest wymieniony w VLAN 1?\
#text(fill:green)[]\
//Bo:
// trunk domyślnie należy do VLAN 1,
// dopiero konfiguracja trunk zmienia jego zachowanie.
=== Krok 9
==== Podpunkt e
*Zweryfikuj status łącza trunk.*\
W tym momencie jaki adres IP miałby komputer, gdyby były podłączone do sieci za pomocą DHCP?\
#text(fill:green)[]\
//ŻADEN (0.0.0.0)
// Bo:
// DHCP jeszcze NIE jest skonfigurowany
