#include<iostream>
#include "battle.h"
#include "student.h"
using namespace std;

moves::moves(string mt, string n, int d, int h, const vector<string>& e, string desc) {
    move_type = mt;
    name = n;
    damage = d;
    heal = h;
    effects = e;
    description = desc;
}

void moves::useMove() {
    cout << name << " is used!\n";
    cout << description << "\n";
}

void moves::moveDescription() {
    cout << "Move: " << name << "\n";
    cout << "Type: " << move_type << "\n";
    cout << "Damage: " << damage << "\n";
    cout << "Heal: " << heal << "\n";
    cout << "Effects: ";
    for (const string& effect : effects) {
        cout << effect << " ";
    }
    cout << "\n";
}

void moves::applyEffects(Student& s, Student& opponent) {
    if (damage > 0) {
        cout << opponent.getName() << " takes " << damage << " damage!\n";
        
    }
    if (heal > 0) {
        cout << s.getName() << " heals for " << heal << " health!\n";
        
    }
    for (const string& effect : effects) {
        cout << s.getName() << " is affected by " << effect << "!\n";
   
    }
}