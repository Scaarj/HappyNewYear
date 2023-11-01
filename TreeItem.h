#pragma once

#include "Item.h"
#include "Symbol.h"

class TreeItem : public Symbol
{
public:
    TreeItem();
    virtual ~TreeItem();
    TreeItem(const TreeItem &);
    TreeItem &operator=(const TreeItem &) {}

    virtual std::unique_ptr<Item> clone() override;

    virtual void print();
    virtual int overall(const std::vector<std::unique_ptr<Symbol>> &items);
    virtual void decorate(int v);
};
