#include "CollorDrawer.h"

CollorDrawer::RejimeType CollorDrawer::_rejime = CollorDrawer::RejimeType::None;
int CollorDrawer::_iterration = 0;

void CollorDrawer::setColor(ColorType color) {

  switch (color) {
  case ColorType::Red:
    std::cout << "\033[31m";
    break;
  case ColorType::Green:
    std::cout << "\033[32m";
    break;
  case ColorType::Yellow:
    std::cout << "\033[33m";
    break;
  case ColorType::Blue:
    std::cout << "\033[34m";
    break;
  case ColorType::Magenta:
    std::cout << "\033[35m";
    break;
  case ColorType::Cyan:
    std::cout << "\033[36m";
    break;
  case ColorType::White:
    std::cout << "\033[37m";
    break;
  }
}

void CollorDrawer::setRejime(RejimeType rejime) { _rejime = rejime; }

void CollorDrawer::nextRejime() {
  switch (_rejime) {
  case RejimeType::Snake:
    setRejime(RejimeType::Random);
    break;
  case RejimeType::Random:
    setRejime(RejimeType::OneColor);
    break;
  case RejimeType::OneColor:
    setRejime(RejimeType::None);
    break;
  case RejimeType::None:
    setRejime(RejimeType::Snake);
    break;
  default:
    break;
  }
}

void CollorDrawer::animate() {
  switch (_rejime) {
  case RejimeType::None:
    setColor(ColorType::White);
    break;
  case RejimeType::OneColor:
    oneColor();
    break;
  case RejimeType::Random:
    random();
    break;
  case RejimeType::Snake:
    snake();
    break;
  case RejimeType::Running:
    running();
    break;
  default:
    break;
  }
}

void CollorDrawer::oneCycleComplete() {
  _iterration++;
}

void CollorDrawer::oneColor() {
  setColor(static_cast<ColorType>(_iterration % 5 + 1));
}

void CollorDrawer::random() {
  int r = rand() % 6;
  setColor(static_cast<ColorType>(r));
}

void CollorDrawer::running() {}

void CollorDrawer::snake() {
  static int counter = 0;
  setColor(static_cast<ColorType>(counter % 5 + 1));
  counter++;
}
