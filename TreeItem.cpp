#include "TreeItem.h"

#include <algorithm>

#include "CollorDrawer.h"
#include "GlobalPrint.h"

TreeItem::TreeItem()
    : Symbol('*')
{}

TreeItem::~TreeItem() {}

TreeItem::TreeItem(const TreeItem &other)
    : Symbol(other)
{}

void TreeItem::print()
{
    CollorDrawer::setColor(ColorType::Green);
    GlobalPrint::print(_symbol);
}

int TreeItem::overall(const std::vector<std::unique_ptr<Symbol>> &items)
{
    auto isTree = [](const std::unique_ptr<Symbol> &item) {
        TreeItem treeItem;
        return (*item.get()) == treeItem;
    };

    if (std::find_if(items.begin(), items.end(), isTree) != items.end()) {
        return 1;
    }
    return 0;
}

std::unique_ptr<Item> TreeItem::clone()
{
    return std::make_unique<TreeItem>(*this);
}

void TreeItem::decorate(int v) {}
