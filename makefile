
main.o: main.cpp student.h 
	g++ -c main.cpp

main: main.o
	g++ main.o -o main    

clean:
	rm -f *.o main

.PHONY: clean
