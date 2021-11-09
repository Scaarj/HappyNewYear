#pragma once

#include <iostream>

class GlobalPrint {
public:
  static void print(const char ch) { std::cout << ch; }
  static void print(const char *str) { std::cout << str; }
  static void printnl() { std::cout << std::endl; }
};
