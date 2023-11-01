#include "TextHeader.h"

#include <cmath>
#include <ctime>
#include <iostream>

TextHeader::TextHeader(std::string whois, int offset)
    : _whois(whois + "\n")
{
    std::string happyNewYearLine;
    std::time_t time = std::time(nullptr);
    std::tm *now = std::localtime(&time);
    // NOTE: base 1900 + now + next year
    auto newYear = 1900 + now->tm_year + 1;

    happyNewYearLine.resize(offset);
    std::fill(happyNewYearLine.begin(), happyNewYearLine.begin() + offset, ' ');
    std::string happyNewYear{"Happy New Year " + std::to_string(newYear) + "!\n"};
    happyNewYearLine += happyNewYear;

    std::string honored;
    int delta = std::abs(static_cast<int>(happyNewYear.size() - _whois.size() + 1));
    delta = delta * (happyNewYear.size() > _whois.size() ? 1 : -1);
    auto spaceCount = offset + delta / 2;
    honored.resize(spaceCount);
    std::fill(honored.begin(), honored.begin() + spaceCount, ' ');
    honored += whois;

    _header.push_back(happyNewYearLine);
    _header.push_back(honored);
    _header.push_back(std::string("\n"));
}

TextHeader::~TextHeader() {}

void TextHeader::print()
{
    for (auto it : _header) {
        it.print();
    }
}
