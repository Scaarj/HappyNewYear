#pragma once

#include "Item.h"
#include "Symbol.h"

class TreeTrunk : public Symbol
{
public:
    TreeTrunk();
    virtual ~TreeTrunk() = default;
    TreeTrunk(const TreeTrunk &other);
    TreeTrunk &operator=(const TreeTrunk &other);

    virtual void print() override;
    virtual int overall(const std::vector<std::unique_ptr<Symbol>> &items) override;
    virtual void decorate(int) override;
    virtual std::unique_ptr<Item> clone() override;
};
