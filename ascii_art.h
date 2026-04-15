#ifndef ASCII_ART_H
#define ASCII_ART_H

#include <vector>
#include <string>

bool loadAsciiArt(const std::string& fileName, std::vector<std::string>& linesOut);

std::vector<std::string> getAsciiArt(const std::string& artName, const std::vector<std::string>& fallback);

#endif // ASCII_ART_H