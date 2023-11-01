#pragma once

#include "Item.h"

class TreeSection : public Item
{
public:
    TreeSection(int offset, int maxWidth, int start);
    virtual ~TreeSection() = default;
    TreeSection(const TreeSection &other);
    TreeSection &operator=(const TreeSection &other);

    virtual void print() override;
    virtual int overall(const std::vector<std::unique_ptr<Symbol>> &items) override;
    virtual void decorate(int count) override;
    virtual std::unique_ptr<Item> clone() override;

private:
    std::vector<std::unique_ptr<Item>> _lines;
};
