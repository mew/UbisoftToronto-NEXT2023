#pragma once

#define UTILS Utils::GetInstance()
#include "TitleScreen.h"

struct LiteralPos {
    float x, y;
};

struct GridPos {
    int x, y;
};

class Utils {
public:
    static void DrawAnimLine(float x1, float y1, float x2, float y2, int colour, float percent);
    static void DrawRect(float x1, float y1, float x2, float y2, int colour = 0xFFFFFF, float percent = 1.0f);
    static void DrawFillRect(float x1, float y1, float x2, float y2, int colour = 0xFFFFFF, float percent = 1.0f);

    static GridPos LiteralToGrid(float x, float y);
    static LiteralPos GridToLiteral(int column, int row);
private:
    struct Colour {
        float r, g, b;
    };

    static float easePos2(float pos1, float pos2, float percent);
    static Colour h2c(int h);
};

class ScreenHolder {
public:
    static void ChangeScreen(Screen* n) {
        currentScreen = n;
        currentScreen->Init();
    }

    static Screen* GetScreen() {
        return currentScreen;
    }
private:
    static Screen* currentScreen;
};