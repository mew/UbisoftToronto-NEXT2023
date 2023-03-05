#pragma once
#include "Bomb.h"
#include "GameObjects.h"
#include "Screen.h"

class GameScreen final : public Screen {
public:
    void InitScreenSpecific() override;
    Tile* GetPlayerTile();
    void DamagePlayer();
    void MovePlayer(bool vertical, int direction);
    void UpdateScreenSpecific() override;
    std::array<Tile*, 4> GetTileNeighbours(int column, int row);
    void RenderScreenSpecific() override;
private:
    bool objectiveComplete = false;
    int garbageLeft = 0;
    int playerHealth = 3;
    int playerImmunity = 60;
    Grid* grid = nullptr;
    TileObject* player = nullptr;
    std::vector<Bomb*> bombs{};
};
