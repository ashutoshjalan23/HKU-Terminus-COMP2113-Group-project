#ifndef COMMON_H
#define COMMON_H


#include<iostream>
#include<string>
using namespace std;
extern int g_left_row ;  //so i can use later in main.cpp
extern int LEFT_WIDTH;
extern int RIGHT_START;
extern int TERMINAL_WIDTH;
extern int TERMINAL_HEIGHT;

void updateTerminalLayout();

void moveCursor(int row, int col);
void printLeftSide(const string& text);
void clearLeftPaneRow(int row);
void clearScreen();
void clearLine();
#endif
