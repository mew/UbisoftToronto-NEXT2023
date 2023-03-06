#include "stdafx.h"

#include <sstream>

#include "GameObjects.h"
#include "Screen.h"
#include "utils.h"
#include "app/app.h"

void Utils::DrawAnimLine(float x1, float y1, float x2, float y2, int colour, float p) {
    bool r = ScreenHolder::GetScreen()->exit;

    if (r) {
        bool cw = x1 > x2;
        // angle in degrees
        float a = -(p - 1) * 90 * PI / 180;

        // line centre
        float p1 = (x2 + x1) / 2;
        float p2 = (y2 + y1) / 2;

        // rotate
        x1 -= p1;
        y1 -= p2;
        x1 = cw ? x1 * cos(a) - y1 * sin(a) : x1 * cos(a) + y1 * sin(a);
        y1 = cw ? x1 * sin(a) + y1 * cos(a) : -x1 * sin(a) + y1 * cos(a);
        x1 += p1;
        y1 += p2;

        x2 -= p1;
        y2 -= p2;
        x2 = cw ? x2 * cos(a) - y2 * sin(a) : x2 * cos(a) + y2 * sin(a);
        y2 = cw ? x2 * sin(a) + y2 * cos(a) : -x2 * sin(a) + y2 * cos(a);
        x2 += p1;
        y2 += p2;
    }
    
    if (Screen::shake) {
        int a = rand() % 5 * (rand() % 2 == 0 ? -1 : 1);
        int b = rand() % 5 * (rand() % 2 == 0 ? -1 : 1);
        x1 += cos(b*x2) - sin(b*y2);
        y1 += sin(b*x2) - cos(b*y2);
        x2 += cos(a*x2) - sin(a*y2);
        y2 += sin(a*x2) - cos(a*y2);
    }

    x2 = easePos2(x1, x2, p);
    y2 = easePos2(y1, y2, p);


    Colour c = h2c(colour);
    App::DrawLine(x1, y1, x2, y2, c.r, c.g, c.b);
}

void Utils::DrawRect(float x1, float y1, float x2, float y2, int colour, float p) {
    DrawAnimLine(x1, y1, x2, y1, colour, p); 
    DrawAnimLine(x1, y1, x1, y2, colour, p);
    DrawAnimLine(x1, y2, x2, y2, colour, p);
    DrawAnimLine(x2, y1, x2, y2, colour, p);
}

void Utils::DrawFillRect(float x1, float y1, float x2, float y2, int colour, float p) {
    DrawRect(x1, y1, x2, y2, colour, p);
    bool b = y1 > y2;
    for (float i = y1; b ? i > y2 : i < y2; b ? i-- : i++) {
        if ((int) i % 2 == 0) {
            DrawAnimLine(x1, i, x2, i, colour, p);
        }
    }
}

GridPos Utils::LiteralToGrid(float x, float y) {
    x -= 12;
    y -= 9;
    return GridPos{(int) x / TILE_SIZE, (int) y / TILE_SIZE};
}

LiteralPos Utils::GridToLiteral(int column, int row) {
    return LiteralPos{static_cast<float>(column * TILE_SIZE + 15), static_cast<float>(row * TILE_SIZE + 10)};
}

float Utils::easePos2(float pos1, float pos2, float percent) {
    float diff = pos2 - pos1;
    float p = 1 - powf(1 - percent, 3);
    return pos1 + (diff * p);
}

Utils::Colour Utils::h2c(const int h) {
    Colour c;
    c.r = ((h >> 16) & 0xFF) / 255.0f; // red
    c.g = ((h >> 8) & 0xFF) / 255.0f; // green
    c.b = (h & 0xFF) / 255.0f; // blue
    return c;
}

Screen* ScreenHolder::currentScreen;
