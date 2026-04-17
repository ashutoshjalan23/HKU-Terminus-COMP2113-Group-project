#include <iostream>
#include "student.h"
#include "battle.h"
using namespace std;

// Constructor: initializes a Student object with default values
Student::Student(string n, int a) {
    name = n;                 
    age = a;                  
    health = 100.0;           
    knowledge = 20.0;         
    energy = 100.0;           
               
    money = 200000;           
    faculty = "Computer Science"; 
    location = "HKU Campus";  
    moveSet={moves("Print Statement","Output", 18, 0, {"Display"}, "A basic attack that outputs powerful damage."),
             moves("If Statement","Conditional", 14, 0, {"Check"}, "A conditional attack that evaluates and executes."),
             moves("For Loop","Iteration", 10, 5, {"Repeat"}, "A repeating attack that gains strength through iterations."),
             moves("Function Call","Subroutine", 0, 25, {"Support"}, "Calls a helper function to restore significant health.")}; 
             // Introductory programming moves
}

void Student::study() {
    cout << name << " is studying.\n";
    knowledge += 5;   
    energy -= 30;     
    
}

void Student::eat() {
    cout << name << " is eating.\n";
    health += 20;     
    energy += 30;     
}




// Simulates resting to recover stats
void Student::rest() {
    cout << name << " is resting.\n";
    health += 10;     
    energy += 20;     
       
}


void Student::displayStatus() {
    cout << "\nStatus of " << name << ":\n";
    cout << "Health: " << health << "\n";
    cout << "Knowledge: " << knowledge << "\n";
    cout << "Energy: " << energy << "\n";
  
    cout << "Money: $" << money << "\n\n";
}

int Student::getMoney() const {
    return money;
}

void Student::addMoney(int amount) {
    if (amount > 0) {
        money += amount;
    }
}


void Student::deductMoney(int amount) {
    if (amount > 0) {
        money -= amount;
        if (money < 0) {
            money = 0; // Prevent negative balance
        }
    }
}

// Returns the hall (residence) of the student
const string& Student::getHall() const {
    return hall;
}

// Sets the student's hall (residence)
void Student::setHall(const string& h) {
    hall = h;
}

const vector<moves>& Student::getMoveSet() const {
    return moveSet;
}
    
void Student::setMoveSet(const vector<moves>& newMoveSet) {
    moveSet = newMoveSet;
}

void Student::updateMoveSet( int index, const moves& newMove) {
    if(index>=0 && index<=4){
        moveSet[index]=newMove;
    }
}
