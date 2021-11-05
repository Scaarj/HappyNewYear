#include "Joy.h"

#include <algorithm>

#include "CollorDrawer.h"

Joy::Joy() : Symbol('o') {}

Joy::~Joy() {}

void Joy::print() {
  CollorDrawer::animate();
  std::cout << _symbol;
}

int Joy::overall(const std::vector<std::unique_ptr<Symbol>> &items) {
  auto isJoy = [](const std::unique_ptr<Symbol> &item) {
    Joy joy;
    return (*item.get()) == joy;
  };

  if (std::find_if(items.begin(), items.end(), isJoy) != items.end()) {
    return 1;
  }
  return 0;
}

std::unique_ptr<Item> Joy::clone() { return std::make_unique<Joy>(*this); }

void Joy::decorate(int) {}
