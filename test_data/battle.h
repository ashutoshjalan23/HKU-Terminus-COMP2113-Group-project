#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <iostream>
#include<vector>
using namespace std;

// Forward declaration to break circular dependency
class Student;

//moves class definiton
class moves {
private:
    string move_type;
    string name;
    int damage;
    int heal;
    vector<string> effects;
    string description;    

public:
    moves(string mt, string n, int d, int h, const vector<string>& e, string desc);
    void useMove();
    void moveDescription();
   
    string getName() const;
    void applyEffects(Student& s, Student& opponent);
    };



class fight{
    private:
    Student& player;
    Student& opponent;
    public:
    fight(Student& p, Student& o);
    void startBattle();

};
#endif