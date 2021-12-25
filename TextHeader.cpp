#include "TextHeader.h"

#include <CollorDrawer.h>
#include <iostream>

TextHeader::TextHeader(int offset) {
  std::string happyNewYear;
  happyNewYear.resize(offset);
  std::fill(happyNewYear.begin(), happyNewYear.begin() + offset, ' ');
  happyNewYear += "Happy New Year 2022!\n";

  std::string whiteTime;
  whiteTime.resize(offset + 4);
  std::fill(whiteTime.begin(), whiteTime.begin() + offset + 5, ' ');
  whiteTime += "White Team\n";

  _header.push_back(happyNewYear);
  _header.push_back(whiteTime);
  _header.push_back(std::string("\n"));
}

TextHeader::~TextHeader() {}

void TextHeader::print() {
  for (auto it : _header) {
    it.print();
  }
}
