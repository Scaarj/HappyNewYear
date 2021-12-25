#include "EmptyItem.h"

#include <algorithm>

#include "GlobalPrint.h"

EmptyItem::EmptyItem() : Symbol(' ') {}

int EmptyItem::overall(const std::vector<std::unique_ptr<Symbol>> &items) {
  auto isEmpty = [](const std::unique_ptr<Symbol> &item) {
    EmptyItem emptyItem;
    return (*item.get()) == emptyItem;
  };

  if (std::find_if(items.begin(), items.end(), isEmpty) != items.end()) {
    return 1;
  }
  return 0;
}

std::unique_ptr<Item> EmptyItem::clone() {
  return std::make_unique<EmptyItem>(*this);
}

void EmptyItem::decorate(int) {}

void EmptyItem::print() { GlobalPrint::print(_symbol); }
