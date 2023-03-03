#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>

#include "Screen.h"
#include "utils.h"
#include "app/app.h"


bool b = true;

void Utils::DrawAnimLine(float x1, float y1, float x2, float y2, int colour, float p) {
    float n_x2 = easePos2(x1, x2, p);
    float n_y2 = easePos2(y1, y2, p);
    Colour c = h2c(colour);
    App::DrawLine(x1, y1, n_x2, n_y2, c.r, c.g, c.b);
}

void Utils::DrawRect(float x1, float y1, float x2, float y2, int colour, float p) {
    b = true;
    DrawAnimLine(x1, y1, x2, y1, colour, p); 
    DrawAnimLine(x1, y1, x1, y2, colour, p);
    DrawAnimLine(x1, y2, x2, y2, colour, p);
    DrawAnimLine(x2, y1, x2, y2, colour, p);
}

float Utils::easePos2(float pos1, float pos2, float percent) {
    float diff = pos2 - pos1;
    float p = 1 - powf(1 - percent, 3);
    return pos1 + (diff * p);
}

Utils Utils::GetInstance() {
    static Utils u;
    return u;
}

Utils::Colour Utils::h2c(const int h) {
    Colour c;
    c.r = ((h >> 16) & 0xFF) / 255.0f; // red
    c.g = ((h >> 8) & 0xFF) / 255.0f; // green
    c.b = (h & 0xFF) / 255.0f; // blue
    return c;
}
