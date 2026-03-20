#include<iostream>
#include<string>
#include "student.h"
using namespace std;

class Halls{
    private:
        string name;
        string description;
        int capcaity;
        string location;
        int fees;
    public:
        Halls(string n, string d, int c, string l) {
            name = n;
            description = d;
            capcaity = c;
            location = l;
        }

        void showHall(Halls h){
            cout << "Name: " << h.name << endl;
            cout << "Description: " << h.description << endl;
            cout << "Capacity: " << h.capcaity << endl;
            cout << "Location: " << h.location << endl;
        }

        void choose(Halls h, Student& s){
            cout << "You have chosen to stay in " << h.name << ".\n";
            cout << "Enjoy your stay at " << h.name << "!\n";
            s.deductMoney(h.fees);
            s.rest();
        }
};

int main()
{
    
    return 0;
}