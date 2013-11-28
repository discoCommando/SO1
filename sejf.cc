//#include <iostream>
//#include <string>
//#include <cstdint>
//#include <limits> //numeric_limits
//#include <utility> //swap
#include "sejf.h"
#include <cassert>
#include <cstdlib>
#include <climits>
#include <sstream>

using namespace std;

Sejf::Sejf(const string napis, const size_t dostepy)
	: tajny_napis (napis)
	, liczba_dostepow (dostepy)
	, stan_sejfu (OK)
	, moj_kontroler(&stan_sejfu, &liczba_dostepow)
	{
	}
Sejf::Sejf(const Sejf&) = delete;
Sejf& Sejf::operator=(const Sejf&) = delete;
Sejf& Sejf::operator+=(size_t modyfikator)
	{
	if(modyfikator<=max_liczba_dostepow-liczba_dostepow)
		liczba_dostepow += modyfikator;
	if(stan_sejfu != WLAMANIE)
		stan_sejfu = MANIPULACJA;
	return *this;
	}
Sejf& Sejf::operator-=(size_t modyfikator)
	{
	if(liczba_dostepow >= modyfikator)
		this -> liczba_dostepow -= modyfikator;
	if(stan_sejfu != WLAMANIE)
		stan_sejfu = MANIPULACJA;
	return *this;
	}
Sejf& Sejf::operator*=(size_t modyfikator)
	{
	if((modyfikator<=(max_liczba_dostepow%liczba_dostepow)) && (liczba_dostepow<=(max_liczba_dostepow%modyfikator)))
		liczba_dostepow *= modyfikator;
	if(stan_sejfu != WLAMANIE)
		stan_sejfu = MANIPULACJA;
	return *this;
	}
int16_t Sejf::operator[](rozmiar_napisu numer_skrytki)
	{
	int16_t zawartosc_skrytki = -1;
	if(numer_skrytki <= tajny_napis.size())
		{
		if(liczba_dostepow>0)
			{
			--liczba_dostepow;
			zawartosc_skrytki = (int16_t)tajny_napis[numer_skrytki];
			}
		else
			{
			stan_sejfu = WLAMANIE;
			}
		}
	return zawartosc_skrytki;
	}
Kontroler& Sejf::kontroler()
	{
	return moj_kontroler;
	}
Kontroler const& Sejf::kontroler() const
	{
	return moj_kontroler;
	}
Sejf::~Sejf()
	{
	}

void pobierz(Sejf &se, const string &s, bool uda_sie = true) {
    size_t sz = s.length();
    size_t pos = rand() % sz;
    int16_t ch = se[pos];
//    cout << pos << " " << sz << " " << (int)s[pos] <<  " " << (int)ch << endl;
    if(uda_sie) {
        assert((char)ch == s[pos]);
    } else {
        assert(ch == -1);
    }
}

void testuj(Sejf &se, unsigned int ile, const string &s) {
    for(unsigned int i = 0; i < ile; i++) {
        assert(se.kontroler());
        pobierz(se, s);
    }
    assert(!se.kontroler());
    int16_t ch = se[rand() % s.length()];
    assert(ch == -1);
}


void testuj_liczbe(unsigned int ile, const string &s = "rybakot") {
    cout << "Testuje liczbe " << ile << endl;
    Sejf se(s, ile);
    testuj(se, ile, s);
}

void testy_liczb() {
    cout << "Testy liczb" << endl;
    testuj_liczbe(0);
    testuj_liczbe(1);
    testuj_liczbe(2);
    testuj_liczbe(3);
    testuj_liczbe(10);
    testuj_liczbe(100);
    testuj_liczbe(10000);
    testuj_liczbe(1000000);

//    testuj_liczbe(-1); // Ciekawe, co tutaj się dzieje?
//    testuj_liczbe(-2000000022); // A tutaj?
}

void testuj_42(const string &s = "kotopies") {
    cout << "Testuje domyslne 42" << endl;
    Sejf se(s);
    testuj(se, 42, s);
}

void testuj_pusty() {
    cout << "Test pustego napisu" << endl;
    Sejf se("", 1);
    assert(se.kontroler());
    int16_t ch = se[0];
    assert(se.kontroler());
    assert(ch == -1);
    ch = se[0];
    assert(ch == -1);
    assert(se.kontroler());
    se -= 1;
    assert(!se.kontroler());
}

void testuj_operatory(const string &s = "piesokotokot") {
    cout << "Testy operatorow" << endl;
    Sejf se(s, 10); // 10
    pobierz(se, s); // 9
    se *= 3; // 27
    for(int i = 0; i < 26; i++) pobierz(se, s); // 1
    assert(se.kontroler());
    se += 6; // 7
    se -= 6; // 1
    pobierz(se, s);
    assert(!se.kontroler());
    int16_t ch = se[0];
    assert(!se.kontroler());
    assert(ch == -1);
} 
    
void testuj_operatory_zdradliwe(const string &s = "ryboplazokon") {
    cout << "Testy \"ZDRADA\"" << endl;
    Sejf se(s, 10); // 10
    se *= -1;
    assert(se.kontroler());

    // Zakładam, że wtedy nic się nie dzieje (bo byłby overflow)
    // Ale chyba to nie jest jedyne sensowne założenie
    // W każdym razie jest przynajmniej jasność co do zmniejszania o zbyt dużo
    //
    /* Czy po wykonaniu operacji -= mamy zmniejszyć ilość dostępów o tyle o 
     * ile jest możliwe póki nie dojdziemy do 0 czy jeśli dostajemy rozkaz 
     * zmniejszenia o więcej niż możemy to nic nie robimy?
     
    Przejdź do wiadomości wyżej („parent”) | Odpowiedz
    Obraz Maciej Zielenkiewicz
    Odp: Zadanie 3
    Maciej Zielenkiewicz w dniu Thursday, 7 November 2013, 15:32 napisał(a)
     

    Jeżeli nie jest możliwe zmniejszenie liczby dostępów o żądaną wartość to nic nie robimy.
*/
    for(int i = 0; i < 10; i++) pobierz(se, s);
    assert(!se.kontroler());

    Sejf se2(s, 999);
    se2 += -1;
    for(int i = 0; i < 999; i++) pobierz(se2, s);
    assert(!se2.kontroler());

    Sejf se3(s, 11);
    se3 -= -1;
    for(int i = 0; i < 11; i++) pobierz(se3, s);
    assert(!se3.kontroler());
} 

void testuj_kontroler() {
    cout << "Testy kontrolera" << endl;
    string s = "potworpieskomysz";
    Sejf se(s, 15);
    auto k = se.kontroler();
    stringstream ss;
    ss << k;
    assert(ss.str() == "OK\n");
    for(int i = 0; i < 15; i++) {
        pobierz(se, s);
        ss.str("");
        ss << k;
        assert(ss.str() == "OK\n");
    }
    se += 10;
    ss.str("");
    ss << k;
    assert(ss.str() == "ALARM: ZMANIPULOWANY\n");
    for(int i = 0; i < 10; i++) {
        pobierz(se, s);
        ss.str("");
        ss << k;
        assert(ss.str() == "ALARM: ZMANIPULOWANY\n");
    }
    pobierz(se, s, false);
    ss.str("");
    ss << k;
    se += 10;
    assert(ss.str() == "ALARM: WLAMANIE\n");
    for(int i = 0; i < 10; i++) {
        pobierz(se, s);
        ss.str("");
        ss << k;
        assert(ss.str() == "ALARM: WLAMANIE\n");
    }
    pobierz(se, s, false);
}

void testy_dzikie_z_palca() {
    cout << "Testy \"Dzikosc serca\"" << endl;    
    Sejf s1("BezdroznyWedroiecDzisTuNiePrzyjdzie", 199);
    for(int i = 0; i < 1000; i++) {
        s1 -= 10;
        assert(s1.kontroler());
    }
    stringstream ss;
    ss << s1.kontroler();
    assert(ss.str() == "ALARM: ZMANIPULOWANY\n");
    Sejf s2("WodaNieUroda");
//    s1 = s2; // BLAD KOMPILACJI FIXME
    swap(s2, s1);
    assert(s1.kontroler());
    auto k1 = s1.kontroler();
    auto k2 = k1; // A tutaj co??? Chyba OK
 //   __typeof(k2) k3(s1); // Ale tu ma sie wywalic. FIXME
    s1 += 1; //43
    s1 *= 2; //86
    s1 += -86; // 86
    s1 -= 85;
    assert(s1.kontroler());
    int16_t x = s1[0];
    assert((char)x == 'W');
    x = s1[0];
    assert(x == -1);
    assert(!k2);
    s1 += 10;
    s1 *= 0;
    assert(k2);
    ss.str("");
    ss << k2;
    assert(ss.str() == "ALARM: WLAMANIE\n");
}

void testy_z_tresci() {
    cout << "Testy z tresci" << endl;
    Sejf s1("aaa", 2);
    auto k1 = s1.kontroler();
	s1[0];
	s1 *=3;
    assert(k1);
    for(int i = 0; i < 3; i++) {
        pobierz(s1, "aaa");
    }
    assert(!k1);
    pobierz(s1, "aaa", false);
    Sejf s2("bbb", 3);
    swap(s1, s2);
    assert(k1);
    for(int i = 0; i < 3; i++) {
        pobierz(s1, "bbb");
    }
    assert(!k1);
    pobierz(s1, "bbb", false);

//	Sejf s4 = s1; // BLAD KOMPILACJI FIXME
//	Sejf s5(s1); // BLAD KOMPILACJI FIXME
    {
        stringstream ss;
        Sejf s1("aaa", 2);
        s1[2];
        auto k1 = s1.kontroler();
        ss << k1 << "test\n";
        s1[2];
        s1[3];
        s1[4];
        ss << k1;
        s1[3];
        ss << k1;
        s1[2];
        ss << k1;
        assert(ss.str() == 
            "OK\ntest\nOK\nOK\nALARM: WLAMANIE\n");

    }
    {
        Sejf s1("aaa", 2);
        Sejf s2("aaa", 2);
        if (s1.kontroler()) {
            assert(true);
        }
/*        if(s1.kontroler() < s2.kontroler()) {
            assert(false); // tu ma byc blad kompilacji // FIXME
        }
        */
    }
}

void testy_z_forum() {
    cout << "Testy z forum" << endl;
    stringstream ss1, ss2;
    Sejf s1("pon");
    Sejf s2("wto");
    Sejf s3("sro");
    Sejf s4("pia");
    string okejka="OK\n", manipul="ALARM: ZMANIPULOWANY\n";
    ss1 << okejka << okejka << okejka;
    auto k1 = s1.kontroler(), k2(s2.kontroler()),  // To jest Ok
         k3 = s3.kontroler(), k4 = s4.kontroler();
    ss2 << k1 << k2 << k3;
    assert(ss1.str() == ss2.str());
    ss1.str(""), ss2.str("");
//  Przemysław Gumienny w dniu Tuesday, 5 November 2013, 20:48 napisał(a) 
    s1 += 0; 
    s2 -= 0; 
    s3 *= 1;
    s4 *= 0; // Mnozenie przez 0 nie skonczy sie sukcesem, wiec nie bedzie manipulacja

    ss1 << manipul << manipul << manipul << okejka;
    ss2 << k1 << k2 << k3 << k4;

    assert(ss1.str() == ss2.str());

// Tomasz Stęczniewski w dniu Wednesday, 6 November 2013, 15:26 napisał(a) 
    {
    Sejf s1("aaa", 1), s2("bbb", 0);

    auto k1 = s1.kontroler();

    swap(s1, s2);
    assert(!k1);
    }
    /*
On 2013-11-10 00:31, Maciej Szeszko wrote:
> Zamieszczam przykład. Proszę o wskazanie prawdiłowego out'a
>*/

    {
 Sejf s1 ("aaa", 0);
 s1 += 0;
 s1[2];
 s1 += 2;
 s1[1];
 s1[3];
 stringstream ss;
 auto k1 = s1.kontroler();
 ss.str("");
 ss << k1;
    assert(ss.str() == "ALARM: WLAMANIE\n");

 ss.str("");
 ss << k1;
 assert(ss.str() == "ALARM: WLAMANIE\n");


 s1[0];
 s1 += 3;
 s1[2];
 ss.str("");
 ss << s1.kontroler();
 assert(ss.str() == "ALARM: WLAMANIE\n");

 ss.str("");
 ss << s1.kontroler();
 assert(ss.str() == "ALARM: WLAMANIE\n");
    }

        // Dawid Łazarczyk w dniu Sunday, 10 November 2013, 10:57 napisał(a)
    {
    stringstream ss;
    Sejf a("A", 1), b("B", 1);
    b += 1;
    auto k = b.kontroler();
    a[0]; a[0];
    std::swap(a, b);
    ss << k;
    assert(ss.str() == "ALARM: WLAMANIE\n");
        
    
    Sejf c("A", -3); // Nie powinno sie dac skonstruowac
    // sejfu o ujemnej maksymalnej liczbie dostepow
    // Ponoc mozna to rozwiazywac na rozne sposoby
    // np. rzucac wyjatek. Ale jesli konstruktor przyjmuje
    // unsigned, to takie sejf zdaje sie moze sie stworzyc
    assert(c.kontroler());
    }

// Hubert Tarasiuk w dniu Saturday, 16 November 2013, 21:43 napisał(a)
  {
    string str = "superokonioszcurowydra";
    Sejf s1(str, 41);
    s1 = move(s1);
    for(int i = 0; i < 10; i++)
        assert((char)s1[i] == str[i]);
  }

  {
      // Jacek Koziński w dniu Sunday, 17 November 2013, 00:16 napisał(a)
     string s = "kot";
     Sejf s1("pies"), s2(s); 
     Sejf s3 = std::move(s1); 
     s1 = std::move(s2);
     for(int i = 0; i < 3; i++)
         assert(s1[i] == s[i]);

  }

}

const long long ILE = UINT_MAX; // Zmien na tyle, ile maksymalnie odczytow dopuszczasz

void testy_kontrowersyjne() {
  cout << "Testy kontrowersyjne" << endl;
  // Kontrowersyjne dlatego, ze zaleza od implemenatacji
  string str = "puchacz_przez_ch";
  Sejf s(str, 1);
  s *= ILE;
  s -= ILE;
  s += ILE - 1;
  s *= ILE; // To nie powinno sie udac :P
  s *= 2; // To tez nie :P
  s += 1;
  s -= ILE - 1;
  s -= ILE; // To rozwniez
  assert(s.kontroler());
  pobierz(s, str);
  assert(!s.kontroler());
  pobierz(s, str, false);
  
 Sejf s2(str, 10);
 s2 *= ILE;
 s2 *= -1;
 s2 += -1;
 s2 -= -1;
 s2 -= ILE;
 s2 *= 0;
 stringstream ss;
 ss << s2.kontroler();
 assert(ss.str() == "OK\n"); // Zadna z manipulacji nie zakonczyla sie "sukcesem"

 cout << "( Teraz bedzie kontrowersja, jakich malo: 0 x 0 )" << endl;
 Sejf s3(str, 0);
 s3 *= 0;
 ss.str("");
 ss << s3.kontroler();
 assert(ss.str() == "ALARM: ZMANIPULOWANY\n"); // KONTROWERSJAAAAA
}

void testy_konstruktorow() {
  cout << "Testy konstruktorow" << endl;
  Sejf s1("ein_Wurst");
  const Sejf s2("kein_Wurst");
//  s1 = s2; // FIXME Blad kompilacji
//  auto xx = s1.stan; // FIXME Blad kompilacji
//  auto s3(s2); // FIXME Blad kompilacji
//  s2 += 5; // FIXME Blad kompilacji
  auto k1 = s1.kontroler();
  auto k2(s1.kontroler());
//  if(k1 < k2) { // FIXME Blad kompilacji
//    assert(false);
//  }
//  swap(k1, k2); // FIXME Tu moze byc blad, ale nie musi
  // zalezy od tego, czy uzywamy wskaznikow, czy referencji
  auto k3 = k2;
  stringstream ss;
  ss << k3 << k1;
//  __typeof(k3) k4; // FIXME Blad kompilacji
//  __typeof(k3) k4(s1); // FIXME Blad kompilacji
}

const Sejf daj_const_sejfa() {
    Sejf s("a");
    return s;
}

Sejf daj_sejfa() {
    Sejf s("b");
    return s;
}

string daj_const_stringa() {
    string str("abc");
    return str;
}

string daj_stringa() {
    string str("abc");
    return str;
}
int main() {
    srand(1233321);
    testy_liczb();
    testuj_42();
    testuj_pusty();
    testuj_operatory();
    testuj_operatory_zdradliwe();

    testuj_kontroler();
    testy_z_tresci();
    testy_konstruktorow();

    testy_dzikie_z_palca();
    testy_z_forum();
    testy_kontrowersyjne();
    //testy_constow();

    cout << "Twoj program dziala tak samo jak moj :P" << endl;
    cout << "Ciekawe, czy cos z tego wynika" << endl;
}
