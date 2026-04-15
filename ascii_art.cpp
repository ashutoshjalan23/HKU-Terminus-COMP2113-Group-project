#include "ascii_art.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

// Forward declarations for external functions/constants from main.cpp
extern void clearScreen();
extern void moveCursor(int row, int col);
extern const int RIGHT_START;

// Color codes
#define RESET       "\033[0m"
#define CYAN        "\033[38;5;110m"

vector<string> loadAsciiArt(const string& filename) {
    vector<string> result;
    
    // Try multiple possible paths (both relative and absolute)
    vector<string> possiblePaths = {
        "./art/" + filename + ".dat",
        "art/" + filename + ".dat",
        "../gp/art/" + filename + ".dat",
        // Absolute paths for Windows
        "d:/Ashutosh Jalan Documents/HKU/COMP2113/gp/art/" + filename + ".dat",
        "d:\\Ashutosh Jalan Documents\\HKU\\COMP2113\\gp\\art\\" + filename + ".dat",
        // Absolute paths for WSL
        "/mnt/d/Ashutosh Jalan Documents/HKU/COMP2113/gp/art/" + filename + ".dat"
    };
    
    for (const auto& filepath : possiblePaths) {
        ifstream file(filepath);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                result.push_back(line);
            }
            file.close();
            return result;  // Successfully loaded
        }
    }
    
    // If we get here, file not found - show which paths were tried
    std::cerr << "Warning: Could not open ASCII art file: " << filename << ".dat" << endl;
    std::cerr << "Tried paths:" << endl;
    for (const auto& path : possiblePaths) {
        std::cerr << "  - " << path << endl;
    }
    return result;
}


// Generic function to display ASCII art with animation (expanding from center)
void displayAsciiArtAnimated(const vector<string>& lines, int delayMs, const string& color) {
    int totalLines = static_cast<int>(lines.size());
    if (totalLines == 0) {
        return;
    }

    int center = totalLines / 2;

    for (int offset = 0; offset <= center; ++offset) {
        clearScreen();
        for (int i = 0; i < totalLines; ++i) {
            if (i >= center - offset && i <= center + offset) {
                if (!color.empty()) {
                    cout << color;
                }
                cout << lines[i];
                if (!color.empty()) {
                    cout << RESET;
                }
                cout << std::endl;
            } else {
                cout << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

// Generic function to display ASCII art without animation
void displayAsciiArt(const vector<string>& lines, const string& color) {
    if (!color.empty()) {
        cout << color;
    }
    for (const auto& line : lines) {
        cout << line << std::endl;
    }
    if (!color.empty()) {
        cout << RESET;
    }
}

// Display ASCII art on the right side with color
void displayAsciiArtRight(const vector<string>& lines, const string& color) {
    int row = 1;
    for (const auto& line : lines) {
        moveCursor(row, RIGHT_START);
        if (!color.empty()) {
            cout << color;
        }
        cout << line << RESET;
        row++;
    }
    cout << std::flush;
}

// Display ASCII art on the right side with glitch animation effect
void displayAsciiArtRightAnimated(const vector<string>& lines, const string& color, int delayMs) {
    int totalLines = static_cast<int>(lines.size());
    if (totalLines == 0) return;
    
    // Glitch animation: lines appear with distortion
    for (int frame = 0; frame < totalLines + 5; frame++) {
        for (int i = 0; i < totalLines; i++) {
            moveCursor(i + 1, RIGHT_START);
            
            // Determine if this line should be displayed and with what effect
            if (i < frame) {
                // Line is visible
                if (!color.empty()) cout << color;
                
                // Random glitch effect on some frames
                if (frame < totalLines && rand() % 3 == 0) {
                    // Glitch: offset some characters
                    string glitched = lines[i];
                    int glitchPos = rand() % glitched.length();
                    if (glitchPos > 0) {
                        glitched[glitchPos] = '#';
                    }
                    cout << glitched;
                } else {
                    // Normal display
                    cout << lines[i];
                }
                
                if (!color.empty()) cout << RESET;
            }
            cout << std::flush;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

vector<string> getTitleLines() {
    auto lines = loadAsciiArt("HKU_logo");
     if (lines.empty()) {
        lines.push_back("[ ASCII art file 'HKU_logo.dat' not found in ./art/ directory ]");
    }
    return lines;
}