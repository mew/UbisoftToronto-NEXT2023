#pragma once
#include "Component.h"
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

    // Extendable methods
    virtual void InitScreenSpecific() {}
    virtual void UpdateScreenSpecific() {}
    virtual void RenderScreenSpecific() {}

    bool exit = false;
    Screen* nextScreen = nullptr;
    static float percent;
    static bool shake;

    std::vector<Component*> components{};
protected:
    bool init = false;
    virtual ~Screen() = default;
};
