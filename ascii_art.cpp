#include "ascii_art.h"
#include <fstream>
#include <string>
#include <vector>

bool loadAsciiArt(const std::string& fileName, std::vector<std::string>& linesOut) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        linesOut.push_back(line);
    }
    return !linesOut.empty();
}

std::vector<std::string> getAsciiArt(const std::string& artName, const std::vector<std::string>& fallback) {
    std::vector<std::string> lines;
    if (loadAsciiArt("art/" + artName + ".dat", lines)) {
        return lines;
    }
    return fallback;
}