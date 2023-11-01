#include "Pattern.h"

#include "Joy.h"
#include "TreeItem.h"

std::vector<std::unique_ptr<Symbol>> &Pattern::tree()
{
    static std::vector<std::unique_ptr<Symbol>> items;
    items.push_back(std::make_unique<TreeItem>());
    return items;
}

std::vector<std::unique_ptr<Symbol>> &Pattern::joy()
{
    static std::vector<std::unique_ptr<Symbol>> items;
    items.push_back(std::make_unique<Joy>());
    return items;
}

std::vector<std::unique_ptr<Symbol>> &Pattern::treeAndJoy()
{
    static std::vector<std::unique_ptr<Symbol>> items;
    items.push_back(std::make_unique<TreeItem>());
    items.push_back(std::make_unique<Joy>());
    return items;
}
