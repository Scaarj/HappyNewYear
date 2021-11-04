
#include <algorithm>
#include <boost/range/adaptors.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

using namespace std;

// std::cout << "\033[32m" << "Error!" << "\033[0m" << std::endl;

enum class ColorType {
  Green,
  White,
};

class Item {
public:
  Item() {}
  virtual ~Item() {}
  virtual void print() = 0;
  virtual int overall() = 0;
  virtual void decorate(int count) = 0;
};

class Symbol {
public:
  Symbol(char c) : _symbol(c) {}

  bool operator==(const Symbol &other) { return _symbol == other._symbol; }

protected:
  char _symbol;
};

class SingleItem : public Item, public Symbol {
public:
  SingleItem(char symbol) : Symbol(symbol) {}
};

void setColor(ColorType collor) {
  switch (collor) {
  case ColorType::Green:
    std::cout << "\033[32m";
    break;
  case ColorType::White:
    std::cout << "\033[0m";
    break;
  }
}

class Joy : public SingleItem {
public:
  Joy() : SingleItem('o') {}
  virtual ~Joy() {}
  virtual void print() {
    setColor(ColorType::White);
    std::cout << _symbol;
  }
  virtual int overall() { return 1; }
  virtual void decorate(int v) {}
};

class TreeItem : public SingleItem {
public:
  TreeItem() : SingleItem('*') {}
  virtual ~TreeItem() {}
  virtual void print() {
    setColor(ColorType::Green);
    std::cout << _symbol;
  }
  virtual int overall() { return 1; }
  virtual void decorate(int v) {
    if (v) {
      setColor(ColorType::White);
      _symbol = 'o';
    }
  }
};

class EmptyItem : public SingleItem {
public:
  EmptyItem() : SingleItem(' ') {}
  virtual ~EmptyItem() {}
  virtual void print() { std::cout << _symbol; }
  virtual int overall() { return 0; }
  virtual void decorate(int) {}
};

class TreeLine : public Item {
public:
  TreeLine(int offset, int width, int count) {
    int emptyCount = width - count;
    int halfEmptyCount = emptyCount / 2;

    for (int i = 0; i < offset + halfEmptyCount; ++i) {
      _items.push_back(std::unique_ptr<SingleItem>(new EmptyItem));
    }
    for (int i = 0; i < count; ++i) {
      _items.push_back(std::unique_ptr<SingleItem>(new TreeItem));
    }
    for (int i = 0; i < halfEmptyCount; ++i) {
      _items.push_back(std::unique_ptr<SingleItem>(new EmptyItem));
    }
  }

  virtual void print() override {
    for (const auto &it : _items) {
      it->print();
    }
    std::cout << std::endl;
  }

  virtual int overall() override {
    int sum = 0;
    for (const auto &it : _items) {
      sum += it->overall();
    }
    return sum;
  }

  virtual void decorate(int count) override {
    auto isTreeItem = [](const std::unique_ptr<SingleItem> &item) {
      TreeItem tree;
      return *(item.get()) == tree;
    };

    auto isEmptyElement = [](const std::unique_ptr<SingleItem> &item) {
      EmptyItem empty;
      return *(item.get()) == empty;
    };

    auto treeStartIt = std::find_if(_items.begin(), _items.end(), isTreeItem);
    auto treeEndIt = std::find_if(treeStartIt, _items.end(), isEmptyElement);
    int firstIndex = std::distance(_items.begin(), treeStartIt);
    int lastIndex = std::distance(_items.begin(), treeEndIt);

    std::cout << "lines overal " << overall() << " joy count " << count << endl;

    TreeItem treeItem;
    while (count) {
      int pos = rand() % (lastIndex - firstIndex) + firstIndex;
      if (*_items[pos].get() == treeItem) {
        _items[pos] = std::unique_ptr<SingleItem>(new Joy());
        count--;
      }
    }
  }

private:
  std::vector<std::unique_ptr<SingleItem>> _items;
};

class TreeSection : public Item {
public:
  TreeSection(int offset, int maxWidth, int start) {
    for (int i = start; i < ceil(maxWidth / 2) + 1; ++i) {
      int treeItemCount = i * 2 + 1;
      _lines.push_back(
          std::unique_ptr<Item>(new TreeLine(offset, maxWidth, treeItemCount)));
    }
  }

  virtual void print() override {
    for (const auto &it : _lines) {
      it->print();
    }
  }

  virtual int overall() override {
    int sum = 0;
    for (const auto &it : _lines) {
      sum += it->overall();
    }
    return sum;
  }

  virtual void decorate(int count) override {
    int sum = overall();
    std::cout << "section overal " << sum << " joy count " << count << endl;

    for (const auto &it : boost::adaptors::reverse(_lines)) {
      int linesSum = it->overall();
      float ratio = static_cast<float>(linesSum) / sum;
      int joyToSection = ceil(ratio * count);
      if (joyToSection > count) {
        joyToSection = count;
      }
      count -= joyToSection;
      it->decorate(joyToSection);
    }
  }

private:
  std::vector<std::unique_ptr<Item>> _lines;
};

class Tree : public Item {
public:
  Tree(int offset, int sectionCount, int maxWidth, int diff) {
    int temp = 2 * diff;
    int curWidth = maxWidth - sectionCount * temp;
    int start = 0;
    for (int i = 0; i < sectionCount; ++i) {
      auto ptr = std::unique_ptr<Item>(
          new TreeSection(offset - start, curWidth, start));
      _sections.push_back(std::move(ptr));
      curWidth += temp;
      start += diff;
    }
  }

  virtual void decorate(int count) override {
    int sum = overall();
    for (const auto &it : boost::adaptors::reverse(_sections)) {
      int sectionSum = it->overall();
      float ratio = static_cast<float>(sectionSum) / sum;
      int joyToSection = ceil(ratio * count);
      if (joyToSection > count) {
        joyToSection = count;
      }
      count -= joyToSection;
      it->decorate(joyToSection);
    }
  }

  virtual void print() override {
    for (const auto &it : _sections) {
      it->print();
    }
  }

  virtual int overall() override {
    int sum = 0;
    for (const auto &it : _sections) {
      sum += it->overall();
    }
    return sum;
  }

  int treeCount() { return overall(); }

  int joyCount() { return overall(); }

private:
  std::vector<std::unique_ptr<Item>> _sections;
};

int main() {
  srand(time(NULL));
  int offset = 50;
  int sectionCount = 4;
  int maxWidth = 55;
  int sectionDiff = 5;
  Tree tree(offset, sectionCount, maxWidth, sectionDiff);
  int treeCount = tree.overall();
  int joyCount = treeCount / 10;
  tree.decorate(joyCount);

  std::cout << "tree count " << tree.treeCount() << " joy count "
            << tree.joyCount() << std::endl;

  char c;
  while (std::cin >> c) {
    tree.print();

    if (c == 'q') {
      break;
    }
  }

  return 0;
}
