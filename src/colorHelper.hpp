// ColorHelper.hpp
#ifndef COLOR_HELPER_HPP
#define COLOR_HELPER_HPP

#include "raylib.h"

class ColorHelper
{
  public:
    // Delete the constructor to prevent instantiation
    ColorHelper() = delete;

    // Static method to convert hue to RGB
    static Color HueToRGB(float hue);
};

#endif // COLOR_HELPER_HPP
