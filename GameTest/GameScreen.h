#pragma once
#include "Bomb.h"
#include "GameObjects.h"
#include "Screen.h"

class GameScreen final : public Screen {
public:
    void InitScreenSpecific() override;
    /**
     * \brief Gets the tile the player is currently standing on
     * \return Tile player is currently on
     */
    Tile* GetPlayerTile();
    
    void UpdateScreenSpecific() override;
    void RenderScreenSpecific() override;
private:
    /**
     * \brief Deal damage to the player and give them iframes
     */
    void DamagePlayer();
    
    /**
     * \brief Move player in positive or negative direction.
     *          x/y determined by vertical parameter
     * \param vertical moving vertically?
     * \param direction positive or negative direction
     */
    void MovePlayer(bool vertical, int direction);

    /**
     * \brief Get adjacent tiles from grid position.
     * \return array of adjacent tiles
     */
    std::array<Tile*, 4> GetTileNeighbours(int column, int row);
    
    bool objectiveComplete = false;
    int garbageLeft = 0;
    int playerHealth = 3;
    int playerImmunity = 60;
    int moveTimer = 0;
    int bombTimer = 0;
    int enemyMoveTimer = 60;
    Grid* grid = nullptr;
    TileObject* player = nullptr;
    std::vector<Bomb*> bombs{};
    std::vector<TileObject*> enemies{};
};
