#include<iostream>
#include "battle.h"
#include "student.h"
#include <cstdlib>  
#include<fstream>
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

string moves::getName() const {
    return name;
}

fight::fight(Student& player, Student& opp) : player(player), opponent(opp) {
}

void fight::startBattle(){
  const char filename[100]="../art/arena.txt";
  ifstream fin(filename);

system("clear");
string line;
while(getline(fin,line)){
    cout<<line<<endl;
}

while(player.getHealth()>0 && opponent.getHealth()>0){

vector<moves> playerMoves = player.getMoveSet();
vector<moves> opponentMoves = opponent.getMoveSet();
        
cout<<"\033[2;20H";
cout<<"Player HP: "<<player.getHealth()<<flush;

cout<<"\033[2;40H";
cout<<"Opponent HP: "<<opponent.getHealth()<<flush;

cout<<"\033[22;10H";
cout<<"Choose your move: "<<endl;
int count=1;
for(const moves& i: playerMoves){
    cout<<"\033[10C";

    cout<<count<<". "<<i.getName()<<endl;
    count++;

}
cout<<"\033[39;1H";

cout<<"Enter the number of your move: "<<flush<<endl;
cout<<"\033[2K";
int moveChoice;
cin>>moveChoice;

if(moveChoice<1 || moveChoice>4){
    cout<<"\033[2K";
    cout<<"invalid move choice. Please choose a valid move."<<flush;
    continue;
}
cout<<"\033[2K";
cout<<"User played move: "<<playerMoves[moveChoice-1].getName()<<endl;
}
}