#pragma once

#include <vector>
#include "Component.h"
#include "Utils.h"

#define COLUMNS 33
#define ROWS 23
#define TILE_SIZE 30

enum TileEntity {
    BLANK,
    WALL,
    OBSTACLE,
    ENEMY,
    PLAYER,
    BOMB,
};

// 40 columns, 30 rows
class Tile final : public Component {
public:
    Tile(int column, int row, TileEntity start = BLANK);
    
    /**
     * \brief Render obstacle or wall present at tile
     */
    void Render() override;
    
    /**
     * \brief Check if entities present on the tile allow for traversal.
     * \return Can you walk on the tile?
     */
    bool Traversable() const;
    
    TileEntity entity;
    int column, row;
private:
    std::vector<std::vector<std::pair<LiteralPos, LiteralPos>>> cracks{};
};

class TileObject : public Component {
public:
    TileObject(int column, int row);
    
    /**
     * \brief Move entity to a new position on the grid.
     * \param column column of new position on grid
     * \param row row of new position on grid
     */
    void Move(int column, int row);
    // Entity's position
    int column, row;

    virtual ~TileObject() = default;
};

class Grid final : public Component {
public:
    /**
     * \brief Initialise the grid.
     */
    void InitGrid();
    void Update() override;

    
    /**
     * \brief Render grid's outline
     */
    void Render() override;
    
    /**
     * \brief Get a pointer to Tile object on grid.
     * \param column column position on grid
     * \param row row position on grid
     * \return Pointer to tile at specified grid position
     */
    Tile* GetTile(int column, int row) const;
    
    // Vector of all tiles in grid
    std::vector<Tile*> gridTiles{};
};