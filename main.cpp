#include <algorithm>
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <random>
#include <thread>

#include "CollorDrawer.h"
#include "GlobalPrint.h"
#include "TextHeader.h"
#include "Tree.h"

#ifdef __linux__
#include <sys/ioctl.h>
#include <termios.h>
static struct termios old, current;

void initTermios(int echo) {
  tcgetattr(0, &old);         /* grab old terminal i/o settings */
  current = old;              /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
    current.c_lflag |= ECHO; /* set echo mode */
  } else {
    current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) { tcsetattr(0, TCSANOW, &old); }

/* Read 1 character - echo defines echo mode */
char getch_(int echo) {
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) { return getch_(0); }

/* Read 1 character with echo */
char getche(void) { return getch_(1); }
#elif _WIN32
char getche(void) {
	return getchar();
}
#else
#endif

int main() {
  srand(time(NULL));
  int offset = 39;
  int sectionCount = 3;
  int maxWidth = 43;
  int sectionDiff = 5;
  /*
  int offset = 50;
  int sectionCount = 4;
  int maxWidth = 55;
  int sectionDiff = 5;
*/
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
#ifdef __linux__
	  system("clear");
#elif _WIN32
		if (system("CLS")) system("clear");
#endif
      textHeader.print();
      copy.print();
      CollorDrawer::setColor(ColorType::White);
      GlobalPrint::print("Press space - for change light mode, 'q' - quit\n");
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      CollorDrawer::oneCycleComplete();
    }
    return 0;
  };

  auto inputFunction = [&](std::atomic<bool> &on) -> int {
    while (on) {
	  char c = getche();
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
