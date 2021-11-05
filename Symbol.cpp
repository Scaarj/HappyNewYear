#include "Symbol.h"

#include <iostream>

Symbol::Symbol(char c) : _symbol(c) {}

bool Symbol::operator==(const Symbol &other) {
  return _symbol == other._symbol;
}
/*
std::unique_ptr<Item> Symbol::clone() {
  return std::make_unique<Symbol>(*this);
}

 void Symbol::print() { std::cout << _symbol; }
*/
