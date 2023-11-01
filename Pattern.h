#pragma once

#include <memory>
#include <vector>

#include "Symbol.h"

class Pattern
{
public:
    static std::vector<std::unique_ptr<Symbol>> &tree();
    static std::vector<std::unique_ptr<Symbol>> &joy();
    static std::vector<std::unique_ptr<Symbol>> &treeAndJoy();
};
