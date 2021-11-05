#pragma once

#include "Item.h"
#include "Symbol.h"

class TreeTrunk : public Symbol {
public:
  TreeTrunk();
  virtual ~TreeTrunk() = default;
  TreeTrunk(const TreeTrunk &other);
  TreeTrunk &operator=(const TreeTrunk &other);

  virtual void print();
  virtual int overall(const std::vector<std::unique_ptr<Symbol>> &items);
  virtual void decorate(int);
  virtual std::unique_ptr<Item> clone() override;
};
