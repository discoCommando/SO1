all: kontroler.o sejf.o

kontroler.o: kontroler.cc kontroler.h
	g++ -Wall -std=c++11 -O2 kontroler.cc -o kontroler.o

sejf.o: sejf.cc sejf.h kontroler.h
	g++ -Wall -std=c++11 -O2 sejf.cc -o sejf.o

clean:
	rm -f sejf.o kontroler.o
