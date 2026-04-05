CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = main

OBJS = main.o student.o halls.o ascii_art.o

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp student.h halls.h ascii_art.h
	$(CXX) $(CXXFLAGS) -c main.cpp

student.o: student.cpp student.h
	$(CXX) $(CXXFLAGS) -c student.cpp

halls.o: halls.cpp halls.h student.h
	$(CXX) $(CXXFLAGS) -c halls.cpp

ascii_art.o: ascii_art.cpp ascii_art.h
	$(CXX) $(CXXFLAGS) -c ascii_art.cpp

clean:
	rm -f *.o main

.PHONY: clean
