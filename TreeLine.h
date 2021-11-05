#pragma once

#include "TreeItem.h"

class TreeLine : public Item {
public:
  TreeLine(int offset, int width, int count);
  ~TreeLine() = default;
  TreeLine(const TreeLine &other);
  TreeLine &operator=(const TreeLine &other);

  virtual void print() override;
  virtual int
  overall(const std::vector<std::unique_ptr<Symbol>> &items) override;
  virtual void decorate(int count) override;
  virtual std::unique_ptr<Item> clone() override;

private:
  std::vector<std::unique_ptr<Symbol>> _items;
};
