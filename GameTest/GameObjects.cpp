#include "stdafx.h"
#include "GameObjects.h"

#include <iostream>

#include "utils.h"

Tile::Tile(int column, int row, TileEntity start) {
    this->column = column;
    this->row = row;
    auto l = Utils::GridToLiteral(column, row);
    this->x = l.x;
    this->y = l.y;
    entity = start;

    // generate cracks
    if (entity == OBSTACLE) {
        for (int i = 0; i < (rand() % 11) + 1; i++) {
            std::vector<std::pair<LiteralPos, LiteralPos>> crack{};
            for (int j = 0; j < (rand() % 4) + 1; j++) {
                LiteralPos first{};
                if (j == 0) {
                    int rp = rand() % TILE_SIZE;
                    if (rand() % 2) {
                        first.x = rp;
                    } else {
                        first.y = rp;
                    }
                } else {
                    first = crack[rand() % crack.size()].second;
                }
                LiteralPos second{};
                // that's a first
                do {
                    second.x = rand() % TILE_SIZE;
                    second.y = rand() % TILE_SIZE;
                } while (abs(first.x - second.x) <= 4 && abs(first.y - second.y) <= 4);

                crack.emplace_back(first, second);
            }
            cracks.push_back(crack);
        }
    }
}

void Tile::Render() {
    if (entity == WALL) {
        Utils::DrawRect(x, y, x+TILE_SIZE, y+TILE_SIZE, 0xBBBBBB);
    } else if (entity == OBSTACLE) {
        // draw obstacle with random lines inside to differentiate from immovable walls
        Utils::DrawRect(x, y, x+TILE_SIZE, y+TILE_SIZE, 0xBBBBBB);
        for (auto lines : cracks) {
            for (auto line : lines) {
                Utils::DrawAnimLine(line.first.x + x, line.first.y + y, line.second.x + x, line.second.y + y, 0x999999);
            }
        }
    }
}

bool Tile::Traversable() const {
    return entity == BLANK || entity == BOMB || entity == ENEMY || entity == PLAYER;
}

TileObject::TileObject(int column, int row) {
    this->column = column;
    this->row = row;
    Move(column, row);
}

void TileObject::Move(int column, int row) {
    this->column = column;
    this->row = row;
    // we need to set the render position too
    auto l = Utils::GridToLiteral(column, row);
    this->x = l.x;
    this->y = l.y;
}

void Grid::InitGrid() {
    // you don't want to know
    for (int i = 0; i < COLUMNS; i++) {
        auto column = std::vector<Tile*>{};
        for (int j = 0; j < ROWS; j++) {
            auto te = BLANK;
            if (j % 2 == 1 && i % 2 == 1) {
                te = WALL;
            } else {
                if (j < 20 || i > 2) {
                    int r = rand() % 100;
                    if (r < 25) {
                        if (r < 3) {
                            te = ENEMY;
                        } else {
                            te = OBSTACLE;
                        }
                    }
                }
            }
            gridTiles.push_back(new Tile(i, j, te));
        }
    }
}

#ifdef _DEBUG
int t = 0;
#endif
void Grid::Update() {
#ifdef _DEBUG
    // if (App::IsKeyPressed(VK_LBUTTON)) {
    //     if (t == 1) {
    //         return;
    //     }
    //     t = 1;
    //     float mx, my;
    //     App::GetMousePos(mx, my);
    //     auto g = Utils::LiteralToGrid(mx, my);
    //     auto t = GetTile(g.x, g.y);
    //     std::cout << "Tile(" << t->column <<"," << t->row << ") " << t->entity << std::endl;
    // } else {
    //     t = 0;
    // }
#endif
}

void Grid::Render() {
    Utils::DrawRect(15, 10, 15+TILE_SIZE*COLUMNS, 10+TILE_SIZE*ROWS, 0xFFFFFF);
}

Tile* Grid::GetTile(const int column, const int row) const {
    if (column < 0 || column >= COLUMNS || row < 0 || row >= ROWS) {
        return nullptr;
    }
    return gridTiles[column * ROWS + row];
}
