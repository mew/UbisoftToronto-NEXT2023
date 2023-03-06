#include "stdafx.h"
#include "Label.h"

#include "FontRenderer.h"

Label::Label(float x, float y, std::string text, float scale) {
    this->x = x;
    this->y = y;
    this->text = text;
    this->scale = scale;
}

void Label::Render() {
    FontRenderer::DrawString(text, x, y, colour, scale);
}