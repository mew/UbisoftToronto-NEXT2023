#include "stdafx.h"
#include "Components.h"

#include <ostream>

#include "FontRenderer.h"
#include "Screen.h"
#include "utils.h"

RectComponent::RectComponent(float posX, float posY, float w, float h) {
    this->x = posX;
    this->y = posY;
    this->w = w;
    this->h = h;
}

void RectComponent::Render(float percent) {
    Utils::DrawRect(x, y, x+w, y+h, colour, percent);
}

Label::Label(float x, float y, std::string text, float scale) {
    this->x = x;
    this->y = y;
    this->text = text;
    this->scale = scale;
}

void Label::Render(float percent) {
    FontRenderer::DrawString(text, x, y, percent, colour, scale);
}
