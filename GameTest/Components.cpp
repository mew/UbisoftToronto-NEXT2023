#include "stdafx.h"
#include "Components.h"

#include <iostream>
#include <ostream>

#include "Screen.h"
#include "utils.h"

RectComponent::RectComponent(float posX, float posY, float w, float h) {
    this->x = posX;
    this->y = posY;
    this->w = w;
    this->h = h;
}

void RectComponent::Render(float percent) {
    if (false) {
        std::cout << "lol" << std::endl;
    } else {
        Utils::DrawRect(x, y, x+w, y+h, colour, percent);
    }
}
