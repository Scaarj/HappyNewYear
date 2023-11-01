#include "TreeSection.h"

#include <algorithm>
#include <cmath>

#include "Pattern.h"
#include "TreeLine.h"

TreeSection::TreeSection(int offset, int maxWidth, int start) {
  for (int i = start; i < ceil(maxWidth / 2) + 1; ++i) {
    int treeItemCount = i * 2 + 1;
    _lines.push_back(
        std::make_unique<TreeLine>(offset, maxWidth, treeItemCount));
  }
}

TreeSection::TreeSection(const TreeSection &other) {
  _lines.reserve(other._lines.size());
  for (const auto &it : other._lines) {
    _lines.push_back(it->clone());
  }
}

TreeSection &TreeSection::operator=(const TreeSection &other) { return *this; }

void TreeSection::print() {
  for (const auto &it : _lines) {
    it->print();
  }
}

int TreeSection::overall(const std::vector<std::unique_ptr<Symbol>> &items) {
  int sum = 0;
  for (const auto &it : _lines) {
    sum += it->overall(items);
  }
  return sum;
}

void TreeSection::decorate(int count) {
  int sum = overall(Pattern::tree());
  int tempCount = count;
  for (const auto &it : _lines) {
    int linesSum = it->overall(Pattern::tree());
    float ratio = static_cast<float>(linesSum) / sum;
    int joyToSection = ceil(ratio * count);
    if (joyToSection > tempCount) {
      joyToSection = tempCount;
    }
    tempCount -= joyToSection;
    it->decorate(joyToSection);
  }
}

std::unique_ptr<Item> TreeSection::clone() {
  return std::make_unique<TreeSection>(*this);
}
