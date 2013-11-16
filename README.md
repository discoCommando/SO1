ZADANIE ZALICZENIOWE NR 1

Należy stworzyć pierścień składający się z N+1 procesów (1 zarządca + N wykonawców), które będą wykonywać obliczanie wartości wyrażenia arytmetycznego zapisanego w ONP (Odwrotna Notacja Polska).

Rozwiązane powinno zawierać dwa programy: program zarządcy o nazwie 'manager' i program wykonawcy o nazwie 'executor'.

Użytkownik uruchamia program zarządcy z parametrami określającymi: liczbę wykonawców (N), nazwę pliku z danymi i nazwę pliku zawierającego wyniki.

Zarówno plik z danymi jak też plik wynikowy powinny znajdować się w katalogu o nazwie DATA, który jest podkatalogiem katalogu zawierającego programy 'manager' i 'executor'.

Obliczanie wartości wyrażenia

Zakładamy, że wyrażenia, których wartość będziemy obliczać zawierają stałe liczbowe o wartościach całkowitych oraz operatory: + (dodawanie), - (odejmowanie), * (mnożenie) oraz / (dzielenie całkowite).

W poniższym przykładzie wyrażenia poszczególne jego elementy oddzielone są znakiem odstępu.

Dla wyrażenia:

2 7 + 3 / 14 3 - 4 * + 2 /

obliczona wartość wynosi 23.

Każdy z wykonawców realizuje jeden krok procesu obliczania.

Polega on na odnalezieniu w otrzymanym od poprzedniego procesu wyrażeniu pierwszego z lewej symbolu operatora i zastąpieniu dwóch stałych liczbowych występujących bezpośrednio na lewo od niego wynikiem operacji określonej tym operatorem. Należy przy tym zwracać uwagę na kolejnośc argumentów wykonywanych operacji. Jeśli w wyrażeniu występuje napis: <stała1> <stała2> <operator>, to obliczenie ma postać: <stała1> <operator> <stała2>.

Dla powyższego wyrażenia przykładowego proces obliczeń wygląda następująco:

2 7 + 3 / 14 3 - 4 * + 2 /

9 3 / 14 3 - 4 * + 2 /

3 14 3 - 4 * + 2 /

3 11 4 * + 2 /

3 44 + 2 /

47 2 /

23

Postać pliku z danymi

Plik z danymi jest plikiem tekstowym zawierającym w pierwszym wierszu liczbę całkowitą W określającą liczbę wyrażeń do obliczenia. W kolejnych W wierszach zapisane są wyrażenia, w każdym wierszu jedno.

Wyrażenia zawierają stałe liczbowe o wartościach całkowitych oraz operatory: + (dodawanie), - (odejmowanie), * (mnożenie) oraz / (dzielenie całkowite).

Poszczególne elementy wyrażeń oddzielone są pojenczym znakiem odstępu.

Można założyć, że zawarte w pliku wyrażenia są poprawnie zbudowane.

Postać pliku wynikowego (wyniki)

Plik wynikowy powinien zawierać obliczone wartości wyrażen, po jednym w każdym wierszu. Każda wartość powinna być poprzedzona numerem wiersza, w którym zapisane było wyrażenie w pliku z danymi, dwukropkiem i pojedynczym odstępem. Zakładamy, że wiersze w pliku z danymi są numerowane od zera.

Przykładowy wiersz pliku wynikowego:

1: 23

Zarządca (manager)

Zarządca tworzy pierścień składający się z niego i N wykonawców.

Z pliku z danymi wczytuje pierwszy wiersz, zawierający liczbę określającą liczbę kolejnych wierszy w tym pliku.

Następnie z kolejnych wierszy pobiera wyrażenia, których wartości mają być obliczone i wysyła je do najbliższego sąsiada (patrz: schemat komunikacji) opatrzone numerem wiersza, w którym były zapisane w pliku z danymi.

Następnie odbiera od ostatniego wykonawcy przekazywane przez niego komunikaty.

Jeśli komunikat zawiera kompletnie wyliczoną wartość wyrażenia, zapisuje otrzymany wynik w pliku wynikowym.

Jeśli w komunikacie zawarte jest wyrażenie, którego wartość nie jest jeszcze kompletnie wyliczona, przekazuje go najbliższemu (pierwszemu) wykonawcy.

Po otrzymaniu wszystkich wyników zarządca inicjuje likwidację pierścienia i kończy pracę po zakończeniu działania wszystkich wykonawców.

Wykonawca (executor)

Działanie wykonawcy zależy od zawartości odebranego od swego poprzednika komunikatu.

Jeśli zawiera on wyrażenie, którego obliczanie nie zostało jeszcze zakończone, wykonuje jeden krok obliczeń i przesyła uzyskany wynik do swojego bezpośredniego następcy.

Jeśłi zawiera on całkowicie wyliczoną wartośc wyrażenia, przekazuje komunikat swojemu bezpośredniemu następcy bez zmian.

Jeśłi zawiera on komunikat o zakończeniu dzialania, przekazuje go następcy i kończy pracę.

Schemat komunikacji

Każdy z procesów tworzących pierścień połączony jest dwoma łączami nienazwanymi ze swoimi najbliższymi sąsiadami. Łącza te powinny używać standardowych deskryptorów wyjściowych i wejściowych. Zapis do łącza powinien odbywać się za pomocą standardowego deskryptora wyjściowego, a odczyt - za pomocą standardowe deskryptora wejściowego.
Komunikacja odbywa się jednokierunkowo.

Po otrzymaniu wszystkich wyników obliczeń, proces zarządcy przekazuje swojemu sąsiadowi znacznik końca działania.

Po otrzymaniu takiego znacznika proces wykonawcy przekazuje go dalej i kończy pracę.

W chwili odebrania tego znacznika przez zarządcę powinien on zaczekać na zakończenie działania wszystkich wykonawców i zakończyć pracę.

Pozostałe informacje

Rozwiązania (tylko Makefile, pliki źródłowe i opcjonalny plik z opisem) należy nadsyłać za pomoca skryptu submit na adres solab@mimuw.edu.pl ze swojego konta na komputerze students.

Ostateczny termin nadsyłania rozwiązań to 20 listopada 2013 r , 23:59

W przypadku wątpliwości można zadać pytanie autorowi zadania K. Szafranowi. Przed zadaniem pytania warto sprawdzić, czy odpowiedź na nie nie pojawiła się na liście często zadawanych pytań.