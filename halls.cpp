#include <iostream>
#include "halls.h"
using namespace std;

// Default constructor: initializes a Halls object with empty/zero values
Halls::Halls() {
    name = "";           // Hall name (empty by default)
    description = "";    // Hall description (empty by default)
    fees = 0;            // Hall fees (zero by default)
    location = "";       // Hall location (empty by default)
}

// Parameterized constructor: initializes a Halls object with given values
Halls::Halls(string n, string d, int f, string l) {
    name = n;           // Set hall name
    description = d;    // Set hall description
    fees = f;           // Set hall fees
    location = l;       // Set hall location
}

// Displays the hall’s details to the console
void Halls::showHall() {
    cout << "Name: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Fees: " << fees << endl;
    cout << "Location: " << location << endl;
}

// Lets the student choose this hall and applies the effects
void Halls::choose(Student& s) {
    cout << "You have chosen to stay in " << name << ".\n";
    cout << "Enjoy your stay at " << name << "!\n";
    s.deductMoney(fees);   // Deduct hall fees from the student’s money
    s.rest();              // Student rests after checking in
    s.setHall(name);       // Set the student’s residence to this hall
}