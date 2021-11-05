#include <algorithm>
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <random>
#include <thread>

#include "CollorDrawer.h"
#include "TextHeader.h"
#include "Tree.h"

int main() {
  srand(time(NULL));
  int offset = 50;
  int sectionCount = 4;
  int maxWidth = 55;
  int sectionDiff = 5;
  Tree tree(offset, sectionCount, maxWidth, sectionDiff);
  int treeCount = tree.treeCount();
  int joyCount = treeCount / 4;
  tree.decorate(joyCount);

  // just try deep copy a tree
  Tree copy = tree;

  TextHeader textHeader(offset);

  CollorDrawer::setRejime(CollorDrawer::RejimeType::Snake);

  std::atomic<bool> on{true};

  auto drawFunction = [&](std::atomic<bool> &on) -> int {
    while (on) {
      system("clear");
      textHeader.print();
      copy.print();
      CollorDrawer::setColor(ColorType::White);
      std::cout << "Press space - for change light mode, 'q' - quit"
                << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      CollorDrawer::oneCycleComplete();
    }
    return 0;
  };

  auto inputFunction = [&](std::atomic<bool> &on) -> int {
    while (on) {
      char c;
      std::cin >> std::noskipws >> c;
      switch (c) {
      case 'q':
        on = false;
        break;
      case 0x20:
        CollorDrawer::nextRejime();
        break;
      default:
        break;
      }
    }
    return 0;
  };

  std::future<int> f1 =
      std::async(std::launch::async, drawFunction, std::ref(on));
  std::future<int> f2 =
      std::async(std::launch::async, inputFunction, std::ref(on));

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  return 0;
}
