#include "Symbol.h"

#include <iostream>

Symbol::Symbol(char c) : _symbol(c) {}

bool Symbol::operator==(const Symbol &other) {
  return _symbol == other._symbol;
}
