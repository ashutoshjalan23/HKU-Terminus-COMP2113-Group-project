#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include "student.h"
#include "halls.h"

// ANSI color codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

const int field_width = 80;

const  string st_johnsFile="Halls/stjohns.txt";
const   string shunhingFile="Halls/shunhing.txt";
const  string rc_leeFile="Halls/rclee.txt"; 
const  string simonFile="Halls/simon.txt";
const  string newcollegeFile="Halls/newcollege.txt";

 Halls st_johns, shunhing, rc_lee, simon, newcollege;

 
  
    
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

// Helper function to trim whitespace
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Remove all non-digit characters (e.g. currency symbols, commas)
std::string removeNonNumeric(const std::string& str) {
    std::string out;
    for (unsigned char c : str) {
        if (std::isdigit(c)) out.push_back(static_cast<char>(c));
    }
    return out;
}

void hall_init(Halls &h, const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string name, description, location, feesStr;
    int fees;
    // Read required lines and validate
    if (!std::getline(file, name) || !std::getline(file, feesStr)
        || !std::getline(file, description) || !std::getline(file, location)) {
        std::cerr << "Error: Malformed or incomplete file " << filename << std::endl;
        return;
    }

    // Trim whitespace
    name = trim(name);
    feesStr = trim(feesStr);
    description = trim(description);
    location = trim(location);

    // Remove currency symbols (e.g. "$", "HK$") and other non-digits
    feesStr = removeNonNumeric(feesStr);
    if (feesStr.empty()) {
        std::cerr << "Error: No numeric fees found in file " << filename << std::endl;
        return;
    }

    try {
        fees = std::stoi(feesStr); // Convert cleaned string to integer
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid fees value in file " << filename << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Fees value out of range in file " << filename << std::endl;
        return;
    }

    h = Halls(name, description, fees, location);
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

    typeText(CYAN"Dr. Chim Tat Wing:" RESET " Now that you've created your student profile, it's time to choose a hall to stay in. Each hall has its own unique atmosphere and facilities, so choose wisely! Here are the available halls:\n \n (1) St. Johns College \n (2) Shun Hing College \n (3) RC Lee Hall \n (4) Simon Hall \n (5) New College \n \n Choose the number to get more information ", 30);
    // Display hall options (this will be implemented later)
    typeText("Please enter the name of the hall you want to stay in: ", 30);
    int hallChoice;
    std::cin >> hallChoice;

    switch (hallChoice)
    {
    case 1:
        st_johns.showHall(st_johns);
        break;
    case 2:
        shunhing.showHall(shunhing);
        break;
    case 3:
        rc_lee.showHall(rc_lee);    
        break;
    case 4: 
        simon.showHall(simon);    
        break;  
    case 5: 
        newcollege.showHall(newcollege);    
        break;
    default:
        break;
    }


}

// In main()
int main() {
    

    

     hall_init(st_johns, st_johnsFile);
    hall_init(shunhing, shunhingFile);  
    hall_init(rc_lee, rc_leeFile);
    hall_init(simon, simonFile);
    hall_init(newcollege, newcollegeFile);  
     
    
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