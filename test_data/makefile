CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET=battle

battle: battle.o student.o test.o
	$(CXX) $(CXXFLAGS) battle.o student.o test.o -o battle

battle.o: battle.cpp battle.h student.h
	$(CXX) $(CXXFLAGS) -c battle.cpp
student.o: student.cpp student.h
	$(CXX) $(CXXFLAGS) -c student.cpp
test.o: test.cpp battle.h student.h
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f *.o battle		