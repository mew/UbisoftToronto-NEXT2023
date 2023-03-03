﻿#pragma once

#define UTILS Utils::GetInstance()

class Utils {
public:
    static void DrawAnimLine(float x1, float y1, float x2, float y2, int colour, float percent);
    static void DrawRect(float x1, float y1, float x2, float y2, int colour = 0xFFFFFF, float percent = 1.0f);

    static float easePos2(float pos1, float pos2, float percent);

    static Utils GetInstance();
private:
    struct Colour {
        float r, g, b;
    };
    
    static Colour h2c(int h);
};
