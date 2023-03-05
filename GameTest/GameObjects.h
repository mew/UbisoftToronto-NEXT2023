#pragma once

#include <vector>
#include "Components.h"
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
    
    void Render(float percent) override;
    bool Traversable();
    TileEntity entity;
    int column, row;
private:
    std::vector<std::vector<std::pair<LiteralPos, LiteralPos>>> cracks{};
};

class TileObject : public Component {
public:
    TileObject(int column, int row);

    void Move(int column, int row);
    int column, row;
protected:
    ~TileObject() = default;
};

class Grid final : public Component {
public:
    void InitGrid();
    void Update() override;
    void Render(float percent) override;
    Tile* GetTile(int x, int y) const;
    std::vector<Tile*> gridTiles{};
private:
    
};

class Enemy {
    
};
