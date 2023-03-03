#include "stdafx.h"
#include "TestScreen.h"

#include "Components.h"

void TestScreen::InitScreenSpecific() {
    auto r = new RectComponent(50, 50, 50, 50);
    components.push_back(r);
}

void TestScreen::UpdateScreenSpecific() {
    
}

void TestScreen::ExitScreenSpecific() {
}
