#ifndef COMMON_H
#define COMMON_H


#include<iostream>
#include<string>
using namespace std;
extern int g_left_row ;  //so i can use later in main.cpp
extern const int LEFT_WIDTH;
extern const int RIGHT_START;

void moveCursor(int row, int col);
void printLeftSide(const string& text);
void clearScreen();

#endif
