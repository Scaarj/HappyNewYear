#include "TreeTrunkSection.h"

#include <algorithm>

#include "EmptyItem.h"
#include "TreeTrunkLine.h"

TreeTrunkSection::TreeTrunkSection(int height, int offset, int maxWidth)
{
    for (int i = 0; i < height; ++i) {
        _lines.push_back(std::make_unique<TreeTrunkLine>(offset, maxWidth));
    }
}

TreeTrunkSection::TreeTrunkSection(const TreeTrunkSection &other)
{
    _lines.reserve(other._lines.size());
    for (const auto &it : other._lines) {
        _lines.push_back(it->clone());
    }
}

TreeTrunkSection &TreeTrunkSection::operator=(const TreeTrunkSection &ohter) {}

void TreeTrunkSection::print()
{
    for (const auto &it : _lines) {
        it->print();
    }
}

int TreeTrunkSection::overall(const std::vector<std::unique_ptr<Symbol>> &pattern)
{
    int sum = 0;
    for (const auto &it : _lines) {
        sum += it->overall(pattern);
    }
    return sum;
}

void TreeTrunkSection::decorate(int) {}

std::unique_ptr<Item> TreeTrunkSection::clone()
{
    return std::make_unique<TreeTrunkSection>(*this);
}
