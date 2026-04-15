//only for testing battle data
#include<iostream>
#include "battle.h"
#include "student.h"

using namespace std;

int main()
{
    Student s1("Alice", 20);
    Student s2("Bob", 22);
    moves m1("Attack", "Punch", 10, 0, {"Stun"}, "A quick punch that can stun the opponent.");
    moves m2("Heal", "First Aid", 0, 20, {"Heal"}, "A basic healing move that restores health.");
    fight f(s1, s2);
    f.startBattle();
    return 0;
}