#include "Tree.h"

#include "Pattern.h"
#include "TreeSection.h"
#include "TreeTrunkSection.h"

#include <boost/range/adaptors.hpp>

Tree::Tree() {}

Tree::Tree(int offset, int sectionCount, int maxWidth, int diff) {
  int temp = 2 * diff;
  int curWidth = maxWidth - sectionCount * temp;
  int start = 0;
  for (int i = 0; i < sectionCount; ++i) {
    _sections.push_back(
        std::make_unique<TreeSection>(offset - start, curWidth, start));
    curWidth += temp;
    start += diff;
  }

  _sections.push_back(std::make_unique<TreeTrunkSection>(4, curWidth - 1, 8));
}

Tree::Tree(const Tree &other) {
  _sections.reserve(other._sections.size());
  for (const auto &it : other._sections) {
    _sections.push_back(it->clone());
  }
}

void Tree::decorate(int count) {
  int sum = treeCount();
  int tempCount = count;
  for (const auto &it : boost::adaptors::reverse(_sections)) {
    int sectionSum = it->overall(Pattern::tree());
    float ratio = static_cast<float>(sectionSum) / sum;
    int joyToSection = ceil(ratio * count);
    if (joyToSection > tempCount) {
      joyToSection = tempCount;
    }
    tempCount -= joyToSection;
    it->decorate(joyToSection);
  }
}

void Tree::print() {
  for (const auto &it : _sections) {
    it->print();
  }
}

int Tree::treeWithJoyCount() { return overall(Pattern::treeAndJoy()); }

int Tree::treeCount() { return overall(Pattern::tree()); }

int Tree::joyCount() { return overall(Pattern::joy()); }

int Tree::overall(const std::vector<std::unique_ptr<Symbol>> &items) {
  int sum = 0;
  for (const auto &it : _sections) {
    sum += it->overall(items);
  }
  return sum;
}
