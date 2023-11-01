#pragma once

#include "DrawItem.h"
#include "Item.h"

class Text : public DrawItem
{
public:
    Text(std::string str);
    virtual ~Text() = default;
    Text(const Text &) = default;
    Text &operator=(const Text &) = default;

    virtual void print() override;

protected:
    std::string _string;
};
