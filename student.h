#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
using namespace std;
// Student class definition
class Student{
    private:
        string name;
        int age;
        int money;
        string hall;
        double health;
        double knowledge;
        double energy;
        double stamina;
        double social;
        string faculty;
        string location;
    public:
        Student(string n, int a) {
            name = n;
            age = a;
            health = 100.0;
            knowledge = 20.0;
            energy = 100.0;
            stamina = 100.0;
            social = 50.0;
            money = 200000; // Starting money
            faculty="Computer Science"; // Default faculty
        }
        
        void attendLecture() {
            cout << name << " is attending a lecture.\n";
            knowledge += 2;
            energy -= 20;
            stamina -= 15;
        }
        
        void study() {
            cout << name << " is studying.\n";
            knowledge += 5;
            energy -= 30;
            stamina -= 25;
        }
        
        void eat() {
            cout << name << " is eating.\n";
            health += 20;
            energy += 30;
        }
        
        void socialize() {
            cout << name << " is socializing with friends.\n";
            social += 20;
            energy -= 10;
        }
        
        void rest() {
            cout << name << " is resting.\n";
            health += 10;
            energy += 20;
            stamina += 15;
        }
        
        void displayStatus() {
            cout << "\nStatus of " << name << ":\n";
            cout << "Health: " << health << "\n";
            cout << "Knowledge: " << knowledge << "\n";
            cout << "Energy: " << energy << "\n";
            cout << "Stamina: " << stamina << "\n";
            cout << "Social: " << social << "\n\n";
        }   
};



#endif