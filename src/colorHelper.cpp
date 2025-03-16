// ColorHelper.cpp
#include "ColorHelper.hpp"

Color ColorHelper::HueToRGB(float hue)
{
    float r = 0, g = 0, b = 0;
    int i = static_cast<int>(hue / 60.0f) % 6;
    float f = (hue / 60.0f) - i;
    float q = 1.0f - f;

    switch (i)
    {
    case 0:
        r = 1.0f;
        g = f;
        b = 0.0f;
        break;
    case 1:
        r = q;
        g = 1.0f;
        b = 0.0f;
        break;
    case 2:
        r = 0.0f;
        g = 1.0f;
        b = f;
        break;
    case 3:
        r = 0.0f;
        g = q;
        b = 1.0f;
        break;
    case 4:
        r = f;
        g = 0.0f;
        b = 1.0f;
        break;
    case 5:
        r = 1.0f;
        g = 0.0f;
        b = q;
        break;
    }

    return Color{static_cast<unsigned char>(r * 255), static_cast<unsigned char>(g * 255), static_cast<unsigned char>(b * 255), 255};
}
