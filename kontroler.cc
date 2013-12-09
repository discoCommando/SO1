#include "kontroler.h"
#include <iostream>

std::ostream& operator<<(std::ostream& wyjscie, const Kontroler& kontroler) {
	wyjscie << kod_alarmu[*kontroler._stan_sejfu];
	return wyjscie;
}

Kontroler::operator bool() const {
	return *_liczba_dostepow > 0;
}

