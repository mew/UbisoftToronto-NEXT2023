#include "stdafx.h"
#include "TestScreen.h"

#include "Components.h"

void TestScreen::InitScreenSpecific() {
    auto r = new RectComponent(50, 50, 50, 50);
    components.push_back(r);

    components.push_back(new Label(150, 150, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 2.0f));
}

void TestScreen::UpdateScreenSpecific() {
    if (App::IsKeyPressed(VK_SPACE)) {
        ChangeScreen(new TestScreen());
    }
}

void TestScreen::ExitScreenSpecific() {
}
