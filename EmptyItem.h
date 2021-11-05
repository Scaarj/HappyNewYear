#pragma once

#include "Item.h"
#include "Symbol.h"

class EmptyItem : public Symbol {
public:
  EmptyItem();
  virtual ~EmptyItem() = default;
  EmptyItem(const EmptyItem &) = default;
  EmptyItem &operator=(const EmptyItem &) = default;

  virtual std::unique_ptr<Item> clone() override;
  virtual int overall(const std::vector<std::unique_ptr<Symbol>> &items);
  virtual void decorate(int);
  virtual void print() override;
};
