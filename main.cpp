#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif
#ifdef _WIN32
#include <conio.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif
#include "student.h"
#include "halls.h"
#include "ascii_art.h"
#include "battle.h"

// ANSI color codes - Sleek & Soothing Palette
#define RESET       "\033[0m"
#define GREEN       "\033[38;5;120m"  // Soft mint green
#define CYAN        "\033[38;5;110m"  // Soft teal
#define BOLD        "\033[1m"
#define RED         "\033[38;5;210m"  // Soft coral red
#define YELLOW      "\033[38;5;179m"  // Soft gold
#define MAGENTA     "\033[38;5;176m"  // Soft lavender
#define BLUE        "\033[38;5;117m"  // Soft sky blue
#define PURPLE      "\033[38;5;139m"  // Soft purple

const int field_width = 80;
const int SCREEN_WIDTH = 160;  // Total terminal width
const int LEFT_WIDTH = 100;     // Left side for text
const int RIGHT_START = 101;    // Right side starts at column 101

// Global variables for split-screen layout
int g_left_row = 1;            // Current row for left side output

// Forward declarations
void clearScreen();

// Position cursor at specific row and column
void moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

// Print text on the left side, respecting column boundaries
void printLeftSide(const std::string& text) {
    moveCursor(g_left_row, 1);
    // Truncate to LEFT_WIDTH
    std::string output = text.length() > LEFT_WIDTH ? text.substr(0, LEFT_WIDTH) : text;
   if(output==text) std::cout << output << std::flush;
   else{
        std::cout << output << "..." << std::flush; 
        g_left_row++;
        std::string remaining = text.substr(LEFT_WIDTH);
        printLeftSide(remaining); 
   }
    g_left_row++;
}
std::vector<std::string> loadAsciiArt(const std::string& filename) {
    std::vector<std::string> result;
    
    // Try multiple possible paths (both relative and absolute)
    std::vector<std::string> possiblePaths = {
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
        std::ifstream file(filepath);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                result.push_back(line);
            }
            file.close();
            return result;  // Successfully loaded
        }
    }
    
    // If we get here, file not found - show which paths were tried
    std::cerr << "Warning: Could not open ASCII art file: " << filename << ".dat" << std::endl;
    std::cerr << "Tried paths:" << std::endl;
    for (const auto& path : possiblePaths) {
        std::cerr << "  - " << path << std::endl;
    }
    return result;
}

// Generic function to display ASCII art with animation (expanding from center)
void displayAsciiArtAnimated(const std::vector<std::string>& lines, int delayMs = 50, const std::string& color = "") {
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
                    std::cout << color;
                }
                std::cout << lines[i];
                if (!color.empty()) {
                    std::cout << RESET;
                }
                std::cout << std::endl;
            } else {
                std::cout << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

// Generic function to display ASCII art without animation
void displayAsciiArt(const std::vector<std::string>& lines, const std::string& color = "") {
    if (!color.empty()) {
        std::cout << color;
    }
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }
    if (!color.empty()) {
        std::cout << RESET;
    }
}

// Display ASCII art on the right side with color
void displayAsciiArtRight(const std::vector<std::string>& lines, const std::string& color = "") {
    int row = 1;
    for (const auto& line : lines) {
        moveCursor(row, RIGHT_START);
        if (!color.empty()) {
            std::cout << color;
        }
        std::cout << line << RESET;
        row++;
    }
    std::cout << std::flush;
}

std::vector<std::string> getTitleLines() {
    auto lines = loadAsciiArt("HKU_logo");
     if (lines.empty()) {
        lines.push_back("[ ASCII art file 'HKU_logo.dat' not found in ./art/ directory ]");
    }
    return lines;
}

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
    bool skipAnimation = false;
    
    // Set stdin to non-blocking mode on Unix-like systems
    #ifndef _WIN32
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    #endif
    
    for (size_t i = 0; i < text.length(); ++i) {
        std::cout << text[i] << std::flush;
        
        // Check for input to skip animation
        #ifdef _WIN32
        if (_kbhit()) {
            _getch(); // Consume the key
            skipAnimation = true;
        }
        #else
        char c;
        if (read(STDIN_FILENO, &c, 1) > 0) {
            skipAnimation = true;
        }
        #endif
        
        if (skipAnimation) {
            // Print remaining text instantly
            for (size_t j = i + 1; j < text.length(); ++j) {
                std::cout << text[j];
            }
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    
    // Restore stdin to blocking mode on Unix-like systems
    #ifndef _WIN32
    int flags2 = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags2 & ~O_NONBLOCK);
    #endif
    
    std::cout << std::endl;
}

std::string trim(const std::string& str);

struct Location {
    std::string name;
    std::string title;
    std::string description;
    Location* parent = nullptr;
    std::vector<Location*> children;

    Location(const std::string& n, const std::string& t, const std::string& d)
        : name(n), title(t), description(d) {}

    void addChild(Location* child) {
        child->parent = this;
        children.push_back(child);
    }

    Location* findChild(const std::string& childName) const {
        for (Location* child : children) {
            if (child->name == childName) {
                return child;
            }
        }
        return nullptr;
    }

    std::string getPath() const {
        if (parent == nullptr) {
            return "/";
        }
        std::vector<std::string> path;
        const Location* current = this;
        while (current != nullptr && current->parent != nullptr) {
            path.push_back(current->name);
            current = current->parent;
        }
        std::string result;
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            result += "/" + *it;
        }
        return result.empty() ? "/" : result;
    }
};

Location* buildLocationTree() {
    Location* root = new Location("hku", "HKU", "The University of Hong Kong campus base.");

    Location* mainCampus = new Location("main-campus", "Main Campus", "The heart of HKU, where academic life begins.");
    Location* residential = new Location("residential-halls", "Residential Halls", "Where students live and build community.");
    Location* academic = new Location("academic-blocks", "Academic Blocks", "Lecture halls, laboratories, and study spaces.");
    Location* recreation = new Location("recreation", "Recreation", "Places to relax, eat, and connect with friends.");

    root->addChild(mainCampus);
    root->addChild(residential);
    root->addChild(academic);
    root->addChild(recreation);

    mainCampus->addChild(new Location("library", "HKU Library", "A quiet place full of books, computers, and study rooms."));
    mainCampus->addChild(new Location("student-centre", "Student Centre", "Student clubs, services, and bulletin boards are here."));
    mainCampus->addChild(new Location("ad-building", "Administration Building", "The administration hub for campus services."));

    academic->addChild(new Location("lecture-hall", "Lecture Hall", "Where lectures take place and classmates gather."));
    academic->addChild(new Location("science-park", "Science Park", "Cutting-edge research labs and innovation spaces."));
    academic->addChild(new Location("computer-lab", "Computer Lab", "A hub for coding, projects, and late-night study sessions."));

    residential->addChild(new Location("st-johns", "St. John’s College", "Historic college with active student traditions."));
    residential->addChild(new Location("shun-hing", "Shun Hing College", "A lively hall with plenty of social activities."));
    residential->addChild(new Location("rc-lee", "RC Lee Hall", "A modern hall close to both academics and leisure."));
    residential->addChild(new Location("simon", "Simon Hall", "Comfortable living and community-focused spaces."));
    residential->addChild(new Location("new-college", "New College", "A newer residence with lots of campus energy."));

    recreation->addChild(new Location("canteen", "HKU Canteen", "Eat delicious meals and catch up with friends."));
    recreation->addChild(new Location("garden", "Centennial Garden", "A peaceful garden for relaxation and fresh air."));
    recreation->addChild(new Location("sports-centre", "Sports Centre", "Play sports and stay fit between classes."));

    return root;
}

void printLocationListing(const Location* current, bool showLong = false) {
    if (current->children.empty()) {
        std::cout << RED << "No sub-locations here." << RESET << std::endl;
        return;
    }
    for (const Location* child : current->children) {
        if (showLong) {
            std::cout << GREEN << child->name << RESET << " - " << BOLD << child->title << RESET << ": " << child->description << std::endl;
        } else {
            std::cout << GREEN << child->name << RESET << std::endl;
        }
    }
}

Location* resolveLocation(Location* current, const std::string& path, Location* root) {
    if (path.empty() || path == ".") {
        return current;
    }
    if (path == "/") {
        return root;
    }

    Location* node = current;
    std::string token;
    std::istringstream iss(path);
    if (path.front() == '/') {
        node = root;
    }
    while (std::getline(iss, token, '/')) {
        if (token.empty() || token == ".") {
            continue;
        }
        if (token == "..") {
            if (node->parent != nullptr) {
                node = node->parent;
            }
            continue;
        }
        Location* next = node->findChild(token);
        if (next == nullptr) {
            return nullptr;
        }
        node = next;
    }
    return node;
}

void printMapTree(const Location* node, const Location* current, int depth = 0) {
    
    std::cout << std::endl;

    std::string indent;
    for (int i = 0; i < depth; ++i) {
        indent += "\t";
    }
        if (node == current) {
            std::cout << BOLD;
        }
        std::cout << indent << node->title << " [" << node->name << "]";
        
        if (!node->children.empty()) {
            std::cout << " ->";
        }
        
        if (node == current) {
            std::cout << " " << "** CURRENT LOCATION **" << RESET;
        }
        std::cout << std::endl;

    if (depth > 1)
        std::cout << indent << "\tActivities" << std::endl;
    
    for (int i = 0; i < static_cast<int>(node->children.size()); ++i) {
        printMapTree(node->children[i], current, depth + 1);
    }
}

void showMap(Location* root, Location* current) {
    std::cout << "Campus map:" << std::endl;
    printMapTree(root, current, 0);
}

void runLocationShell(Student& student, int count) {
    Location* root = buildLocationTree();
    Location* current = root;
    std::string input;
    if(count==0){
    std::cout << "\n" << CYAN<<"Chim Tat Wing: "<<RESET << "Explore HKU locations using commands like"<<RED<<"  ls, cd, pwd, help, map and exit." << RESET << std::endl;
    std::cout << CYAN << "Try typing 'help' to get started." << RESET << std::endl;
    std::cout<<CYAN<<"Chim Tat Wing: "<<RESET<<"Type ls to see everywhere you can go"<<RESET<<std::endl;
    std::cout << BOLD << MAGENTA << "hku:" << CYAN << current->getPath() << MAGENTA << "$ " << RESET;
    std::getline(std::cin, input); // clear leftover input
    while(input!="ls"){
        std::cout<<RED<<"Please type 'ls' to see the locations before proceeding."<<RESET<<std::endl;
std::cout << BOLD << MAGENTA << "hku:" << CYAN << current->getPath() << MAGENTA << "$ " << RESET;
    std::getline(std::cin, input); // clear leftover input
    }

    
        printLocationListing(current);
    
    std::cout<<CYAN<<"Chim Tat Wing:"<<RESET<<"Good now try cd to move to a location. Let's go to the main campus and meet your peers"<<std::endl;
    while(input!="cd main-campus"){
        std::cout<<RED<<"Please type 'cd main-campus' to move to the main campus before proceeding."<<RESET<<std::endl;
        std::cout << BOLD << MAGENTA << "hku:" << CYAN << current->getPath() << MAGENTA << "$ " << RESET;
        std::getline(std::cin, input);
    }
    current = resolveLocation(current, "main-campus", root);
    
    // Split-screen display for meeting Marcus
    clearScreen();
    g_left_row = 1;  // Reset left-side row counter
    
    printLeftSide(std::string(GREEN) + "Moved to " + current->title + " (" + current->getPath() + ")" + RESET);
    printLeftSide(std::string(CYAN) + "Chim Tat Wing:" + RESET + " Oh! Meet Marcus, He is also a first year CDS student!");
    auto art = loadAsciiArt("rival2");
    if (art.empty()) {
        printLeftSide(std::string(YELLOW) + "[ ASCII art file 'rival2.dat' not found in ./art/ directory ]" + RESET);
    } else {
        // Display ASCII art on the right side of the screen
        displayAsciiArtRight(art, GREEN);
    }
    // Dialogue and ASCII art remain on screen - shell continues below

}
    while (true) {
        // Continue on the left side for shell prompt
        std::string prompt = std::string(BOLD) + MAGENTA + "hku:" + CYAN + current->getPath() + MAGENTA + "$ " + RESET;
        moveCursor(g_left_row, 1);
        std::cout << prompt << std::flush;
        g_left_row++;
        
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        if (input.empty()) {
            continue;
        }

        std::istringstream iss(input);
        std::string command;
        iss >> command;

        if (command == "ls") {
            std::string flag;
            iss >> flag;
            // For ls, we need to modify printLocationListing to use positioned printing temporarily
            if (current->children.empty()) {
                printLeftSide(std::string(RED) + "No sub-locations here." + RESET);
            } else {
                for (const Location* child : current->children) {
                    if (flag == "-l") {
                        std::string listing = std::string(GREEN) + child->name + RESET + " - " + BOLD + child->title + RESET + ": " + child->description;
                        printLeftSide(listing);
                    } else {
                        printLeftSide(std::string(GREEN) + child->name + RESET);
                    }
                }
            }
        } else if (command == "pwd") {
            printLeftSide(std::string(GREEN) + current->getPath() + RESET);
        } else if (command == "cd") {
            std::string target;
            iss >> target;
            if (target.empty()) {
                current = root;
                continue;
            }
            Location* next = resolveLocation(current, target, root);
            if (next == nullptr) {
                printLeftSide(std::string(RED) + "No such location: " + target + RESET);
            } else {
                current = next;
                printLeftSide(std::string(GREEN) + "Moved to " + current->title + " (" + current->getPath() + ")" + RESET);
            }
        } else if (command == "look") {
            printLeftSide(std::string(BOLD) + CYAN + current->title + RESET + " - " + current->description);
            if (current->name == "library") {
                printLeftSide(std::string(YELLOW) + "You can study here to increase your knowledge." + RESET);
                student.study();
            } else if (current->name == "canteen") {
                printLeftSide(std::string(YELLOW) + "A good place to eat and recover energy." + RESET);
                student.eat();
            } else if (current->name == "garden") {
                printLeftSide(std::string(YELLOW) + "Relaxing in the garden restores your stamina." + RESET);
                student.rest();
            }
        } else if (command == "map") {
            showMap(root, current);
        } else if (command == "clear"){
            clearScreen();
            g_left_row = 1;
        }
        else if (command == "help") {
            printLeftSide(std::string(BOLD) + CYAN + "Available commands:" + RESET);
            printLeftSide(std::string(GREEN) + "  ls        " + RESET + "- list locations in the current area");
            printLeftSide(std::string(GREEN) + "  ls -l     " + RESET + "- list locations with descriptions");
            printLeftSide(std::string(GREEN) + "  cd <path> " + RESET + "- move to another location (use .. to go up, / for root)");
            printLeftSide(std::string(GREEN) + "  pwd       " + RESET + "- show current location path");
            printLeftSide(std::string(GREEN) + "  look      " + RESET + "- learn more about the current location");
            printLeftSide(std::string(GREEN) + "  map       " + RESET + "- show the full campus map");
            printLeftSide(std::string(GREEN) + "  status    " + RESET + "- show your student status");
            printLeftSide(std::string(GREEN) + "  exit      " + RESET + "- leave the navigation shell");
        } else if (command == "status") {
            student.displayStatus();
        } else if (command == "exit" || command == "quit") {
            printLeftSide(std::string(YELLOW) + "Exiting HKU navigation." + RESET);
            break;
        } else {
            printLeftSide(std::string(RED) + "Unknown command: " + command + ". Type help for a list of commands." + RESET);
        }
    }

    // Clean up allocated locations.
    std::vector<Location*> stack{root};
    while (!stack.empty()) {
        Location* node = stack.back();
        stack.pop_back();
        for (Location* child : node->children) {
            stack.push_back(child);
        }
        delete node;
    }
}

void showAnimatedTitle() {
    auto title = getTitleLines();
    displayAsciiArtAnimated(title, 50);
}

int show_start_Menu() {
    
    std::cout << "\n\n";
    std::cout << BOLD << CYAN << "Welcome to HKU Terminus!" << RESET << "\n";
    std::cout << BOLD << CYAN << "Main Menu" << RESET << "\n";
    std::cout << "1. " << GREEN << "New Game" << RESET << "\n";
    std::cout << "2. " << GREEN << "Load Game" << RESET << "\n";
    std::cout << "3. " << GREEN << "Quit" << RESET << "\n";
    std::cout << "Enter your choice (1-3): ";
    
    int choice;
    if (!(std::cin >> choice) || (choice < 1 || choice > 3)){
        clearScreen();
        std::cout << "Invalid choice. Press Enter to try again...";
        cin.clear(); // Reset error flags
        std::cin.ignore();
        choice = show_start_Menu();
    }
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

void startGame() {
    // Default name and age, will be updated
    std::cout << "Starting a new game...\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearScreen();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    g_left_row = 1;
    
    printLeftSide(std::string(GREEN) + "Welcome to the prestigious " + CYAN + "University of Hong Kong!" + RESET + "    You are about to embark on an exciting journey as a student at HKU.\nYour choices will shape your university experience, so choose wisely and enjoy your time at HKU!\n\n");
    printLeftSide(std::string(CYAN) + "Dr. Chim Tat Wing:" + RESET + " Hello there! Welcome to HKU. I'm Dr. Chim Tat Wing, your friendly advisor. I'm here to help you navigate your university life and make the most of your time here. Feel free to ask me anything or seek advice whenever you need it. Let's make your HKU experience unforgettable!\n\n");
    
    auto art = loadAsciiArt("HKU_logo");
    if (art.empty()) {
        printLeftSide(std::string(YELLOW) + "[ ASCII art file 'HKU_logo.dat' not found in ./art/ directory ]" + RESET);
    } else {
        displayAsciiArtRight(art, CYAN);
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    printLeftSide(std::string(CYAN) + "Dr. Chim Tat Wing: " + RESET + "What's your name, student?");
    
    std::string name;
    std::cin >> name;
   
    printLeftSide(std::string(CYAN) + "Dr. Chim Tat Wing: " + RESET + "Nice to meet you, " + name + "! How old are you?");
    int age;
    std::cin >> age;       
    printLeftSide(std::string(CYAN) + "Dr. Chim Tat Wing: " + RESET + "Great! So you're " + std::to_string(age) + " years old. Let's get you started on your university journey. Remember, I'm here to help you along the way, so don't hesitate to reach out if you need any advice or assistance. Good luck, " + name + "!");
    Student s(name, age);

    printLeftSide(std::string(CYAN) + "Dr. Chim Tat Wing:" + RESET + " Now that you've created your student profile, it's time to choose a hall to stay in. Each hall has its own unique atmosphere and facilities, so choose wisely! Here are the available halls:");
    printLeftSide("(1) St. Johns College");
    printLeftSide("(2) Shun Hing College");
    printLeftSide("(3) RC Lee Hall");
    printLeftSide("(4) Simon Hall");
    printLeftSide("(5) New College");
    printLeftSide("Choose the number to get more information:");
    // Display hall options
    std::cout << "Enter your choice (1-5): ";
    int hallChoice;
    std::cin >> hallChoice;

    Halls* selectedHall = nullptr;
    switch (hallChoice) {
        case 1:
            selectedHall = &st_johns;
            break;
        case 2:
            selectedHall = &shunhing;
            break;
        case 3:
            selectedHall = &rc_lee;
            break;
        case 4:
            selectedHall = &simon;
            break;
        case 5:
            selectedHall = &newcollege;
            break;
        default:
            std::cout << "That hall option is not recognized. You will still explore HKU locations." << std::endl;
            break;
    }

    if (selectedHall != nullptr) {
        selectedHall->showHall();
        std::cout << "Would you like to move in to this hall? (y/n): ";
        std::string confirm;
        std::cin >> confirm;
        if (!confirm.empty() && (confirm[0] == 'y' || confirm[0] == 'Y')) {
            selectedHall->choose(s);
        } else {
            std::cout << "You decided to delay your move-in and explore HKU first." << std::endl;
        }
    }

    std::cout << "\nWelcome to the HKU navigation shell. You can move around campus using commands like ls, cd, and pwd." << std::endl;
    runLocationShell(s,0);
}

// In main()
int main() {

    hall_init(st_johns, st_johnsFile);
    hall_init(shunhing, shunhingFile);  
    hall_init(rc_lee, rc_leeFile);
    hall_init(simon, simonFile);
    hall_init(newcollege, newcollegeFile);  
     
    showAnimatedTitle();
    int option = show_start_Menu();
    
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