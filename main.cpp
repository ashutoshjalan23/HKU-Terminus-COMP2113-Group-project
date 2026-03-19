#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <string>
#include "student.h"

// ANSI color codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

const int field_width = 80;

void clearScreen() {
    system("clear");
}

void typeText(const std::string& text, int delayMs = 10) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << std::endl;
}

void LS(Student s){
    std::cout<<"Locations"<<std::endl;
    std::cout<<"Library"<<std::endl;   
}

void showAnimatedTitle() {
    clearScreen();
    std::string title[] = {
        ".....:*******************************************************:.....",
        ".....:*****************************+-#*++**+==***************:.....",
        ".....:*****-#****#-----=***#=:-=+**+=-:-++******#************:.....",
        ".....:***-=-*+****=*+==+=+#:=********+*==++=-====+=+-*=+*****:.....",
        ".....:***=:-#***+++=+*-:***#=:==-::--=+**#***********=+***##*:.....",
        ".....:*****=-***+-#*****===+****+==---:::::::---=====-=+*****:.....",
        ".....:****#=--+*#==*#**==---:--:-:----=-----::+*######*******:.....",
        ".....:******=---+%:=-=-*=::-:-:--***=-:-*-:---:---==--:--*#**:.....",
        ".....:*******#=++**-*++=----=+******+-:-=**====++++++++---***:.....",
        ".....:**#-:*##*%##=*-:-:*****#=*****=-:---*************+--***:.....",
        ".....:***#==*-+=-------*******-=:===*-*+*************+-==*#**:.....",
        ".....:**********#*#*#********#**%*******************#**#*****:.....",
        ".....:***************************#***************************:.....",
        ".....:*********************+=--+*#*=....:=*******************:.....",
        ".....:**********-==+.............:.............:=*==*********:.....",
        ".....:***+**+***=::+...........................-====*********:.....",
        ".....:**********=::+....*..:*=*....:==*%-#==#:.-====*********:.....",
        ".....:****+*****=:-+..*=#:=++%+=....*--%.*=-%..-====*********:.....",
        ".....:**********=::+.:=+*:.=%+*:....*==%:*==%..-====*********:.....",
        "......******+***=::+...::::.=%*.....:.*%*:..+:.-====*********......",
        "......+**+******=:-=......................-....-====********=......",
        "......:#*****+**=::+...:#.:=........-%=.::#::..-====*******#:......",
        ".......#***+****=:-=..#=%+=+=*--...:=-+:**+*=..-====********.......",
        ".......:#*******=:-=.:=*+:+:*-*....:-#:++==:::.-====******#........",
        "........=*******=:-=.......:...............::..=====******=........",
        ".........***+***=:-=........:::.....:--:.......=====******.........",
        "..........#*****=:=*+-:=*+=======*========+***+=+===*****.:=:......",
        ".....=+*+*+#****=+=============*###*=============++=***%*+===+=....",
        "....===...:+%**#==============-*****===============+*#%-....--=-...",
        "...=:.=.:*=-.*#****************=###+****************%=..-++:+:.==..",
        ".:*:...*+..+.:*#****************###*****************#..--.:*:...:+:",
        "*:..-+=:-+..#+**:#***+**+**+*********************#:*-*+:.*:--::...*",
        "+::=:*.-+:-+:==...:**********+****************#*:...:+=+:.+::..:.:=",
        ".=+.:+==+.+=.*=......=%**********#**********%=......*=.:*:.==:+:+=.",
        "...==.:#:*.-+=::=*-....:=****+************=:....=+=::=#:.==::.+=...",
        ".....==::...*:*.=:::++-::..:+****#****+:..::-++::+-:+..+:..:==.....",
        ".......:*:.=.=:=:*+.*==-::-=**********+=-::-..=:+.*--*=:.-+:.......",
        "..........==-:===.+*..#..*.:+....===:=*-:..:*::.=-:=..==-..........",
        ".............:#=..::.=:.:=-+*::-.+*+..=:.....*-...:**:.............",
        "................:-===:..-::.-=...+-::.:=.....:===-.................",
        ".......................=+*+==-:::::::-==**+-......................."
    };

    // Fade effect from center
    int totalLines = sizeof(title) / sizeof(title[0]);
    int center = totalLines / 2;

    for (int offset = 0; offset <= center; ++offset) {
        clearScreen();
        for (int i = 0; i < totalLines; ++i) {
            if (i >= center - offset && i <= center + offset) {
                std::cout <<std::right<<std::setw(field_width) <<title[i] << std::endl;
            } else {
                std::cout <<std::right<<std::setw(field_width) <<std::string(title[i].length(), ' ') << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
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
void showRightJustifiedLogo(const std::string& logo, int screenWidth) {
    std::istringstream logoStream(logo);
    std::string line;
    while (std::getline(logoStream, line)) {
        std::cout << std::setw(screenWidth) << line << std::endl;
    }
}

int startMenu() {
    showAnimatedTitle();
    int choice;
    do {
        choice = showMenu();
        if (choice < 1 || choice > 3) {
            std::cout << "Invalid choice. Press Enter to try again...";
            std::cin.ignore();
            std::cin.get();
            clearScreen();
            showAnimatedTitle(); // re-show title? or just menu
        }
    } while (choice < 1 || choice > 3);
    return choice;
}

void startGame() {
    // Default name and age, will be updated
    std::cout << "Starting a new game...\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearScreen();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    typeText("Welcome to the prestigious " CYAN "University of Hong Kong!" RESET "    You are about to embark on an exciting journey as a student at HKU.\nYour choices will shape your university experience, so choose wisely and enjoy your time at HKU!\n\n", 30);
    typeText(CYAN "Dr. Chim Tat Wing:" RESET " Hello there! Welcome to HKU. I'm Dr. Chim Tat Wing, your friendly advisor. I'm here to help you navigate your university life and make the most of your time here. Feel free to ask me anything or seek advice whenever you need it. Let's make your HKU experience unforgettable!\"\n\n", 30);
    typeText(CYAN "Dr. Chim Tat Wing: " RESET "What's your name, student?", 30);

    std::string name;
    std::cin >> name;
   
    typeText(CYAN "Dr. Chim Tat Wing: " RESET "Nice to meet you, " + name + "! How old are you?\n", 30);
    int age;
    std::cin >> age;       
    typeText(CYAN "Dr. Chim Tat Wing: " RESET "Great! So you're " + std::to_string(age) + " years old. Let's get you started on your university journey. Remember, I'm here to help you along the way, so don't hesitate to reach out if you need any advice or assistance. Good luck, " + name + "!\n", 30);
    Student s(name, age);

    typeText(CYAN"Dr. Chim Tat Wing:" RESET " Now that you've created your student profile, it's time to choose a hall to stay in. Each hall has its own unique atmosphere and facilities, so choose wisely! Here are the available halls:\n \n St. Johns College : 50,000HKD \n Lap Chee College: 30,000HKD \n RC Lee Hall: 25,000HKD \n ", 30);
    // Display hall options (this will be implemented later)
    typeText("Please enter the name of the hall you want to stay in: ", 30);
    std::string hallChoice;
    std::cin >> hallChoice;


}

// In main()
int main() {
     
    
    int option = startMenu();
    
    if(option==1) {
        //start new game
        startGame();
    } else if(option==2) {
        // Load game
        std::cout << "Loading game...\n";
        // ... rest of game
    } else {
        std::cout << "Quitting the game. Goodbye!\n";
    }
    // ... rest of game
    return 0;
}