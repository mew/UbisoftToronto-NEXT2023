#include "stdafx.h"
#include "EndScreen.h"

#include "Button.h"
#include "Label.h"
#include "TitleScreen.h"

EndScreen::EndScreen(bool w) {
    std::string txt;
    float pos;
    int col;
    // change some elements depending on if player won or died
    if (w) {
        txt = "YOU WON";
        pos = CENTRE_SCREEN_W - (12*8*7 >> 1);
        col = 0x00FF00;
    } else {
        txt = "YOU DIED";
        pos = CENTRE_SCREEN_W - (12*8*8 >> 1);
        col = 0xFF0000;
    }
    auto header = new Label(pos, 600, txt, 8.0f);
    header->colour = col;
    components.push_back(header);

    components.push_back(new Button(CENTRE_SCREEN_W - 50, 400, 100, 30, "TITLE", [this] {
        ChangeScreen(new TitleScreen());
    }));
    auto exitButton = new Button(CENTRE_SCREEN_W - 50, 350, 100, 30, "QUIT", [] {
        std::exit(0);
    });
    exitButton->hoverColour = 0xFF0000;
    components.push_back(exitButton);
}
