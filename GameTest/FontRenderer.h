#pragma once
#include <map>
#include <string>
#include <vector>

struct CharLine {
    float x1, y1, x2, y2;
};

// oh dear
class FontRenderer {
public:
    static void DrawString(std::string str, float x, float y, float percent, int colour, float scale = 1.0f);

    static void DrawChar(char c, float x, float y, float percent, int colour, float scale);
private:
    static std::map<char, std::vector<CharLine>> charMap;
};
