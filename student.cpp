#include <iostream>
#include "student.h"
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
             moves("Function Call","Subroutine", 0, 25, {"Support"}, "Calls a helper function to restore significant health.")}; // Introductory programming moves
}




// Simulates studying independently
void Student::study() {
    cout << name << " is studying.\n";
    knowledge += 5;   // Gain more knowledge than lecture
    energy -= 30;     // Higher energy cost
        // Higher stamina cost
}

// Simulates eating to recover health and energy
void Student::eat() {
    cout << name << " is eating.\n";
    health += 20;     // Increase health
    energy += 30;     // Restore energy
}

// Simulates social interaction
void Student::socialize() {
    cout << name << " is socializing with friends.\n";
      // Increase social level
    energy -= 10;     // Small energy cost
}

// Simulates resting to recover stats
void Student::rest() {
    cout << name << " is resting.\n";
    health += 10;     // Recover some health
    energy += 20;     // Recover energy
       // Recover stamina
}

// Displays the current status of the student
void Student::displayStatus() {
    cout << "\nStatus of " << name << ":\n";
    cout << "Health: " << health << "\n";
    cout << "Knowledge: " << knowledge << "\n";
    cout << "Energy: " << energy << "\n";
  
    cout << "Money: $" << money << "\n\n";
}

// Returns the current amount of money
int Student::getMoney() const {
    return money;
}

// Adds money to the student's balance (only if positive)
void Student::addMoney(int amount) {
    if (amount > 0) {
        money += amount;
    }
}

// Deducts money from the student's balance (ensures it doesn't go below 0)
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
