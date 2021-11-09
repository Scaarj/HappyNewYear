#include "Text.h"

#include <iostream>

#include "CollorDrawer.h"
#include "GlobalPrint.h"

Text::Text(std::string str) { _string = str; }

void Text::print() {
  for (const auto &it : _string) {
    CollorDrawer::animate();
    GlobalPrint::print(it);
  }
}
