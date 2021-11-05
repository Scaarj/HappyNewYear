#include "TreeTrunk.h"

#include <algorithm>

#include "CollorDrawer.h"

TreeTrunk::TreeTrunk() : Symbol('|') {}

TreeTrunk::TreeTrunk(const TreeTrunk &other) : Symbol(other) {}

TreeTrunk &TreeTrunk::operator=(const TreeTrunk &other) {}

void TreeTrunk::print() {
  CollorDrawer::setColor(ColorType::Yellow);
  std::cout << _symbol;
}

int TreeTrunk::overall(const std::vector<std::unique_ptr<Symbol>> &items) {
  auto isTree = [](const std::unique_ptr<Symbol> &item) {
    TreeTrunk treeTrunk;
    return (*item.get()) == treeTrunk;
  };

  if (std::find_if(items.begin(), items.end(), isTree) != items.end()) {
    return 1;
  }
  return 0;
}

void TreeTrunk::decorate(int) {}

std::unique_ptr<Item> TreeTrunk::clone() {
  return std::make_unique<TreeTrunk>(*this);
}
