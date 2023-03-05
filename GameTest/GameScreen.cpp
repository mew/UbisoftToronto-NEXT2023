#include "stdafx.h"
#include "GameScreen.h"

#include <array>
#include <iostream>

#include "Bomb.h"
#include "GameObjects.h"

void GameScreen::InitScreenSpecific() {
    // lol
    srand(time(nullptr));
    // create grid
    grid = new Grid();
    grid->InitGrid();
    components.push_back(grid);

    // create player
    //  player logic is all handled here because i had problems
    //  when it was in it's own class
    this->player = new TileObject(0, 22);
    components.push_back(player);
}

Tile* GameScreen::GetPlayerTile() {
    return grid->GetTile(player->column, player->row);
}

void GameScreen::MovePlayer(bool vertical, int direction) {
    int c = player->column;
    int r = player->row;
    (vertical ? r : c) += direction;
    auto destTile = grid->GetTile(c, r);
    if (destTile == nullptr) {
        return;
    }
    std::cout << "Tile(" << destTile->column << "," << destTile->row << ")" << destTile->entity << std::endl;
    if (destTile->Traversable()) {
        destTile->entity = destTile->entity == BOMB ? BOMB : PLAYER;
        auto playerTile = GetPlayerTile();
        playerTile->entity = playerTile->entity == BOMB ? BOMB : BLANK;
        player->Move(c, r);
    }
}


int moveTimer = 0;
int bombTimer = 0;
void GameScreen::UpdateScreenSpecific() {
    if (App::IsKeyPressed(VK_SPACE) && bombTimer <= 0) {
        auto playerTile = GetPlayerTile();
        if (playerTile->entity != BOMB) {
            bombs.push_back(new Bomb(player->column, player->row));
            playerTile->entity = BOMB;
            bombTimer = 15;
        }
    } else {
        bombTimer--;
    }
    
    if (moveTimer <= 0) {
        moveTimer = 5;
        if (App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed('D')) {
            MovePlayer(false, 1);
        } else if (App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed('A')) {
            MovePlayer(false, -1);
        } else if (App::IsKeyPressed(VK_UP) || App::IsKeyPressed('W')) {
            MovePlayer(true, 1);
        } else if (App::IsKeyPressed(VK_DOWN) || App::IsKeyPressed('S')) {
            MovePlayer(true, -1);
        } else {
            moveTimer = 0;
        }
    } else {
        moveTimer--;
    }

    for (int i = 0; i < bombs.size(); i++) {
        auto bomb = bombs[i];
        bomb->Update();
        if (bomb->PostExplode()) {
            grid->GetTile(bomb->column, bomb->row)->entity = BLANK;
            bombs.erase(bombs.begin() + i);
            delete bomb;
        } else if (bomb->Explode()) {
            auto neighbours = GetTileNeighbours(bomb->column, bomb->row);
            for (auto neighbour : neighbours) {
                if (neighbour != nullptr && neighbour->entity == OBSTACLE) {
                    neighbour->entity = BLANK;
                }
            }
        }
    }
}

std::array<Tile*, 4> GameScreen::GetTileNeighbours(int column, int row) {
    return {
        grid->GetTile(column - 1, row),
        grid->GetTile(column + 1, row),
        grid->GetTile(column, row - 1),
        grid->GetTile(column, row + 1)
    };
}

void GameScreen::RenderScreenSpecific() {
    for (auto tile : grid->gridTiles) {
        tile->Render(percent);
    }

    // body
    Utils::DrawAnimLine(10+player->x, 0+player->y, 15+player->x, 8+player->y, player->colour, percent);
    Utils::DrawAnimLine(15+player->x, 8+player->y, 20+player->x, 0+player->y, player->colour, percent);
    Utils::DrawAnimLine(15+player->x, 8+player->y, 15+player->x, 18+player->y, player->colour, percent);
    Utils::DrawAnimLine(10+player->x, 13+player->y, 20+player->x, 13+player->y, player->colour, percent);

    // head
    Utils::DrawRect(10+player->x, 18+player->y, 20+player->x, 28+player->y, player->colour, percent);
    
    for (auto bomb : bombs) {
        if (bomb->Explode()) {
            auto bombTile = grid->GetTile(bomb->column, bomb->row);
            Utils::DrawFillRect(bombTile->x+2, bombTile->y+2,bombTile->x+28,bombTile->y+28, 0xFF0000, percent);
            auto neighbours = GetTileNeighbours(bomb->column, bomb->row);
            for (Tile* neighbour : neighbours) {
                if (neighbour == nullptr || neighbour->entity == WALL) {
                    continue;
                }
                Utils::DrawFillRect(neighbour->x+2, neighbour->y+2, neighbour->x+28, neighbour->y+28, 0xFF0000, percent);
            }
        } else {
            bomb->Render(percent);
        }
    }
}
