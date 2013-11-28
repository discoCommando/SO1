#ifndef KONTROLER_H
#define KONTROLER_H

#include <ostream>
#include <cstring>


enum poziom_wlamania {OK=0, MANIPULACJA=1, WLAMANIE=2};
const std::string kod_alarmu[3] = {"OK\n", "ALARM: ZMANIPULOWANY\n", "ALARM: WLAMANIE\n"};

class Kontroler final{
public:
	friend class Sejf;
	
	
	friend std::ostream& operator<<(std::ostream& wyjscie, const Kontroler& kontroler);
	explicit operator bool() const;

private:
	poziom_wlamania *_stan_sejfu;
	size_t *_liczba_dostepow;
	
	Kontroler(poziom_wlamania *stan, size_t *liczba_dostepow)
			: _stan_sejfu(stan)
			, _liczba_dostepow(liczba_dostepow)
			{
				
			}
	
};

#endif //KOTROLER_H