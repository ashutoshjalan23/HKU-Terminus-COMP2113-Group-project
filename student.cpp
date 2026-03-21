#include <iostream>
#include "student.h"
using namespace std;

Student::Student(string n, int a) {
    name = n;
    age = a;
    health = 100.0;
    knowledge = 20.0;
    energy = 100.0;
    stamina = 100.0;
    social = 50.0;
    money = 200000; // Starting money
    faculty = "Computer Science"; // Default faculty
    location = "HKU Campus";
}

void Student::attendLecture() {
    cout << name << " is attending a lecture.\n";
    knowledge += 2;
    energy -= 20;
    stamina -= 15;
}

void Student::study() {
    cout << name << " is studying.\n";
    knowledge += 5;
    energy -= 30;
    stamina -= 25;
}

void Student::eat() {
    cout << name << " is eating.\n";
    health += 20;
    energy += 30;
}

void Student::socialize() {
    cout << name << " is socializing with friends.\n";
    social += 20;
    energy -= 10;
}

void Student::rest() {
    cout << name << " is resting.\n";
    health += 10;
    energy += 20;
    stamina += 15;
}

void Student::displayStatus() {
    cout << "\nStatus of " << name << ":\n";
    cout << "Health: " << health << "\n";
    cout << "Knowledge: " << knowledge << "\n";
    cout << "Energy: " << energy << "\n";
    cout << "Stamina: " << stamina << "\n";
    cout << "Social: " << social << "\n";
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
            money = 0;
        }
    }
}

const string& Student::getHall() const {
    return hall;
}

void Student::setHall(const string& h) {
    hall = h;
}
