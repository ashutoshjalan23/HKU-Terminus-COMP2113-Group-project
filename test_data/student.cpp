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
    moveSet={moves("attack","print",10,0,{"none"},"A basic attack using stream of characters"),
            moves("heal","Garbage Collector",0,15,{"none"},"A defensive move that restores health by collecting garbage data."),
            moves("attack","Segmentation Fault",20,0,{"none"},"A powerful attack that causes a segmentation fault, dealing heavy damage to the opponent."),
            moves("attack","Memory Leak",15,0,{"none"},"An attack that causes a memory leak, dealing damage.")
        };
} // Introductory programming moves






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

void Student::takeDamage(int h) {
    health -= h;
    if (health < 0) health = 0; 
    
    if(health>100) health=100;
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
    