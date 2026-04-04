<<<<<<< HEAD
#include<iostream>
#include<string>
#include "student.h"
using namespace std;



=======
#include <iostream>
#include "halls.h"
using namespace std;

Halls::Halls() {
    name = "";
    description = "";
    fees = 0;
    location = "";
}

Halls::Halls(string n, string d, int f, string l) {
    name = n;
    description = d;
    fees = f;
    location = l;
}

void Halls::showHall() {
    cout << "Name: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Fees: " << fees << endl;
    cout << "Location: " << location << endl;
}

void Halls::choose(Student& s) {
    cout << "You have chosen to stay in " << name << ".\n";
    cout << "Enjoy your stay at " << name << "!\n";
    s.deductMoney(fees);
    s.rest();
    s.setHall(name);
}
>>>>>>> bd766b2e59b6c90339a151cf615c28fe903efb03
