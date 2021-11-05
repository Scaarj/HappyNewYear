#pragma once

#include "DrawItem.h"
#include "Item.h"

class TreeTrunkLine : public Item {
public:
  TreeTrunkLine(int offset, int maxWidth);
  virtual ~TreeTrunkLine() = default;
  TreeTrunkLine(const TreeTrunkLine &other);
  TreeTrunkLine &operator=(const TreeTrunkLine &);

  virtual void print() override;
  virtual int
  overall(const std::vector<std::unique_ptr<Symbol>> &items) override;
  virtual void decorate(int) override;
  virtual std::unique_ptr<Item> clone() override;

private:
  std::vector<std::unique_ptr<Symbol>> _items;
};
