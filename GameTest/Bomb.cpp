#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb(int column, int row): TileObject(column, row) {}

void Bomb::Render(float percent) {
    // jesus christ
    Utils::DrawRect(x+8, y+8, x+22, y+22, colour, percent);

    if (timer < 60) {
        Utils::DrawAnimLine(x+11, y+22, x+11, y+22+(timer < 30 ? 1.0f : 2.0f), colour, percent);
    } else {
        Utils::DrawAnimLine(x+11, y+22, x+11, y+24, colour, percent);
        Utils::DrawAnimLine(x+11, y+24, x+11+((timer - 60.0f) / 14.0f), y+24, colour, percent);
    }
}

void Bomb::Update() {
    timer--;
    if (timer > 75) {
        colour = timer / 25 % 2 == 0 ? 0xFFFFFF : 0xFF0000;
    } else {
        colour = timer / 10 % 2 == 0 ? 0xFFFFFF : 0xFF0000;
    }
}

bool Bomb::Explode() {
    return timer <= 0 && timer > -60;
}

bool Bomb::PostExplode() {
    return timer < -59;
}
