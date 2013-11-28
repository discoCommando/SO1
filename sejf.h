#ifndef __SEJF_H__
#define __SEJF_H__
#include <string>
#include <cstdint>
#include <limits>
#include <iostream>
#include <utility>
#include "kontroler.h"
using namespace std;

typedef uintmax_t rozmiar_napisu;

const size_t max_liczba_dostepow = numeric_limits<size_t>().max();
class Kontroler;
class Sejf{
public:
Sejf(const string napis, const size_t dostepy = 42);
Sejf(const Sejf&);
Sejf& operator=(const Sejf&);
Sejf& operator+=(size_t modyfikator);
Sejf& operator-=(size_t modyfikator);
Sejf& operator*=(size_t modyfikator);
int16_t operator[](rozmiar_napisu numer_skrytki);
Kontroler& kontroler();
Kontroler const& kontroler() const;
~Sejf();

private:
string tajny_napis;
size_t liczba_dostepow;
poziom_wlamania stan_sejfu;
Kontroler moj_kontroler;
};

#endif