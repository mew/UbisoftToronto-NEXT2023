#include "stdafx.h"
#include "Screen.h"

#include <iostream>

void Screen::Init() {
    percent = 0.0f;
    init = true;

    InitScreenSpecific();
}

void Screen::Update() {
    if (init) {
        percent += 0.01f;
        if (percent >= 1) {
            init = false;
        }
    } else if (exit) {
        percent -= 0.01f;
        if (percent <= 1) {
            exit = false;
        }
    }

    UpdateScreenSpecific();
}

void Screen::Render() {
    for (auto component : components) {
        std::cout << "rect(" << component->x << "," << component->y << ")" << "|" << init << percent << std::endl;
        component->Render(percent);
    }
}

void Screen::Exit() {
    percent = 1.0f;
    exit = true;

    ExitScreenSpecific();
}
