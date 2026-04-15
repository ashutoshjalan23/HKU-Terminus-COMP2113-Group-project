CXX = g++
CXXFLAGS = -std=c++11 -Wall 
TARGET = main

OBJS = main.o student.o halls.o battle.o ascii_art.o

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp student.h halls.h battle.h ascii_art.h
	$(CXX) $(CXXFLAGS) -c main.cpp

student.o: student.cpp student.h battle.h
	$(CXX) $(CXXFLAGS) -c student.cpp

halls.o: halls.cpp halls.h student.h battle.h
	$(CXX) $(CXXFLAGS) -c halls.cpp

battle.o: battle.cpp battle.h student.h
	$(CXX) $(CXXFLAGS) -c battle.cpp

ascii_art.o: ascii_art.cpp ascii_art.h
	$(CXX) $(CXXFLAGS) -c ascii_art.cpp

clean:
	rm -f *.o main

.PHONY: clean
