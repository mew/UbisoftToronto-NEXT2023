#pragma once
#include "Components.h"
#include "app/app.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "app/main.h"

#define CENTRE_SCREEN_W (WINDOW_WIDTH >> 1)

class Screen {
public:
    void Init();
    void Update();
    void Render();
    void ChangeScreen(Screen* newScreen);
    void Exit();

    virtual void InitScreenSpecific() {}
    virtual void UpdateScreenSpecific() {}
    virtual void ExitScreenSpecific() {}

    bool init = false;
    bool exit = false;
    float percent = 0.0f;
    Screen* nextScreen = nullptr;

    std::vector<Component*> components{};
public:
    virtual ~Screen() = default;
};
