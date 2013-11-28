all: kontroler.o sejf.o

kontroler.o: kontroler.cc kontroler.h
	g++ -Wall -std=c++11 -O2 kontroler.cc -c -o kontroler.o

sejf.o: sejf.cc sejf.h kontroler.h
	g++ -Wall -std=c++11 -O2 kontroler.o sejf.cc -o sejf

clean:
	rm -f sejf.o kontroler.o
