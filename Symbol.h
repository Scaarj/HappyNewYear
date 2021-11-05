#pragma once

#include "Item.h"

class Symbol : public Item {
public:
  Symbol(char c);
  virtual ~Symbol() = default;
  Symbol(const Symbol &) = default;
  Symbol &operator=(const Symbol &) = default;

  virtual int overall(const std::vector<std::unique_ptr<Symbol>> &items) {}
  virtual void decorate(int count) {}
  bool operator==(const Symbol &other);

protected:
  char _symbol;
};
