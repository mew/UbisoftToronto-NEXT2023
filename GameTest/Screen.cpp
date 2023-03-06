#include "stdafx.h"
#include "Screen.h"
#include "Utils.h"

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
        return;
    }
    if (exit) {
        percent -= 0.01f;
        if (percent <= 0) {
            exit = false;
            ScreenHolder::ChangeScreen(nextScreen);
        }
        return;
    }

    for (auto component : components) {
        component->Update();
    }

    UpdateScreenSpecific();
}

void Screen::Render() {
    for (auto component : components) {
        component->Render(percent);
    }

    RenderScreenSpecific();
}

void Screen::ChangeScreen(Screen* newScreen) {
    shake = false;
    nextScreen = newScreen;
    Exit();
}

void Screen::Exit() {
    percent = 1.0f;
    exit = true;

    ExitScreenSpecific();
}

bool Screen::shake = false;