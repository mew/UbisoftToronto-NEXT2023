#pragma once
#include "GameObjects.h"

class Bomb final : public TileObject {
public:
    Bomb(int column, int row);

    void Render(float percent) override;
    void Update() override;
    bool Explode();
    bool PostExplode();

private:
    // 3.5 seconds
    int timer = 210;
};
