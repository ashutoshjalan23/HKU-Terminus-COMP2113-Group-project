#ifndef HALLS_H
#define HALLS_H
#include <string>
#include <vector>   
#include "student.h"
using namespace std;

// Hall class definition
class Halls{
    private:
        string name;
        string description;
        int capcaity;
        string location;
        int fees;
    public:

        Halls(){

        }  //std consturctor

        Halls(string n, string d, int c, string l) {
            name = n;
            description = d;
            capcaity = c;
            location = l;
        }

        void showHall(Halls h){
            cout << "Name: " << h.name << endl;
            cout << "Description: " << h.description << endl;
            cout << "Fees: " << h.fees << endl;
            cout << "Location: " << h.location << endl;
        }

        void choose(Halls h, Student& s){
            cout << "You have chosen to stay in " << h.name << ".\n";
            cout << "Enjoy your stay at " << h.name << "!\n";
            s.money -= h.fees;
            s.rest();
        }
};
#endif 