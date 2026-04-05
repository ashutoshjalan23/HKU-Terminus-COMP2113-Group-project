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
#include "student.h"
#include "halls.h"
#include "ascii_art.h"

// ANSI color codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

const int field_width = 80;

std::vector<std::string> getTitleLines() {
    static const std::vector<std::string> defaultTitle = {
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

    return getAsciiArt("HKU_logo", defaultTitle);
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
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
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
        std::cout << "No sub-locations here." << std::endl;
        return;
    }
    for (const Location* child : current->children) {
        if (showLong) {
            std::cout << child->name << " - " << child->title << ": " << child->description << std::endl;
        } else {
            std::cout << child->name << std::endl;
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

void runLocationShell(Student& student) {
    Location* root = buildLocationTree();
    Location* current = root;
    std::string input;

    std::cout << "\nExplore HKU locations using commands like ls, cd, pwd, help, and exit." << std::endl;
    std::cout << "Try typing 'help' to get started." << std::endl;

    std::getline(std::cin, input); // clear leftover input
    while (true) {
        std::cout << "hku:" << current->getPath() << "$ ";
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
            printLocationListing(current, flag == "-l");
        } else if (command == "pwd") {
            std::cout << current->getPath() << std::endl;
        } else if (command == "cd") {
            std::string target;
            iss >> target;
            if (target.empty()) {
                current = root;
                continue;
            }
            Location* next = resolveLocation(current, target, root);
            if (next == nullptr) {
                std::cout << "No such location: " << target << std::endl;
            } else {
                current = next;
                std::cout << "Moved to " << current->title << " (" << current->getPath() << ")" << std::endl;
            }
        } else if (command == "look") {
            std::cout << current->title << " - " << current->description << std::endl;
            if (current->name == "library") {
                std::cout << "You can study here to increase your knowledge." << std::endl;
                student.study();
            } else if (current->name == "canteen") {
                std::cout << "A good place to eat and recover energy." << std::endl;
                student.eat();
            } else if (current->name == "garden") {
                std::cout << "Relaxing in the garden restores your stamina." << std::endl;
                student.rest();
            }
        } else if (command == "help") {
            std::cout << "Available commands:" << std::endl;
            std::cout << "  ls        - list locations in the current area" << std::endl;
            std::cout << "  ls -l     - list locations with descriptions" << std::endl;
            std::cout << "  cd <path> - move to another location (use .. to go up, / for root)" << std::endl;
            std::cout << "  pwd       - show current location path" << std::endl;
            std::cout << "  look      - learn more about the current location" << std::endl;
            std::cout << "  status    - show your student status" << std::endl;
            std::cout << "  exit      - leave the navigation shell" << std::endl;
        } else if (command == "status") {
            student.displayStatus();
        } else if (command == "exit" || command == "quit") {
            std::cout << "Exiting HKU navigation." << std::endl;
            break;
        } else {
            std::cout << "Unknown command: " << command << ". Type help for a list of commands." << std::endl;
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
    clearScreen();
    auto title = getTitleLines();

    int totalLines = static_cast<int>(title.size());
    if (totalLines == 0) {
        return;
    }

    int center = totalLines / 2;

    for (int offset = 0; offset <= center; ++offset) {
        clearScreen();
        for (int i = 0; i < totalLines; ++i) {
            if (i >= center - offset && i <= center + offset) {
                std::cout << std::right << std::setw(field_width) << title[i] << std::endl;
            } else {
                std::cout << std::right << std::setw(field_width) << std::string(title[i].length(), ' ') << std::endl;
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
    // Display hall options
    typeText("Please enter the number of the hall you want to stay in: ", 30);
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
    runLocationShell(s);
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