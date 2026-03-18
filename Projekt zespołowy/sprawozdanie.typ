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
#text(size:18pt)[
#outline(title: text(size: 42pt, weight: "bold")[Spis treści],
        )]
#pagebreak()
#set page(margin:2cm)
#set text(size:14pt,hyphenate: false)
#set par(justify: true, first-line-indent:(amount:2em,all:true), spacing: 1em)
= Temat i cel projektu
Tematem projektu jest aplikacja webowa, umożliwiająca użytkownikom na kupno oraz sprzedaż produktów.

Celem projektu jest utworzenie działającej aplikacji webowej poprzez współpracę większej ilości osób w grupie projektowej. Dodatkowym celem realizacji projektu jest nabycie przez zespół umiejętności pracy w grupie, wykonywania przydzielonych im zadań, tworzenia i trzymania się harmonogramu pracy, komunikacji wewnątrz zespołu oraz zdolności reagowania na wydarzenia nieplanowane w trakcie wykonywania projektu.

= Przegląd istniejących rozwiązań w obszarze problemu
Analizując dzisiejszy rynek platform typu marketplace w internecie możemy znaleźć wiele różnych stron, skupiających się na lokalnych, krajowych lub międzynarodowych rynkach. Rynki można również podzielić na rynki *wertykalne* oraz *horyzontalne*, gdzie pierwsze skupiają się na konkretnym rodzaju produktu, zaś drugie rynki posiadają w swojej ofercie szeroką gamę kategorii produktów. 

Na polskim rynku funkcjonuje kilka dużych platform, które różnią się od siebie sposobem działania, specjalizacją oraz docelową grupą użytkowników.

Jedną z największych takich platform jest *Allegro*, który umożliwia firmom (lub osobom prywatnym pod warunkiem działalności okazjonalnej, niezwiązanej z regularnym zarobkiem) sprzedaż swoich produktów w wielu kategoriach, takich jak elektronika czy artykuły domowe. Umożliwiona jest sprzedaż zarówno produktów nowych jak i używanych. Platforma posiada rozbudowany system płatności, ochrony kupującego przed możliwymi oszustwami/uszkodzeniami produktu, oraz rozbudowaną logistykę dostaw.

Drugim znaczącym graczem na polskim rynku jest *OLX*, który w porównaniu do Allegro skupia się na możliwości wystawiania ogłoszeń lokalnych i sprzedaży pomiędzy użytkownikami. Cechą szczególną tej platformy jest możliwość komunikacji pomiędzy sprzedającym a kupującym, oraz możliwość odbioru osobistego towaru. Oprócz towarów strona umożliwia również wystawianie ofert pracy oraz wykonania usług (np. usług remontowych).

Ostatnim podmiotem analizy jest *Vinted*. Jest to przykład platformy skupiającej się na bardzo specyficznej kategorii produktów - odzieży oraz akcesoriów używanych. Prosty interfejs użytkownika oraz spełnienie bardzo konkretnej potrzeby użytkowników pozwolił platformie na uzyskanie dużej ilości użytkowników.

Analizując powyższe przykłady oraz inne niewspomniane wcześniej można zauważyć zróżnicowanie rozwiązań, które niezależnie od swojej niszy oraz metod działania nadal uzyskują swoją renomę. Można jednak wyznaczyć cechy wspólne wszystkich stron: jasno określony rynek produktów, możliwość wystawiania ogłoszeń, system komunikacji między użytkownikiem a sprzedającym, duża ilość możliwości transportu produktu. Rozwiązania te będą punktem odniesienia do utworzenia własnej aplikacji webowej.
= Analiza wymagań użytkownika
Po analizie istniejących rozwiązań zdecydowano się, aby projektowana aplikacja pozwalała użytkownikom na sprzedaż różnych przedmiotów, bez szytwno określonego zakresu produktów. Sprzedaż skupiać się będzie na transakcjach lokalnych, gdzie kupujący ma możliwość bezpośredniej komunikacji ze sprzedającym w modelu zbliżonym do systemu w serwisie OLX.

Użytkownicy korzystający z systemu będą mieli możliwość rejestracji oraz zalogowania na konto użytkownika, które będzie wymagane w celu korzystania z pełnej funkcjonalności aplikacji. Następnie użytkownicy mogą wyszukiwać istniejacych ofert sprzedaży korzystając z wyszukiwarki oraz systemu filtrów, lub wystawić na sprzedaż własny produkt wykorzystując dostępny kreator. W przypadku chęci kupienia wybranego produktu, kupujący może kupić produkt bezpośrednio (jeśli jest to sprzedaż bezpośrednia) lub skontaktować się z kupującym w celu ustalenia warunków sprzedaży wykorzystując do tego czat tekstowy.

Zakłada się, że system będzie prosty oraz intuicyjny dla użytkowników systemu. Używanie aplikacji nie powinno sprawiać problemów użytkownikom, a interfejs powinien być prosty i przejrzysty, umożliwiając szybkie wykonywanie podstawowych operacji.
= Wymagania funkcjonalne i niefunkcjonalne
== Wymagania funkcjonalne
+ Rejestracja użytkownika - System powinien umożliwiać utworzenie konta użytkownika przy pomocy formularza rejestracyjengo
+ Logowanie uzytkownika - System powinien umożliwiać zalogowanie użytkownika do konta przy użyciu odpowiednich danych uwierzytelniających
+ Zarządzenie kontem użytkownika - Użytkownik powinien mieć możliwość przeglądania oraz edytowania informacji o swoim koncie
+ Dodawanie ogłoszeń - Użytkownik powinien mieć możliwość utworzenia ogłoszenia sprzedaży poprzez formularz utworzenia ogłoszenia
+ Edycja i usuwanie ogłoszeń - Użytkownik powinien mieć możliwość edytowania oraz usuwania własnych ogłoszeń
+ Przeglądanie ogłoszeń - Użytkownik powinien mieć możliwość przeglądania dostępnych ofert sprzedaży utworzonych przez innych użytkowników
+ Wyszukiwanie ogłoszeń - Użytkownik powinien mieć możliwość wyszukania oferty za pomocy wyszukiwarki tekstowej
+ Filtrowanie ogłoszeń - Użytkownik powinien mieć możliwość filtrowania ogłoszeń według zadanych kryteriów (np. minimalna i maksymalna cena, kategoria, lokalizacja)
+ Wyświetlanie szczegółów ogłoszenia - Użytkownik powinien mieć możliwość wyświetlenia szczegółowych informacji o wybranej ofercie sprzedaży
+ Komunikacja pomiędzy kupującym a sprzedającym - Kupujący powinien mieć możliwość skontaktowania się ze sprzedającym za pomocy czatu tekstowego
+ Opcja zakupu bezpośredniego - Kupujący powinien mieć możliwość kupna produktu bezpośrednio, jeśli dana oferta posiada taką możliwość
== Wymagania niefunkcjonalne
+ Przejrzystość interfejsu - Interfejs użytkownika powinien być intuicyjny i prosty w obsłudze
+ Dostępność systemu - System powinien być dostępny dla użytkowników przez przeglądarkę internetową
+ Bezpieczeństwo danych - Dane użytkownika powinny być odpowiednio zabezpieczone, a dostęp do konta powinien wymagać uwierzytelnienia
+ Niezawodność systemu - Aplikacja powinna działać stabilnie i minimalizować możliwość występowania błędów
= Założenia projektowe
Projektowana aplikacja będzie platformą typu marketplace umożliwiającą użytkownikom na sprzedaż i kupno przedmiotów różnych kategorii. System koncentrować się będzie na transakcjach lokalnych, umożliwiając bezpośrednią komunikację miedzy dwiema stronami transakcji. Aplikacja będzie wzorować się na istniejących popularnych serwisach internetowych jak np. OLX. 

Zakres funkcjonalności opisany został w *sekcji 4*, zawiera on między innymi rejestrację kont, wystawianie ogłoszeń czy wykorzystanie czatu tekstowego do komunikacji ze sprzedającym. 

Aplikacja zaprojektowana będzie w architekturze klient-serwer, gdzie frontend obsługiwać będzie interfejs użytkownika, zaś backend będzie odpowiedzialny za logikę aplikacji, przetwarzanie danych oraz komunikację z bazą danych. Wymiana danych między endami będzie się odbywać za pomocą API. 

Ze względu na doświadczenie zespołu, jak i charakteru pracy aplikacja będzie miała charakter demonstracyjny, co oznacza, że nie wszystkie funkcje będą zaimplementowane (jak np. system obsługi transakcji czy system wsparcia użytkownika). Celem projektu będzie utworzenie systemu z możliwie kompletną listą funkcjonalności określone z *sekcji 4*.
= Specyfikacja techniczna
Projektowana aplikacja w architekturze klient-serwer wykorzystywać będzie frontend oraz backend w postaci komponentów, które będą komunikować się ze sobą przy pomocy API. Wykorzystane zostaną następujące technologie:
+ Baza danych - *PostgreSQL*
+ Backend - *Django* wraz z *Django REST Framework* jako API
+ Frontend - *React*
= Schemat bazy danych
= Analiza ryzyka - scenariusze awaryjne i sposoby monitorowania ryzyka
= Tryb współpracy
Zespół projektowy został podzielony po wspólnych ustaleniach zgodnie z~preferencjami:
+ Daniel Gościński: Lider zespołu, back-end, sprawozdanie
+ Krystian Zientara: back-end
+ Jakub Watała: front-end
+ Łukasz Duda: front-end
+ Michał Górny: baza danych
Pomimo podziału nie zakłada się ról jako absolutnych, w przypadkach szczególnych przewiduje się tymczasową zmianę ról w celu wsparcia reszty osób.

Komunikacja grupy odbywać się będzie poprzez platformę *Discord*, gdzie członkowie projektu będą komunikować się ze sobą, oraz zgłaszać będą swoje postępy lub występujące przeszkody.

Kod aplikacji będzie znajdował się w repozytorium na *Githubie*.

Projekt zostanie podzielony na etapy, gdzie każdy etap rozpoczynać się będzie od określenia potrzeb, celów oraz możliwych ograniczeń. Etap kończyć się będzie spotkaniem podsumowującym, w którym zespół będzie podsumowywał powierzone zadania.

= Przyjęte sposoby organizacji pracy i komunikacji w zespole
= Harmonogram pracy 
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

= Repozytorium
#show link: underline
#show link: set text(blue)
#link("https://github.com/LostOrphan/PWR-Projekt-Zespolowy-Web-Marketplace")[Repozytorium aplikacji znajduje się na Githubie.]
= Deklaracja wykorzystanych narzędzi AI