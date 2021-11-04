
#include <algorithm>
#include <boost/range/adaptors.hpp>
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include <vector>

enum class ColorType : int {
  Green = 0,
  White = 1,
  Yellow = 2,
  Red = 3,
  Blue = 4,
  Magenta = 5,
  Cyan = 6,
};

void setColor(ColorType color) {
  switch (color) {
  case ColorType::Red:
    std::cout << "\033[31m";
    break;
  case ColorType::Green:
    std::cout << "\033[32m";
    break;
  case ColorType::Yellow:
    std::cout << "\033[33m";
    break;
  case ColorType::Blue:
    std::cout << "\033[34m";
    break;
  case ColorType::Magenta:
    std::cout << "\033[35m";
    break;
  case ColorType::Cyan:
    std::cout << "\033[36m";
    break;
  case ColorType::White:
    std::cout << "\033[37m";
    break;
  }
}

class GlobalColorController {
public:
  enum class RejimeType : int {
    None,
    OneColor,
    Snake,
    Random,
    Running,
  };

public:
  static void setRejime(RejimeType rejime) { _rejime = rejime; }

  static void nextRejime() {
    switch (_rejime) {
    case RejimeType::None:
      setRejime(RejimeType::OneColor);
      break;
    case RejimeType::OneColor:
      setRejime(RejimeType::Snake);
      break;
    case RejimeType::Snake:
      setRejime(RejimeType::Random);
      break;
    case RejimeType::Random:
      setRejime(RejimeType::None);
      break;
    default:
      break;
    }
  }

  static void animate() {
    switch (_rejime) {
    case RejimeType::None:
      setColor(ColorType::White);
      break;
    case RejimeType::OneColor:
      oneColor();
      break;
    case RejimeType::Random:
      random();
      break;
    case RejimeType::Snake:
      snake();
      break;
    case RejimeType::Running:
      running();
      break;
    default:
      break;
    }
    _complete = false;
  }

  static void oneCycleComplete() {
    _iterration++;
    _complete = true;
  }

  static void oneColor() {
    setColor(static_cast<ColorType>(_iterration % 5 + 1));
  }

  static void random() {
    int r = rand() % 6;
    setColor(static_cast<ColorType>(r));
  }

  static void running() {}

  static void snake() {
    static int counter = 0;
    setColor(static_cast<ColorType>(counter % 6));
    counter++;
  }

private:
  static RejimeType _rejime;
  static bool _complete;
  static int _iterration;
};

GlobalColorController::RejimeType GlobalColorController::_rejime =
    GlobalColorController::RejimeType::None;
bool GlobalColorController::_complete = true;
int GlobalColorController::_iterration = 0;

class SingleItem;

class Item {
public:
  Item() {}
  virtual ~Item() {}
  virtual void print() = 0;
  virtual int
  overall(const std::vector<std::unique_ptr<SingleItem>> &items) = 0;
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

class Joy : public SingleItem {
public:
  Joy() : SingleItem('o') {}
  virtual ~Joy() {}
  virtual void print() {
    GlobalColorController::animate();
    std::cout << _symbol;
  }
  virtual int overall(const std::vector<std::unique_ptr<SingleItem>> &items) {
    auto isJoy = [](const std::unique_ptr<SingleItem> &item) {
      Joy joy;
      return (*item.get()) == joy;
    };

    if (std::find_if(items.begin(), items.end(), isJoy) != items.end()) {
      return 1;
    }
    return 0;
  }

  virtual void decorate(int) {}
};

class TreeItem : public SingleItem {
public:
  TreeItem() : SingleItem('*') {}
  virtual ~TreeItem() {}
  virtual void print() {
    setColor(ColorType::Green);
    std::cout << _symbol;
  }

  virtual int overall(const std::vector<std::unique_ptr<SingleItem>> &items) {
    auto isTree = [](const std::unique_ptr<SingleItem> &item) {
      TreeItem treeItem;
      return (*item.get()) == treeItem;
    };

    if (std::find_if(items.begin(), items.end(), isTree) != items.end()) {
      return 1;
    }
    return 0;
  }

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

  virtual int overall(const std::vector<std::unique_ptr<SingleItem>> &items) {
    auto isEmpty = [](const std::unique_ptr<SingleItem> &item) {
      EmptyItem emptyItem;
      return (*item.get()) == emptyItem;
    };

    if (std::find_if(items.begin(), items.end(), isEmpty) != items.end()) {
      return 1;
    }
    return 0;
  }

  virtual void decorate(int) {}
};

class Pattern {
public:
  static std::vector<std::unique_ptr<SingleItem>> &tree() {
    static std::vector<std::unique_ptr<SingleItem>> items;
    items.push_back(std::make_unique<TreeItem>());
    return items;
  }

  static std::vector<std::unique_ptr<SingleItem>> &joy() {
    static std::vector<std::unique_ptr<SingleItem>> items;
    items.push_back(std::make_unique<Joy>());
    return items;
  }

  static std::vector<std::unique_ptr<SingleItem>> &treeAndJoy() {
    static std::vector<std::unique_ptr<SingleItem>> items;
    items.push_back(std::make_unique<TreeItem>());
    items.push_back(std::make_unique<Joy>());
    return items;
  }
};

class TreeLine : public Item {
public:
  TreeLine(int offset, int width, int count) {
    int emptyCount = width - count;
    int halfEmptyCount = emptyCount / 2;

    for (int i = 0; i < offset + halfEmptyCount; ++i) {
      _items.push_back(std::make_unique<EmptyItem>());
    }
    for (int i = 0; i < count; ++i) {
      _items.push_back(std::make_unique<TreeItem>());
    }
    for (int i = 0; i < halfEmptyCount; ++i) {
      _items.push_back(std::make_unique<EmptyItem>());
    }
  }

  virtual void print() override {
    for (const auto &it : _items) {
      it->print();
    }
    std::cout << std::endl;
  }

  virtual int
  overall(const std::vector<std::unique_ptr<SingleItem>> &items) override {
    int sum = 0;
    for (const auto &it : _items) {
      sum += it->overall(items);
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

    TreeItem treeItem;
    while (count) {
      int pos = rand() % (lastIndex - firstIndex) + firstIndex;
      if (*_items[pos].get() == treeItem) {
        _items[pos] = std::make_unique<Joy>();
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
          std::make_unique<TreeLine>(offset, maxWidth, treeItemCount));
    }
  }

  virtual void print() override {
    for (const auto &it : _lines) {
      it->print();
    }
  }

  virtual int
  overall(const std::vector<std::unique_ptr<SingleItem>> &items) override {
    int sum = 0;
    for (const auto &it : _lines) {
      sum += it->overall(items);
    }
    return sum;
  }

  virtual void decorate(int count) override {
    int sum = overall(Pattern::tree());
    int tempCount = count;
    for (const auto &it : boost::adaptors::reverse(_lines)) {
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
      auto ptr = std::make_unique<TreeSection>(offset - start, curWidth, start);
      _sections.push_back(std::move(ptr));
      curWidth += temp;
      start += diff;
    }
  }

  void loop() { animate(); }

  void animate() { print(); }

  virtual void decorate(int count) override {
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

  virtual void print() override {
    for (const auto &it : _sections) {
      it->print();
    }
  }

  int treeWithJoyCount() { return overall(Pattern::treeAndJoy()); }
  int treeCount() { return overall(Pattern::tree()); }
  int joyCount() { return overall(Pattern::joy()); }

private:
  virtual int
  overall(const std::vector<std::unique_ptr<SingleItem>> &items) override {
    int sum = 0;
    for (const auto &it : _sections) {
      sum += it->overall(items);
    }
    return sum;
  }

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
  int treeCount = tree.treeCount();
  int joyCount = treeCount / 4;
  tree.decorate(joyCount);

  GlobalColorController::setRejime(GlobalColorController::RejimeType::None);

  std::atomic<bool> on{true};

  auto drawFunction = [&](std::atomic<bool> &on) -> int {
    while (on) {
      system("clear");
      tree.loop();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      GlobalColorController::oneCycleComplete();
    }
    return 0;
  };

  auto inputFunction = [&](std::atomic<bool> &on) -> int {
    while (on) {
      char c;
      std::cin >> std::noskipws >> c;
      switch (c) {
      case 'q':
        on = false;
        break;
      case 0x20:
        GlobalColorController::nextRejime();
        break;
      default:
        break;
      }
    }
    return 0;
  };

  std::future<int> f1 =
      std::async(std::launch::async, drawFunction, std::ref(on));
  std::future<int> f2 =
      std::async(std::launch::async, inputFunction, std::ref(on));

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  return 0;
}
