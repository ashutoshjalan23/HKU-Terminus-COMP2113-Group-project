CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = main

OBJS = main.o student.o halls.o

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp student.h halls.h
	$(CXX) $(CXXFLAGS) -c main.cpp

student.o: student.cpp student.h
	$(CXX) $(CXXFLAGS) -c student.cpp

halls.o: halls.cpp halls.h student.h
	$(CXX) $(CXXFLAGS) -c halls.cpp

clean:
	rm -f *.o main

.PHONY: clean
