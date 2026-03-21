#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "student.h"
#include "halls.h"

// ANSI color codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"

// Global hall objects
Halls st_johns, shunhing, rc_lee, simon, newcollege;

// File paths
const std::string st_johnsFile = "Halls/stjohns.txt";
const std::string shunhingFile = "Halls/shunhing.txt";
const std::string rc_leeFile = "Halls/rclee.txt";
const std::string simonFile = "Halls/simon.txt";
const std::string newcollegeFile = "Halls/newcollege.txt";
const std::string logoFile = "HKU_logo.dat";

const int screenWidth = 80;

// Type text with animation
void typeText(const std::string& text, int delayMs = 30) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

// Slide logo from center to edges
void showLogo() {
    std::ifstream file(logoFile);
    std::vector<std::string> logoLines;
    std::string line;

    while (std::getline(file, line)) {
        logoLines.push_back(line);
    }

    if (logoLines.empty()) return;

    int totalLines = logoLines.size();
    int center = totalLines / 2;

    for (int offset = 0; offset <= center; ++offset) {
        system("clear");
        for (int i = 0; i < totalLines; ++i) {
            if (i >= center - offset && i <= center + offset) {
                int padding = (screenWidth - logoLines[i].length()) / 2;
                std::cout << std::string(padding, ' ') << CYAN << logoLines[i] << RESET << "\n";
            } else {
                std::cout << "\n";
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void showTitle() {
    showLogo();
    std::cout << "\n\n";
    std::cout << BOLD << YELLOW << "       A University Life Simulation\n" << RESET;
    std::cout << "\n\n";
    std::cout << "           Press Enter to start...";
    std::cin.get();
}

int showMenu() {
    std::cout << "\n\n";
    std::cout << BOLD << CYAN << "Welcome to HKU Terminus!" << RESET << "\n";
    std::cout << BOLD << CYAN << "Main Menu" << RESET << "\n";
    std::cout << "1. " << GREEN << "New Game" << RESET << "\n";
    std::cout << "2. " << GREEN << "Load Game" << RESET << "\n";
    std::cout << "3. " << GREEN << "Quit" << RESET << "\n";
    std::cout << "Enter your choice (1-3): ";

    int choice;
    std::cin >> choice;
    return choice;
}

// Load hall from file
void loadHall(Halls& h, const std::string& fname) {
    std::ifstream f(fname);
    std::string name, feesStr, desc, loc;
    if (std::getline(f, name) && std::getline(f, feesStr) &&
        std::getline(f, desc) && std::getline(f, loc)) {
        int fees = 0;
        for (char c : feesStr) if (isdigit(c)) fees = fees * 10 + (c - '0');
        h = Halls(name, desc, fees, loc);
    }
}

void startGame() {
    system("clear");
    typeText("Welcome to the prestigious " CYAN "University of Hong Kong!" RESET "\n", 30);
    typeText("You are about to embark on an exciting journey as a student at HKU.\n", 30);
    typeText("Your choices will shape your university experience, so choose wisely!\n\n", 30);

    typeText(CYAN "Dr. Chim Tat Wing:" RESET " Hello there! Welcome to HKU.\n", 30);
    typeText("I'm Dr. Chim Tat Wing, your friendly advisor.\n", 30);
    typeText("I'm here to help you navigate your university life.\n\n", 30);

    typeText(CYAN "Dr. Chim Tat Wing: " RESET "What's your name, student?\n", 30);

    std::string name;
    std::cout << "> ";
    std::cin >> name;

    typeText(CYAN "Dr. Chim Tat Wing: " RESET "Nice to meet you, " + name + "!\n", 30);
    typeText("How old are you?\n", 30);

    int age;
    std::cout << "> ";
    std::cin >> age;

    typeText(CYAN "Dr. Chim Tat Wing: " RESET "Great! So you're " + std::to_string(age) + " years old.\n", 30);
    typeText("Let's get you started on your university journey.\n\n", 30);

    Student player(name, age);

    typeText(CYAN "Dr. Chim Tat Wing:" RESET " Now it's time to choose a hall to stay in.\n", 30);
    typeText("Each hall has its own unique atmosphere and facilities.\n", 30);
    typeText("Here are the available halls:\n\n", 30);

    typeText(" (1) St. Johns College\n", 20);
    typeText(" (2) Shun Hing College\n", 20);
    typeText(" (3) RC Lee Hall\n", 20);
    typeText(" (4) Simon Hall\n", 20);
    typeText(" (5) New College\n\n", 20);

    typeText("Choose the number of the hall you want to stay in: ", 30);

    int hallChoice;
    std::cout << "> ";
    std::cin >> hallChoice;

    loadHall(st_johns, st_johnsFile);
    loadHall(shunhing, shunhingFile);
    loadHall(rc_lee, rc_leeFile);
    loadHall(simon, simonFile);
    loadHall(newcollege, newcollegeFile);

    Halls* halls[] = {&st_johns, &shunhing, &rc_lee, &simon, &newcollege};

    Halls currentHall;
    if (hallChoice >= 1 && hallChoice <= 5) {
        currentHall = *halls[hallChoice - 1];
        std::cout << "\n";
        currentHall.showHall();
        player.deductMoney(currentHall.getFees());
        player.setHall(currentHall.getName());
    }

    std::cout << "\n";
    typeText("Enjoy your stay at " + currentHall.getName() + "!\n\n", 30);

    // Game loop
    int day = 1;
    int currentPart = 0; // 0=Morning, 1=Noon, 2=Evening, 3=Night
    const char* dayNames[] = {"Morning", "Noon", "Evening", "Night"};
    bool gameRunning = true;

    while (gameRunning) {
        system("clear");
        std::cout << BOLD << YELLOW << "\n=== Day " << day << " - " << dayNames[currentPart] << " ===" << RESET << "\n\n";

        player.displayStatus();

        std::cout << "What would you like to do?\n\n";
        std::cout << "1. Go to Library (study)\n";
        std::cout << "2. Go to Cafeteria (eat)\n";
        std::cout << "3. Attend Lecture\n";
        std::cout << "4. Socialize with friends\n";
        std::cout << "5. Go to Gym\n";
        std::cout << "6. Sleep (end day)\n";
        std::cout << "7. Check Status\n";
        std::cout << "8. Quit Game\n";
        std::cout << "\nEnter choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                typeText(player.getName() + " goes to the library to study.\n", 15);
                player.study();
                break;
            case 2:
                typeText(player.getName() + " goes to the cafeteria.\n", 15);
                player.eat();
                break;
            case 3:
                typeText(player.getName() + " attends a lecture.\n", 15);
                player.attendLecture();
                break;
            case 4:
                typeText(player.getName() + " socializes with friends.\n", 15);
                player.socialize();
                break;
            case 5:
                typeText(player.getName() + " goes to the gym to exercise.\n", 15);
                break;
            case 6:
                player.rest();
                currentPart++;
                if (currentPart > 3) {
                    currentPart = 0;
                    day++;
                }
                break;
            case 7:
                player.displayStatus();
                break;
            case 8:
                gameRunning = false;
                std::cout << "\nThanks for playing!\n";
                break;
        }

        if (choice != 6 && choice != 8) {
            currentPart++;
            if (currentPart > 3) {
                currentPart = 0;
                day++;
            }
        }

        if (gameRunning) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

int main() {
    showTitle();

    int option = showMenu();

    if (option == 1) {
        startGame();
    } else if (option == 2) {
        std::cout << "Loading game...\n";
    } else {
        std::cout << "Quitting the game. Goodbye!\n";
    }

    return 0;
}
