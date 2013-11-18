all: manager executor



manager: manager.o err.o
	gcc -Wall -o manager manager.o err.o

executor: executor.o err.o
	gcc -Wall -o executor executor.o err.o

manager.o: manager.c err.h
	gcc -Wall -c manager.c

executor.o: executor.c err.h
	gcc -Wall -c executor.c


err.o: err.c err.h
	gcc -Wall -c err.c

clean:
	rm -f *.o manager executor

