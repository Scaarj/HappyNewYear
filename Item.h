#pragma once

#include <memory>
#include <vector>

#include "DrawItem.h"

class Symbol;

class Item : public DrawItem
{
public:
    Item();
    virtual ~Item();
    virtual int overall(const std::vector<std::unique_ptr<Symbol>> &items) = 0;
    virtual void decorate(int count) = 0;
    virtual std::unique_ptr<Item> clone() = 0;
};
