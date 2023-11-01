#pragma once

#include "Item.h"
#include "Symbol.h"

class Joy : public Symbol
{
public:
    Joy();
    virtual ~Joy();
    Joy(const Joy &) = default;
    Joy &operator=(const Joy &) = default;

    virtual std::unique_ptr<Item> clone() override;
    virtual void print() override;
    virtual int overall(const std::vector<std::unique_ptr<Symbol>> &items) override;
    virtual void decorate(int) override;
};
