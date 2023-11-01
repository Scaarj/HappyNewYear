#pragma once

#include "DrawItem.h"
#include "Item.h"

class TreeTrunkSection : public Item
{
public:
    TreeTrunkSection(int height, int offset, int maxWidth);
    ~TreeTrunkSection() = default;
    TreeTrunkSection(const TreeTrunkSection &other);
    TreeTrunkSection &operator=(const TreeTrunkSection &ohter);

    virtual void print() override;
    virtual int overall(const std::vector<std::unique_ptr<Symbol>> &pattern) override;
    virtual void decorate(int) override;
    virtual std::unique_ptr<Item> clone() override;

private:
    std::vector<std::unique_ptr<Item>> _lines;
};
