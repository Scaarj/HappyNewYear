#include "TreeTrunkLine.h"

#include <iostream>

#include "EmptyItem.h"
#include "GlobalPrint.h"
#include "TreeTrunk.h"

TreeTrunkLine::TreeTrunkLine(int offset, int maxWidth)
{
    for (int i = 0; i < offset; ++i) {
        _items.push_back(std::make_unique<EmptyItem>());
    }
    for (int i = 0; i < maxWidth; ++i) {
        _items.push_back(std::make_unique<TreeTrunk>());
    }
}

TreeTrunkLine::TreeTrunkLine(const TreeTrunkLine &other)
{
    _items.reserve(other._items.size());
    for (const auto &it : other._items) {
        _items.push_back(std::make_unique<TreeTrunk>(*reinterpret_cast<TreeTrunk *>(it.get())));
    }
}

TreeTrunkLine &TreeTrunkLine::operator=(const TreeTrunkLine &) {}

void TreeTrunkLine::print()
{
    for (const auto &it : _items) {
        it->print();
    }
    GlobalPrint::printnl();
}

int TreeTrunkLine::overall(const std::vector<std::unique_ptr<Symbol>> &items)
{
    int sum = 0;
    for (const auto &it : _items) {
        sum += it->overall(items);
    }
    return sum;
}

void TreeTrunkLine::decorate(int) {}

std::unique_ptr<Item> TreeTrunkLine::clone()
{
    return std::make_unique<TreeTrunkLine>(*this);
}
