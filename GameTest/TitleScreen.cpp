#include "stdafx.h"
#include "TitleScreen.h"

#include "Components.h"
#include "FontRenderer.h"
#include "GameScreen.h"

void TitleScreen::InitScreenSpecific() {
    components.push_back(new Label(CENTRE_SCREEN_W - (12*8*9 >> 1), 600, "BOMB GAME", 8.0f));
    components.push_back(new Button(CENTRE_SCREEN_W - 50, 400, 100, 30, "START", [this] {
        App::PlaySound(".\\TestData\\Test.wav");
        ChangeScreen(new GameScreen());
    }));
    auto exitButton = new Button(CENTRE_SCREEN_W - 50, 350, 100, 30, "EXIT", [] {
        std::exit(0);
    });
    exitButton->hoverColour = 0xFF0000;
    components.push_back(exitButton);
}

void TitleScreen::UpdateScreenSpecific() {
    if (App::IsKeyPressed(VK_SPACE)) {
        ChangeScreen(new TitleScreen());
    }
}

void TitleScreen::ExitScreenSpecific() {
    
}
