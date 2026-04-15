#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include<vector>
#include "battle.h"
using namespace std;

// Student class definition
class Student {
private:
    string name;
    int age;
    int money;
    string hall;
    double health;
    double knowledge;
    double energy;
    string faculty;
    string location;
    vector<moves> moveSet;

public:
    Student(string n, int a);

    void attendLecture();
    void study();
    void eat();
    void socialize();
    void rest();
    void displayStatus();

    int getMoney() const;
    void addMoney(int amount);
    void deductMoney(int amount);
    const string& getHall() const;
    void setHall(const string& h);
    const vector<moves>& getMoveSet() const;
    string getName() const { return name; }
    int getAge() const { return age; }
    double getHealth() const { return health; }
    double getKnowledge() const { return knowledge; }
    double getEnergy() const { return energy; }

};

#endif
