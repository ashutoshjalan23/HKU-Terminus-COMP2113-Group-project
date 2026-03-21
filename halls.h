#ifndef HALLS_H
#define HALLS_H

#include <string>
#include <iostream>
#include "student.h"
using namespace std;

// Hall class definition
class Halls {
private:
    string name;
    string description;
    int fees;
    string location;

public:
    Halls();
    Halls(string n, string d, int f, string l);

    void showHall();
    void choose(Student& s);

    string getName() const { return name; }
    string getDescription() const { return description; }
    int getFees() const { return fees; }
    string getLocation() const { return location; }
};

#endif
