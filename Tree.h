#include "Item.h"

class Tree : public Item {
public:
  Tree();
  Tree(int offset, int sectionCount, int maxWidth, int diff);
  virtual ~Tree() = default;
  Tree(const Tree &other);
  Tree &operator=(const Tree &) {}

  virtual void decorate(int count) override;
  virtual void print() override;
  int treeWithJoyCount();
  int treeCount();
  int joyCount();
  virtual std::unique_ptr<Item> clone() override {}

private:
  virtual int
  overall(const std::vector<std::unique_ptr<Symbol>> &items) override;

private:
  std::vector<std::unique_ptr<Item>> _sections;
};
