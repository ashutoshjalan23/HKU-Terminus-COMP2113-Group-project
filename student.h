<<<<<<< HEAD
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
        friend class Halls;
        }

        int getMoney() const {
            return money;
        }

        void addMoney(int amount) {
            if (amount > 0) {
                money += amount;
            }
        }

        void deductMoney(int amount) {
            if (amount > 0) {
                money -= amount;
                if (money < 0) {
                    money = 0;
                }
            }
        }

        const string& getHall() const {
            return hall;
        }

        void setHall(const string& h) {
            hall = h;
        }
};



#endif
=======
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
using namespace std;

// Student class definition
class Student {
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
    Student(string n, int a);

    void attendLecture();
    void study();
    void eat();
    void socialize();
    void rest();
    void displayStatus();

    int getMoney() const;
    void addMoney(int amount);
    void deductMoney(int amount);
    const string& getHall() const;
    void setHall(const string& h);

    string getName() const { return name; }
    int getAge() const { return age; }
    double getHealth() const { return health; }
    double getKnowledge() const { return knowledge; }
    double getEnergy() const { return energy; }
    double getStamina() const { return stamina; }
    double getSocial() const { return social; }
};

#endif
>>>>>>> bd766b2e59b6c90339a151cf615c28fe903efb03
