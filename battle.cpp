#include<iostream>
#include "battle.h"
#include "student.h"
#include <cstdlib>
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

fight::fight(Student& p, Student& o) {
    player=p;
    opponent=o;
}

void fight::startBattle(){
    cout<<"Battle starts between"<<player.getName()<< " and "<<opponent.getName()<< "!\n";
    string playerMove, opponentMove;
    int playerHealth=player.getHealth();
    int opponentHealth=opponent.getHealth();

    while(playerHealth>0 && opponentHealth>0){
        cout<<player.getName()<<", choose your move: ";
        cin>>playerMove;
        cout<<opponent.getName()<<" chooses their move.\n";
       
        int opponentMoveIndex = rand() % opponent.getMoveSet().size();
        opponentMove = opponent.getMoveSet()[opponentMoveIndex].getName();

        cout<<player.getName()<<" uses "<<playerMove<<"!\n";
        cout<<opponent.getName()<<" uses "<<opponentMove<<"!\n";

        playerHealth -= rand() % 20; 
        opponentHealth -= rand() % 20; 

        cout<<player.getName()<<" has "<<playerHealth<<" health left.\n";
        cout<<opponent.getName()<<" has "<<opponentHealth<<" health left.\n";
    }
}