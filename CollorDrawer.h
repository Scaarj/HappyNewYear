#pragma once

#include <iostream>

enum class ColorType : int {
  Green = 0,
  White = 1,
  Yellow = 2,
  Red = 3,
  Blue = 4,
  Magenta = 5,
  Cyan = 6,
};

class CollorDrawer {
public:
  enum class RejimeType : int {
    None,
    OneColor,
    Snake,
    Random,
    Running,
  };

public:
  static void setColor(ColorType color);
  static void setRejime(RejimeType rejime);
  static void nextRejime();
  static void animate();
  static void oneCycleComplete();
  static void oneColor();
  static void random();
  static void running();
  static void snake();

private:
  static RejimeType _rejime;
  static bool _complete;
  static int _iterration;
};
