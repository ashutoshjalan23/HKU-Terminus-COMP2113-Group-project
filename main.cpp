#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>
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
#include <termios.h>
#endif
#include "common.h"
#include "battle.h"

#include "student.h"
#include "halls.h"
#include "ascii_art.h"

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


// Global variables for split-screen layout
int g_left_row = 1;            // Current row for left side output

const  string st_johnsFile="Halls/stjohns.txt";
const   string shunhingFile="Halls/shunhing.txt";
const  string rc_leeFile="Halls/rclee.txt"; 
const  string simonFile="Halls/simon.txt";
const  string newcollegeFile="Halls/newcollege.txt";

Halls st_johns, shunhing, rc_lee, simon, newcollege;

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
        printLeftSide(std::string(RED) + "No sub-locations here." + RESET);
        return;
    }
    for (const Location* child : current->children) {
        if (showLong) {
            printLeftSide(std::string(GREEN) + child->name + RESET + " - " + BOLD + child->title + RESET + ": " + child->description);
        } else {
            printLeftSide(std::string(GREEN) + child->name + RESET);
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

//NEXT TWO MAP FUNCTION ARE ONLY FOR TESTING PURPOSES
void printMapTree(const Location* node, const Location* current, int depth = 0) {
    printLeftSide("");

    std::string indent;
    for (int i = 0; i < depth; ++i) {
        indent += "\t";
    }

    std::string line = indent;
    if (node == current) {
        line += BOLD;
    }
    line += node->title + " [" + node->name + "]";
    if (!node->children.empty()) {
        line += " ->";
    }
    if (node == current) {
        line += " ** CURRENT LOCATION **";
        line += RESET;
    }
    printLeftSide(line);

    if (depth > 1) {
        printLeftSide(indent + "\tActivities");
    }
    
    for (int i = 0; i < static_cast<int>(node->children.size()); ++i) {
        printMapTree(node->children[i], current, depth + 1);
    }
}

void showMap(Location* root, Location* current) {
    printLeftSide("Campus map:");
    printMapTree(root, current, 0);
}

void displayLocationArtOrDefault(const std::string& locationName, const std::string& color = "") {
    auto art = loadAsciiArt(locationName);
    if (art.empty()) {
        art = loadAsciiArt("HKU_logo");
    }

    displayAsciiArtRight(art, color);
}

//all the terminal logic
namespace {

enum class ShellKeyType {
    Character,
    Enter,
    Backspace,
    Tab,
    Left,
    Right,
    Up,
    Down,
    Delete,
    Escape,
    Unknown
};

struct ShellKey {
    ShellKeyType type = ShellKeyType::Unknown;
    char character = '\0';
};

struct ShellCompletionState {
    bool active = false;
    size_t tokenStart = 0;
    std::vector<std::string> suggestions;
    std::size_t suggestionIndex = 0;
};

struct ShellEditorState {
    std::string buffer;
    std::size_t cursor = 0;
    std::vector<std::string> history;
    int historyIndex = -1;
    std::string draftBuffer;
    ShellCompletionState completion;
};

#ifndef _WIN32
class TerminalRawMode {
public:
    TerminalRawMode() {
        if (tcgetattr(STDIN_FILENO, &originalState) == 0) {
            termios rawState = originalState;
            rawState.c_lflag &= static_cast<unsigned long>(~(ICANON | ECHO));
            rawState.c_iflag &= static_cast<unsigned long>(~(IXON | ICRNL));
            rawState.c_cc[VMIN] = 1;
            rawState.c_cc[VTIME] = 0;
            if (tcsetattr(STDIN_FILENO, TCSANOW, &rawState) == 0) {
                active = true;
            }
        }
    }

    ~TerminalRawMode() {
        if (active) {
            tcsetattr(STDIN_FILENO, TCSANOW, &originalState);
        }
    }

private:
    termios originalState{};
    bool active = false;
};
#endif

std::string buildShellPrompt(const Location* current) {
    return std::string(BOLD) + MAGENTA + "hku:" + CYAN + current->getPath() + MAGENTA + "$ " + RESET;
}

std::size_t visiblePromptWidth(const Location* current) {
    return 6 + current->getPath().size();
}

bool startsWith(const std::string& value, const std::string& prefix) {
    return value.size() >= prefix.size() && value.compare(0, prefix.size(), prefix) == 0;
}

void renderShellLine(int row, const Location* current, const std::string& buffer, std::size_t cursor) {
    updateTerminalLayout();
    clearLeftPaneRow(row);
    std::cout << buildShellPrompt(current) << buffer << std::flush;
    moveCursor(row, static_cast<int>(visiblePromptWidth(current) + cursor + 1));
    std::cout << std::flush;
}

void resetCompletion(ShellEditorState& editor) {
    editor.completion = ShellCompletionState{};
}

ShellKey readShellKey() {
    ShellKey key;

#ifdef _WIN32
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        int extended = _getch();
        switch (extended) {
            case 72: key.type = ShellKeyType::Up; break;
            case 80: key.type = ShellKeyType::Down; break;
            case 75: key.type = ShellKeyType::Left; break;
            case 77: key.type = ShellKeyType::Right; break;
            case 83: key.type = ShellKeyType::Delete; break;
            default: key.type = ShellKeyType::Unknown; break;
        }
        return key;
    }
#else
    char ch = '\0';
    if (read(STDIN_FILENO, &ch, 1) <= 0) {
        return key;
    }
#endif

    unsigned char code = static_cast<unsigned char>(
#ifdef _WIN32
        ch
#else
        ch
#endif
    );

    if (code == 13 || code == '\n') {
        key.type = ShellKeyType::Enter;
    } else if (code == 9) {
        key.type = ShellKeyType::Tab;
    } else if (code == 8 || code == 127) {
        key.type = ShellKeyType::Backspace;
    } else if (code == 27) {
#ifndef _WIN32
        char sequence[2] = {'\0', '\0'};
        if (read(STDIN_FILENO, &sequence[0], 1) > 0 && read(STDIN_FILENO, &sequence[1], 1) > 0 && sequence[0] == '[') {
            switch (sequence[1]) {
                case 'A': key.type = ShellKeyType::Up; break;
                case 'B': key.type = ShellKeyType::Down; break;
                case 'C': key.type = ShellKeyType::Right; break;
                case 'D': key.type = ShellKeyType::Left; break;
                case '3': {
                    char trailing = '\0';
                    if (read(STDIN_FILENO, &trailing, 1) > 0 && trailing == '~') {
                        key.type = ShellKeyType::Delete;
                    }
                    break;
                }
                default:
                    key.type = ShellKeyType::Escape;
                    break;
            }
        } else {
            key.type = ShellKeyType::Escape;
        }
#else
        key.type = ShellKeyType::Escape;
#endif
    } else if (std::isprint(code)) {
        key.type = ShellKeyType::Character;
        key.character = static_cast<char>(code);
    } else {
        key.type = ShellKeyType::Unknown;
    }

    return key;
}

void collectLocationCandidates(const Location* node, const std::string& prefix, std::vector<std::string>& output) {
    if (node == nullptr) {
        return;
    }

    for (const Location* child : node->children) {
        std::string candidate = prefix.empty() ? child->name : prefix + "/" + child->name;
        output.push_back(candidate);
        collectLocationCandidates(child, candidate, output);
    }
}

std::vector<std::string> buildCommandCandidates(const std::string& prefix) {
    const std::vector<std::string> commands = {
        "ls", "cd", "pwd", "look", "map", "clear", "help", "status", "exit", "quit"
    };

    std::vector<std::string> matches;
    for (const std::string& command : commands) {
        if (startsWith(command, prefix)) {
            matches.push_back(command);
        }
    }
    return matches;
}

std::vector<std::string> buildPathCandidates(Location* current, Location* root, const std::string& pathPrefix) {
    Location* baseNode = current;
    std::string relativePrefix = pathPrefix;

    if (!pathPrefix.empty() && pathPrefix.front() == '/') {
        baseNode = root;
        relativePrefix = pathPrefix.substr(1);
    }

    std::string basePath = relativePrefix;
    std::size_t slashPos = relativePrefix.find_last_of('/');
    if (slashPos != std::string::npos) {
        basePath = relativePrefix.substr(0, slashPos);
        baseNode = resolveLocation(baseNode, basePath, root);
        if (baseNode == nullptr) {
            return {};
        }
    } else {
        basePath.clear();
    }

    std::vector<std::string> rawCandidates;
    collectLocationCandidates(baseNode, basePath, rawCandidates);

    std::vector<std::string> filtered;
    for (const std::string& candidate : rawCandidates) {
        std::string visibleCandidate = pathPrefix.empty() ? candidate : (pathPrefix.front() == '/' ? "/" + candidate : candidate);
        if (startsWith(visibleCandidate, pathPrefix)) {
            filtered.push_back(visibleCandidate);
        }
    }

    std::sort(filtered.begin(), filtered.end());
    filtered.erase(std::unique(filtered.begin(), filtered.end()), filtered.end());
    return filtered;
}

struct CompletionQuery {
    bool pathMode = false;
    std::size_t tokenStart = 0;
    std::vector<std::string> suggestions;
};

CompletionQuery buildCompletionQuery(const std::string& buffer, std::size_t cursor, Location* current, Location* root) {
    CompletionQuery query;

    if (cursor > buffer.size()) {
        cursor = buffer.size();
    }

    std::size_t firstNonSpace = buffer.find_first_not_of(" \t");
    if (firstNonSpace == std::string::npos || cursor < firstNonSpace) {
        return query;
    }

    std::size_t firstSpace = buffer.find_first_of(" \t", firstNonSpace);
    std::string command = firstSpace == std::string::npos ? buffer.substr(firstNonSpace) : buffer.substr(firstNonSpace, firstSpace - firstNonSpace);

    if (command == "cd" && firstSpace != std::string::npos) {
        std::size_t argumentStart = buffer.find_first_not_of(" \t", firstSpace);
        if (argumentStart == std::string::npos) {
            argumentStart = cursor;
        }
        if (cursor < argumentStart) {
            return query;
        }

        query.pathMode = true;
        query.tokenStart = argumentStart;
        std::string prefix = buffer.substr(argumentStart, cursor - argumentStart);
        query.suggestions = buildPathCandidates(current, root, prefix);
        return query;
    }

    std::size_t tokenStart = cursor;
    while (tokenStart > firstNonSpace && !std::isspace(static_cast<unsigned char>(buffer[tokenStart - 1]))) {
        tokenStart--;
    }

    query.tokenStart = tokenStart;
    std::string prefix = buffer.substr(tokenStart, cursor - tokenStart);
    query.suggestions = buildCommandCandidates(prefix);
    return query;
}

void replaceBufferRange(std::string& buffer, std::size_t start, std::size_t end, const std::string& replacement, std::size_t& cursor) {
    if (start > end || start > buffer.size()) {
        return;
    }

    end = std::min(end, buffer.size());
    buffer.replace(start, end - start, replacement);
    cursor = start + replacement.size();
}

bool handleCompletion(ShellEditorState& editor, Location* current, Location* root) {
    if (editor.completion.active && !editor.completion.suggestions.empty()) {
        editor.completion.suggestionIndex = (editor.completion.suggestionIndex + 1) % editor.completion.suggestions.size();
        std::string replacement = editor.completion.suggestions[editor.completion.suggestionIndex];
        replaceBufferRange(editor.buffer, editor.completion.tokenStart, editor.cursor, replacement, editor.cursor);
        return true;
    }

    CompletionQuery query = buildCompletionQuery(editor.buffer, editor.cursor, current, root);
    if (query.suggestions.empty()) {
        return false;
    }

    editor.completion.active = true;
    editor.completion.tokenStart = query.tokenStart;
    editor.completion.suggestions = query.suggestions;
    editor.completion.suggestionIndex = 0;

    std::string replacement = editor.completion.suggestions[editor.completion.suggestionIndex];
    replaceBufferRange(editor.buffer, editor.completion.tokenStart, editor.cursor, replacement, editor.cursor);
    return true;
}

void applyHistoryMove(ShellEditorState& editor, int direction) {
    if (editor.history.empty()) {
        return;
    }

    if (direction < 0) {
        if (editor.historyIndex == -1) {
            editor.draftBuffer = editor.buffer;
            editor.historyIndex = static_cast<int>(editor.history.size()) - 1;
        } else if (editor.historyIndex > 0) {
            editor.historyIndex--;
        }

        editor.buffer = editor.history[editor.historyIndex];
        editor.cursor = editor.buffer.size();
        resetCompletion(editor);
        return;
    }

    if (editor.historyIndex == -1) {
        return;
    }

    if (editor.historyIndex < static_cast<int>(editor.history.size()) - 1) {
        editor.historyIndex++;
        editor.buffer = editor.history[editor.historyIndex];
    } else {
        editor.historyIndex = -1;
        editor.buffer = editor.draftBuffer;
    }

    editor.cursor = editor.buffer.size();
    resetCompletion(editor);
}

void insertCharacter(ShellEditorState& editor, char character) {
    if (editor.historyIndex != -1) {
        editor.historyIndex = -1;
        editor.draftBuffer.clear();
    }
    editor.buffer.insert(editor.cursor, 1, character);
    editor.cursor++;
    resetCompletion(editor);
}

void removeCharacterBeforeCursor(ShellEditorState& editor) {
    if (editor.cursor == 0) {
        return;
    }

    if (editor.historyIndex != -1) {
        editor.historyIndex = -1;
        editor.draftBuffer.clear();
    }
    editor.buffer.erase(editor.cursor - 1, 1);
    editor.cursor--;
    resetCompletion(editor);
}

void removeCharacterAtCursor(ShellEditorState& editor) {
    if (editor.cursor >= editor.buffer.size()) {
        return;
    }

    if (editor.historyIndex != -1) {
        editor.historyIndex = -1;
        editor.draftBuffer.clear();
    }
    editor.buffer.erase(editor.cursor, 1);
    resetCompletion(editor);
}

void printShellHelp() {
    printLeftSide(std::string(BOLD) + CYAN + "Available commands:" + RESET);
    printLeftSide(std::string(GREEN) + "  ls        " + RESET + "- list locations in the current area");
    printLeftSide(std::string(GREEN) + "  ls -l     " + RESET + "- list locations with descriptions");
    printLeftSide(std::string(GREEN) + "  cd <path> " + RESET + "- move to another location (use .. to go up, / for root)");
    printLeftSide(std::string(GREEN) + "  pwd       " + RESET + "- show current location path");
    printLeftSide(std::string(GREEN) + "  look      " + RESET + "- learn more about the current location");
    printLeftSide(std::string(GREEN) + "  map       " + RESET + "- show the full campus map");
    printLeftSide(std::string(GREEN) + "  status    " + RESET + "- show your student status");
    printLeftSide(std::string(GREEN) + "  clear     " + RESET + "- clear the terminal and redraw the shell");
    printLeftSide(std::string(GREEN) + "  exit      " + RESET + "- leave the navigation shell");
}

bool executeShellCommand(const std::string& input, Location*& current, Location* root, Student& student) {
    std::istringstream iss(input);
    std::string command;
    iss >> command;

    if (command == "ls") {
        std::string flag;
        iss >> flag;
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
            displayLocationArtOrDefault(current->name);
            return true;
        }

        Location* next = resolveLocation(current, target, root);
        if (next == nullptr) {
            printLeftSide(std::string(RED) + "No such location: " + target + RESET);
        } else {
            current = next;
            printLeftSide(std::string(GREEN) + "Moved to " + current->title + " (" + current->getPath() + ")" + RESET);
            displayLocationArtOrDefault(current->name);
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
    } else if (command == "clear") {
        clearScreen();
        g_left_row = 1;
        displayLocationArtOrDefault(current->name);
    } else if (command == "help") {
        printShellHelp();
    } else if (command == "status") {
        student.displayStatus();
    } else if (command == "exit" || command == "quit") {
        printLeftSide(std::string(YELLOW) + "Exiting HKU navigation. \n" + RESET);
        return false;
    } else {
        printLeftSide(std::string(RED) + "Unknown command: " + command + ". Type help for a list of commands." + RESET);
    }

    return true;
}

std::string readShellLine(Location* current, Location* root, int promptRow, ShellEditorState& editor) {
    renderShellLine(promptRow, current, editor.buffer, editor.cursor);

#ifndef _WIN32
    TerminalRawMode rawMode;
#endif

    while (true) {
        ShellKey key = readShellKey();
        switch (key.type) {
            case ShellKeyType::Character:
                insertCharacter(editor, key.character);
                break;
            case ShellKeyType::Backspace:
                removeCharacterBeforeCursor(editor);
                break;
            case ShellKeyType::Delete:
                removeCharacterAtCursor(editor);
                break;
            case ShellKeyType::Left:
                if (editor.cursor > 0) {
                    editor.cursor--;
                }
                resetCompletion(editor);
                break;
            case ShellKeyType::Right:
                if (editor.cursor < editor.buffer.size()) {
                    editor.cursor++;
                }
                resetCompletion(editor);
                break;
            case ShellKeyType::Up:
                applyHistoryMove(editor, -1);
                break;
            case ShellKeyType::Down:
                applyHistoryMove(editor, 1);
                break;
            case ShellKeyType::Tab:
                handleCompletion(editor, current, root);
                break;
            case ShellKeyType::Enter:
                std::cout << std::endl;
                if (!trim(editor.buffer).empty()) {
                    editor.history.push_back(trim(editor.buffer));
                }
                {
                    std::string submitted = trim(editor.buffer);
                    editor.buffer.clear();
                    editor.cursor = 0;
                    editor.historyIndex = -1;
                    editor.draftBuffer.clear();
                    resetCompletion(editor);
                    return submitted;
                }
            case ShellKeyType::Escape:
            case ShellKeyType::Unknown:
            default:
                break;
        }

        renderShellLine(promptRow, current, editor.buffer, editor.cursor);
    }
}

} // namespace

void runLocationShell(Student& student, int count) {
    Location* root = buildLocationTree();
    Location* current = root;
    ShellEditorState shellEditor;

    // Reset left-pane row tracking before any shell prompt rendering.
    g_left_row = 1;

    if (count == 0) {
        printLeftSide(std::string(CYAN) + "Chim Tat Wing: " + RESET + "Explore HKU locations using commands like" + RED + "  ls, cd, pwd, help, map and exit." + RESET);
        printLeftSide(std::string(CYAN) + "Try typing 'help' to get started." + RESET);
        printLeftSide(std::string(CYAN) + "Chim Tat Wing:" + RESET + " Type ls to see everywhere you can go" + RESET);

        while (true) {
            int promptRow = g_left_row;
            std::string input = readShellLine(current, root, promptRow, shellEditor);
            g_left_row = promptRow + 1;
            
            if (trim(input) == "ls") {
                printLocationListing(current);
                break;
            }
            
            printLeftSide(std::string(RED) + "Please type 'ls' to see the locations before proceeding." + RESET);
        }

        printLeftSide(std::string(CYAN) + "Chim Tat Wing:" + RESET + " Good now try cd to move to a location. Let's go to the main campus and meet your peers");

        while (true) {
            int promptRow = g_left_row;
            std::string input = readShellLine(current, root, promptRow, shellEditor);
            g_left_row = promptRow + 1;

            if (trim(input) == "cd main-campus") {
                break;
            }

            printLeftSide(std::string(RED) + "Please type 'cd main-campus' to move to the main campus before proceeding." + RESET);
        }

        current = resolveLocation(current, "main-campus", root);

        clearScreen();
        g_left_row = 1;

        printLeftSide(std::string(GREEN) + "Moved to " + current->title + " (" + current->getPath() + ")" + RESET);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printLeftSide(std::string(CYAN) + "Chim Tat Wing:" + RESET + " Oh! Meet Marcus, He is also a first year CDS student!");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

#ifdef _WIN32
        PlaySound(TEXT("audio/meet_marcus.wav"), NULL, SND_FILENAME | SND_ASYNC);
#else
        system("mpv audio/meet_marcus.wav > /dev/null 2>&1 &");
#endif

        auto art = loadAsciiArt("rival2");
        if (art.empty()) {
            printLeftSide(std::string(YELLOW) + "[ ASCII art file 'rival2.dat' not found in ./art/ directory ]" + RESET);
        } else {
            displayAsciiArtRightAnimated(art, GREEN, 40);
        }
    }

    printLeftSide(std::string(RED) + "Marcus:" + RESET + "Ugh! Another first year! You think you can survive in HKU? Let's see your CS skills! \n" + RESET);
    typeText(std::string(BOLD) + RED + "Marcus challenges you to a coding battle!" + RESET, 30);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    clearScreen();
    g_left_row = 1;
    displayLocationArtOrDefault(current->name);

    while (true) {
        int promptRow = g_left_row;
        std::string input = readShellLine(current, root, promptRow, shellEditor);
        g_left_row = promptRow + 1;

        if (trim(input).empty()) {
            continue;
        }

        if (!executeShellCommand(input, current, root, student)) {
            break;
        }
    }

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

void startGame() {
    // Default name and age, will be updated
    std::cout << "Starting a new game...\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearScreen();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    g_left_row = 1;
    
    printLeftSide(std::string(GREEN) + "Welcome to the prestigious " + CYAN + "University of Hong Kong!" + RESET + "You are about to embark on an exciting journey as a student at HKU.\nYour choices will shape your university experience, so choose wisely and enjoy your time at HKU!\n\n");
    printLeftSide(std::string(CYAN) + "Dr. Chim Tat Wing:" + RESET + " Hello there! Welcome to HKU. I'm Dr. Chim Tat Wing, your friendly advisor. I'm here to help you navigate your university life and make the most of your time here. Feel free to ask me anything or seek advice whenever you need it. Let's make your HKU experience unforgettable!\n\n");
    
    auto art = loadAsciiArt("HKU_logo");
    if (!art.empty()) {
        displayAsciiArtRight(art, CYAN);
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    printLeftSide(std::string(CYAN) + "Dr. Chim Tat Wing: " + RESET + "What's your name, student? ");
    
    std::string name;
    std::cin >> name;
   
    printLeftSide(std::string(CYAN) + "Dr. Chim Tat Wing: " + RESET + "Nice to meet you, " + name + "! How old are you? ");
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

    clearScreen();
    g_left_row = 1;
    runLocationShell(s,0);
}

// In main()
int main() {

    updateTerminalLayout();
    std::cout << YELLOW << "[ Recommended ] Please switch your terminal to full-screen mode for the best split-screen experience." << RESET << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.get(); 
     
    auto title = loadAsciiArt("HKU_logo");
    displayAsciiArtAnimated(title, 50);
    
    int option = show_start_Menu();
    
    if(option==1) {
        //start new game
        startGame();
    
    } else if(option==2) {
        // Load game
        std::cout << "Loading game...\n" << "Featuring Adding Soon\n";
        // ... rest of game
    
    } else {
        std::cout << "Quitting the game. Goodbye!\n";
    }
    // ... rest of game
    return 0;
}