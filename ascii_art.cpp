#include "ascii_art.h"
#include "common.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Color codes
#define RESET       "\033[0m"
#define CYAN        "\033[38;5;110m"
#define YELLOW      "\033[38;5;179m"

static void clearRightPane() {
    updateTerminalLayout();
    int rightPaneWidth = max(1, TERMINAL_WIDTH - RIGHT_START + 1);
    for (int row = 1; row <= TERMINAL_HEIGHT; ++row) {
        moveCursor(row, RIGHT_START);
        cout << string(rightPaneWidth, ' ');
    }
    cout << flush;
}

static vector<string> scaleAsciiArtToFit(const vector<string>& lines, int maxWidth, int maxHeight) {
    if (lines.empty()) {
        return lines;
    }

    int originalHeight = static_cast<int>(lines.size());
    int originalWidth = 0;
    for (const auto& line : lines) {
        originalWidth = max(originalWidth, static_cast<int>(line.size()));
    }

    if (originalWidth <= 0) {
        return lines;
    }

    double widthScale = (originalWidth > maxWidth) ? static_cast<double>(maxWidth) / static_cast<double>(originalWidth) : 1.0;
    double heightScale = (originalHeight > maxHeight) ? static_cast<double>(maxHeight) / static_cast<double>(originalHeight) : 1.0;
    double scale = min(widthScale, heightScale);

    if (scale >= 1.0) {
        return lines;
    }

    int targetWidth = max(1, static_cast<int>(originalWidth * scale));
    int targetHeight = max(1, static_cast<int>(originalHeight * scale));

    vector<string> scaled;
    scaled.reserve(targetHeight);

    for (int y = 0; y < targetHeight; ++y) {
        int srcY = min(originalHeight - 1, static_cast<int>(y / scale));
        const string& srcLine = lines[srcY];

        string out;
        out.reserve(targetWidth);

        for (int x = 0; x < targetWidth; ++x) {
            int srcX = min(originalWidth - 1, static_cast<int>(x / scale));
            if (srcX < static_cast<int>(srcLine.size())) {
                out.push_back(srcLine[srcX]);
            } else {
                out.push_back(' ');
            }
        }
        scaled.push_back(out);
    }

    return scaled;
}

vector<string> loadAsciiArt(const string& filename) {
    vector<string> result;
    
    // Try relative paths only.
    vector<string> possiblePaths = {
        "./art/" + filename + ".dat",
        "art/" + filename + ".dat",
        "../gp/art/" + filename + ".dat"
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

    if (result.empty() && (filename=="HKU_logo" || filename=="rival2")){
        printLeftSide(std::string(YELLOW) + "[ ASCII art file ' " + filename + "' not found in ./art/ directory ]" + RESET);
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
    updateTerminalLayout();
    int rightPaneWidth = max(1, TERMINAL_WIDTH - RIGHT_START + 1);
    int maxArtHeight = max(1, TERMINAL_HEIGHT);
    vector<string> fittedLines = scaleAsciiArtToFit(lines, rightPaneWidth, maxArtHeight);

    clearRightPane();

    int row = 1;
    for (const auto& line : fittedLines) {
        int startCol = RIGHT_START + max(0, rightPaneWidth - static_cast<int>(line.size()));
        moveCursor(row, startCol);
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
    updateTerminalLayout();
    int rightPaneWidth = max(1, TERMINAL_WIDTH - RIGHT_START + 1);
    int maxArtHeight = max(1, TERMINAL_HEIGHT);
    vector<string> fittedLines = scaleAsciiArtToFit(lines, rightPaneWidth, maxArtHeight);

    int totalLines = static_cast<int>(fittedLines.size());
    if (totalLines == 0) return;

    clearRightPane();
    
    // Glitch animation: lines appear with distortion
    for (int frame = 0; frame < totalLines + 5; frame++) {
        for (int i = 0; i < totalLines; i++) {
            moveCursor(i + 1, RIGHT_START);
            cout << string(rightPaneWidth, ' ');
            moveCursor(i + 1, RIGHT_START);
            
            // Determine if this line should be displayed and with what effect
            if (i < frame) {
                // Line is visible
                if (!color.empty()) cout << color;
                
                // Random glitch effect on some frames
                if (frame < totalLines && rand() % 3 == 0) {
                    // Glitch: offset some characters
                    string glitched = fittedLines[i];
                    if (!glitched.empty()) {
                        int glitchPos = rand() % glitched.length();
                        if (glitchPos >= 0) {
                            glitched[glitchPos] = '#';
                        }
                    }
                    int startCol = RIGHT_START + max(0, rightPaneWidth - static_cast<int>(glitched.size()));
                    moveCursor(i + 1, startCol);
                    cout << glitched;
                } else {
                    // Normal display
                    int startCol = RIGHT_START + max(0, rightPaneWidth - static_cast<int>(fittedLines[i].size()));
                    moveCursor(i + 1, startCol);
                    cout << fittedLines[i];
                }
                
                if (!color.empty()) cout << RESET;
            }
            cout << std::flush;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}
