#pragma once

class DrawItem {
public:
  DrawItem();
  virtual ~DrawItem();
  virtual void print() = 0;
};
