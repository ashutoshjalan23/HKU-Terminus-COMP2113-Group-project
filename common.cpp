#include<iostream>
#include "common.h"
#include<string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;

// Runtime layout values (updated from terminal size)
int LEFT_WIDTH = 100;
int RIGHT_START = 101;
int TERMINAL_WIDTH = 200;
int TERMINAL_HEIGHT = 50;
const int PANEL_GAP = 2;

void updateTerminalLayout() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        TERMINAL_WIDTH = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        TERMINAL_HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        TERMINAL_WIDTH = static_cast<int>(w.ws_col);
        TERMINAL_HEIGHT = static_cast<int>(w.ws_row);
    }
#endif

    if (TERMINAL_WIDTH < 80) {
        TERMINAL_WIDTH = 80;
    }
    if (TERMINAL_HEIGHT < 24) {
        TERMINAL_HEIGHT = 24;
    }

    int paneWidth = (TERMINAL_WIDTH - PANEL_GAP) / 2;
    if (paneWidth < 20) {
        paneWidth = 20;
    }
    LEFT_WIDTH = paneWidth;
    RIGHT_START = LEFT_WIDTH + PANEL_GAP + 1;
}


void moveCursor(int row, int col) {
    cout << "\033[" << row << ";" << col << "H";
}

void printLeftSide(const string& text) {
    updateTerminalLayout();
    size_t leftWidth = static_cast<size_t>(LEFT_WIDTH);

    auto emitLine = [&](const string& line) {
        moveCursor(g_left_row, 1);
        cout << line << flush;
        g_left_row++;
    };

    auto wrapAndEmit = [&](const string& paragraph) {
        if (paragraph.empty()) {
            emitLine("");
            return;
        }

        size_t start = 0;
        while (start < paragraph.size()) {
            size_t remaining = paragraph.size() - start;
            if (remaining <= leftWidth) {
                emitLine(paragraph.substr(start));
                break;
            }

            size_t end = start + leftWidth;
            size_t breakPos = paragraph.rfind(' ', end);
            if (breakPos == string::npos || breakPos < start) {
                breakPos = end;
            }

            emitLine(paragraph.substr(start, breakPos - start));

            start = breakPos;
            while (start < paragraph.size() && paragraph[start] == ' ') {
                start++;
            }
        }
    };

    size_t segmentStart = 0;
    while (segmentStart <= text.size()) {
        size_t newlinePos = text.find('\n', segmentStart);
        if (newlinePos == string::npos) {
            wrapAndEmit(text.substr(segmentStart));
            break;
        }

        wrapAndEmit(text.substr(segmentStart, newlinePos - segmentStart));
        segmentStart = newlinePos + 1;

        if (segmentStart == text.size()) {
            emitLine("");
            break;
        }
    }
}

void clearLine(){
    cout<<"\033[2K";
}

void clearLeftPaneRow(int row) {
    updateTerminalLayout();
    moveCursor(row, 1);
    cout << string(LEFT_WIDTH, ' ') << flush;
    moveCursor(row, 1);
}

void clearScreen() {
    updateTerminalLayout();
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}