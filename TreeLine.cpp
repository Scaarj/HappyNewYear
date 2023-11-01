#include "TreeLine.h"

#include <algorithm>
#include <iostream>

#include "EmptyItem.h"
#include "GlobalPrint.h"
#include "Joy.h"

TreeLine::TreeLine(int offset, int width, int count)
{
    int emptyCount = width - count;
    int halfEmptyCount = emptyCount / 2;

    for (int i = 0; i < offset + halfEmptyCount; ++i) {
        _items.push_back(std::make_unique<EmptyItem>());
    }
    for (int i = 0; i < count; ++i) {
        _items.push_back(std::make_unique<TreeItem>());
    }
    for (int i = 0; i < halfEmptyCount; ++i) {
        _items.push_back(std::make_unique<EmptyItem>());
    }
}

TreeLine::TreeLine(const TreeLine &other)
{
    _items.reserve(other._items.size());
    Joy joy;
    TreeItem treeItem;
    EmptyItem emptyItem;

    for (const auto &it : other._items) {
        if (it.get()->operator==(joy)) {
            _items.push_back(std::make_unique<Joy>(*reinterpret_cast<Joy *>(it.get())));
        } else if (it.get()->operator==(treeItem)) {
            _items.push_back(std::make_unique<TreeItem>(*reinterpret_cast<TreeItem *>(it.get())));
        } else {
            _items.push_back(
                std::make_unique<EmptyItem>(*reinterpret_cast<class EmptyItem *>(it.get())));
        }
    }
}

TreeLine &TreeLine::operator=(const TreeLine &) {}

void TreeLine::print()
{
    for (const auto &it : _items) {
        it->print();
    }
    GlobalPrint::printnl();
}

int TreeLine::overall(const std::vector<std::unique_ptr<Symbol>> &items)
{
    int sum = 0;
    for (const auto &it : _items) {
        sum += it->overall(items);
    }
    return sum;
}

void TreeLine::decorate(int count)
{
    auto isTreeItem = [](const std::unique_ptr<Symbol> &item) {
        TreeItem tree;
        return *(item.get()) == tree;
    };

    auto isEmptyElement = [](const std::unique_ptr<Symbol> &item) {
        EmptyItem empty;
        return *(item.get()) == empty;
    };

    auto treeStartIt = std::find_if(_items.begin(), _items.end(), isTreeItem);
    auto treeEndIt = std::find_if(treeStartIt, _items.end(), isEmptyElement);
    int firstIndex = std::distance(_items.begin(), treeStartIt);
    int lastIndex = std::distance(_items.begin(), treeEndIt);

    TreeItem treeItem;
    while (count) {
        int pos = rand() % (lastIndex - firstIndex) + firstIndex;
        if (*_items[pos].get() == treeItem) {
            _items[pos] = std::make_unique<Joy>();
            count--;
        }
    }
}

std::unique_ptr<Item> TreeLine::clone()
{
    return std::make_unique<TreeLine>(*this);
}
