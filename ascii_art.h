#ifndef ASCII_ART_H
#define ASCII_ART_H

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Function declarations for ASCII art operations
vector<string> loadAsciiArt(const string& filename);

void displayAsciiArtAnimated(const vector<string>& lines, int delayMs = 50, const string& color = "");

void displayAsciiArt(const vector<string>& lines, const string& color = "");

void displayAsciiArtRight(const vector<string>& lines, const string& color = "");

void displayAsciiArtRightAnimated(const vector<string>& lines, const string& color = "", int delayMs = 50);

vector<string> getTitleLines();

#endif // ASCII_ART_H