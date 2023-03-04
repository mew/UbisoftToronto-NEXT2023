#include "stdafx.h"
#include "Components.h"

#include <iostream>
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

Button::Button(float x, float y, float w, float h, std::string text, std::function<void()> action) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->buttonText = text;
    this->onClick = action;
}

void Button::Render(float percent) {
    float textWidth = FontRenderer::GetStringWidth(&buttonText, 1.5f);
    
    float tx = x + (w / 2) - (textWidth / 2);
    float ty = y + (h / 2) - 7.5f;
    FontRenderer::DrawString(buttonText, tx, ty, percent, colour, 1.5f);
    Utils::DrawRect(x, y, x+w, y+h, colour, percent);
}

void Button::Update() {
    float mx, my;
    App::GetMousePos(mx, my);
    bool hovered = mx >= x && mx <= x+w && my >= y && my <= y+h;
    if (hovered) {
        this->colour = hoverColour;
    } else {
        this->colour = 0xFFFFFF;
    }
    
    if (hovered && App::IsKeyPressed(VK_LBUTTON)) {
        onClick();
    }
}
