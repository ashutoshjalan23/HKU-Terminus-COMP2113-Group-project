#include<iostream>
#include "common.h"
#include<string>
using namespace std;

// Define constants
const int LEFT_WIDTH = 100;
const int RIGHT_START = 101;


void moveCursor(int row, int col) {
    cout << "\033[" << row << ";" << col << "H";
}

void printLeftSide(const string& text) {
    moveCursor(g_left_row, 1);
    
    string output = text.length() > LEFT_WIDTH ? text.substr(0, LEFT_WIDTH) : text;  //pnly printing the length which 
                                                                                    // fit in the left side
   if(output==text) cout << output << flush;
   else{
        cout << output << "..." << flush; 
        g_left_row++;
        string remaining = text.substr(LEFT_WIDTH);
        printLeftSide(remaining);  //printing remaining part recursively again
   }
    g_left_row++;
}

void clearScreen() {
    
    system("clear");
    return;

}