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
    /**
     * \brief Draw line with animations applied.
     */
    static void DrawAnimLine(float x1, float y1, float x2, float y2, int colour);
    
    /**
     * \brief Draw a rectangle outline with animations applied.
     */
    static void DrawRect(float x1, float y1, float x2, float y2, int colour = 0xFFFFFF);

    
    /**
     * \brief Draw rectangle with scan-line effect.
     */
    static void DrawFillRect(float x1, float y1, float x2, float y2, int colour = 0xFFFFFF);

    /**
     * \brief Convert render position to position on grid.
     */
    static GridPos LiteralToGrid(float x, float y);
    /**
     * \brief Convert position on grid to render position.
     */
    static LiteralPos GridToLiteral(int column, int row);
private:
    /**
     * \brief Holds 3 floats for a colour value
     */
    struct Colour {
        float r, g, b;
    };
    
    /**
     * \brief https://easings.net/
     */
    static float easePos2(float pos1, float pos2, float percent);
    
    /**
     * \brief Turn integer into 3 floats necessary for colouring lines
     * \return Colour struct
     */
    static Colour h2c(int h);
};

class ScreenHolder {
public:
    /**
     * \brief Switch active (displayed) screen
     * \param n new screen
     */
    static void ChangeScreen(Screen* n) {
        currentScreen = n;
        currentScreen->Init();
    }

    /**
     * \return currently active screen
     */
    static Screen* GetScreen() {
        return currentScreen;
    }
private:
    static Screen* currentScreen;
};