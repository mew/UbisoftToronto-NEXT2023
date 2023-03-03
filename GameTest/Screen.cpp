#include "stdafx.h"
#include "Screen.h"

#include "utils.h"

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
        if (percent <= 0) {
            exit = false;
            ScreenHolder::ChangeScreen(nextScreen);
        }
    }

    UpdateScreenSpecific();
}

void Screen::Render() {
    for (auto component : components) {
        component->Render(percent);
    }
}

void Screen::ChangeScreen(Screen* newScreen) {
    nextScreen = newScreen;
    Exit();
}

void Screen::Exit() {
    percent = 1.0f;
    exit = true;

    ExitScreenSpecific();
}
