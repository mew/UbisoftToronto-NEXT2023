#include "stdafx.h"
#include "Button.h"

#include "FontRenderer.h"
#include "Utils.h"


Button::Button(float x, float y, float w, float h, std::string text, std::function<void()> action) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->buttonText = text;
    this->onClick = action;
}

void Button::Render() {
    // centre text
    float textWidth = FontRenderer::GetStringWidth(&buttonText, 1.5f);
    float tx = x + (w / 2) - (textWidth / 2);
    float ty = y + (h / 2) - 7.5f;
    
    FontRenderer::DrawString(buttonText, tx, ty, colour, 1.5f);
    Utils::DrawRect(x, y, x+w, y+h, colour);
}

void Button::Update() {
    // check if mouse over
    float mx, my;
    App::GetMousePos(mx, my);
    bool hovered = mx >= x && mx <= x+w && my >= y && my <= y+h;
    if (hovered) {
        this->colour = hoverColour;
    } else {
        this->colour = 0xFFFFFF;
    }

    // run action when clicked
    if (hovered && App::IsKeyPressed(VK_LBUTTON)) {
        onClick();
    }
}