#pragma once

#include "DrawItem.h"
#include "Text.h"

class TextHeader : public DrawItem {
public:
  TextHeader(std::string _whois, int offset);
  virtual ~TextHeader();
  TextHeader(const TextHeader &) = default;
  TextHeader &operator=(const TextHeader &) = default;

  virtual void print() override;

protected:
  std::vector<Text> _header;
  std::string _whois;
};
