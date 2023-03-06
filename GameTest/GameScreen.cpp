#include "stdafx.h"
#include "GameScreen.h"

#include <array>
#include <iostream>

#include "Bomb.h"
#include "EndScreen.h"
#include "FontRenderer.h"
#include "GameObjects.h"

// 
// Most of the game code is in here.
// 

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

    // create enemies
    //  this is scuffed for a reason, i think?
    for (int i = 0; i < COLUMNS; i++) {
        for (int j = 0; j < ROWS; j++) {
            auto tile = grid->GetTile(i, j);
            if (tile->entity == ENEMY) {
                auto enemy = new TileObject(i, j);
                enemy->colour = 0x0000FF;
                enemies.push_back(enemy);
            }
        }
    }
}

Tile* GameScreen::GetPlayerTile() {
    return grid->GetTile(player->column, player->row);
}

void GameScreen::DamagePlayer() {
    playerImmunity = 60;
    playerHealth--;
}

void GameScreen::MovePlayer(bool vertical, int direction) {
    int c = player->column;
    int r = player->row;
    (vertical ? r : c) += direction;
    auto destTile = grid->GetTile(c, r);
    if (destTile == nullptr) {
        return;
    }
    // can't move if tile is occupied by an obstacle
    if (destTile->Traversable()) {
        destTile->entity = destTile->entity == BOMB ? BOMB : PLAYER;
        auto playerTile = GetPlayerTile();
        playerTile->entity = playerTile->entity == BOMB ? BOMB : BLANK;
        player->Move(c, r);
    }
}

void GameScreen::UpdateScreenSpecific() {
    // try to place a bomb
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

    // move player
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

    // handle bomb explosion
    for (int i = 0; i < bombs.size(); i++) {
        auto bomb = bombs[i];
        bomb->Update();
        auto bombTile = grid->GetTile(bomb->column, bomb->row);
        if (bomb->PostExplode()) {
            bombTile->entity = BLANK;
            bombs.erase(bombs.begin() + i);
            delete bomb;
        } else if (bomb->Explode()) {
            bomb->Sound();
            auto neighbours = GetTileNeighbours(bomb->column, bomb->row);
            auto playerTile = GetPlayerTile();
            for (auto neighbour : neighbours) {
                if (neighbour == nullptr) {
                    continue;
                }
                if (neighbour->entity == OBSTACLE) {
                    neighbour->entity = BLANK;
                }
                if (playerImmunity < 1 && neighbour == playerTile) {
                    DamagePlayer();
                }
                for (int j = 0; j < enemies.size(); j++) {
                    auto enemy = enemies[j];
                    if (enemy->column == neighbour->column && enemy->row == neighbour->row) {
                        enemies.erase(enemies.begin() + j);
                        delete enemy;
                    }
                }
            }
            for (int j = 0; j < enemies.size(); j++) {
                auto enemy = enemies[j];
                if (enemy->column == bombTile->column && enemy->row == bombTile->row) {
                    enemies.erase(enemies.begin() + j);
                    delete enemy;
                }
            }
            if (playerImmunity < 1 && bombTile == playerTile) {
                DamagePlayer();
            }
        }
    }

    // decrease amount of iframes left
    if (playerImmunity > 0) {
        playerImmunity--;
    }

    // check if game over
    if (playerHealth < 1) {
        // todo you lose!
        ChangeScreen(new EndScreen(false));
    }

    // count obstacles remaining
    garbageLeft = 0;
    for (auto tile : grid->gridTiles) {
        if (tile->entity == OBSTACLE) {
            garbageLeft++;
        }
    }
    if (garbageLeft == 0) {
        objectiveComplete = true;

        if (player->column == 0 && player->row == 22) {
            ChangeScreen(new EndScreen(true));
        }
    }

    
    for (auto enemy : enemies) {
        if (playerImmunity < 1) {
            if (enemy->column == player->column && enemy->row == player->row) {
                DamagePlayer();
            }
        }

        // enemy "ai" (this is bad).
        if (enemyMoveTimer < 1) {
            enemyMoveTimer = 90;
            auto enemyTile = grid->GetTile(enemy->column, enemy->row);
            //dulr
            //0123
            auto neighbours = GetTileNeighbours(enemy->column, enemy->row);
            if (player->row > enemyTile->row && neighbours[3] != nullptr && neighbours[3]->Traversable()) {
                enemy->Move(neighbours[3]->column, neighbours[3]->row);
            } else if (player->row < enemyTile->row && neighbours[2] != nullptr && neighbours[2]->Traversable()) {
                enemy->Move(neighbours[2]->column, neighbours[2]->row);
            } else if (player->column > enemyTile->column && neighbours[1] != nullptr && neighbours[1]->Traversable()) {
                enemy->Move(neighbours[1]->column, neighbours[1]->row);
            } else if (player->column < enemyTile->column && neighbours[0] != nullptr && neighbours[0]->Traversable()) {
                enemy->Move(neighbours[0]->column, neighbours[0]->row);
            } else {
                // move to first available neighbour
                for (auto neighbour : neighbours) {
                    if (neighbour == nullptr || !neighbour->Traversable()) {
                        continue;
                    }
                    enemy->Move(neighbour->column, neighbour->row);
                    break;
                }
            }
        } else {
            enemyMoveTimer--;
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
    // render tile decorations
    for (auto tile : grid->gridTiles) {
        tile->Render();
    }

    // draw player
    if (playerImmunity % 2 == 0) {
        // body
        Utils::DrawAnimLine(10+player->x, 0+player->y, 15+player->x, 8+player->y, player->colour);
        Utils::DrawAnimLine(15+player->x, 8+player->y, 20+player->x, 0+player->y, player->colour);
        Utils::DrawAnimLine(15+player->x, 8+player->y, 15+player->x, 18+player->y, player->colour);
        Utils::DrawAnimLine(10+player->x, 13+player->y, 20+player->x, 13+player->y, player->colour);
        // head
        Utils::DrawRect(10+player->x, 18+player->y, 20+player->x, 28+player->y, player->colour);
    }

    // render ui
    if (percent == 1.0f) {
        FontRenderer::DrawString("LEFT", 20, 10+TILE_SIZE*ROWS+10, 0xFFFFFF, 3.0f);
    } else {
        FontRenderer::DrawString("LEFT " + std::to_string(garbageLeft), 20, 10+TILE_SIZE*ROWS+10, 0xFFFFFF, 3.0f);
    }
    std::string life = "LIFE " + std::to_string(playerHealth);
    FontRenderer::DrawString(life, 15+TILE_SIZE*COLUMNS - FontRenderer::GetStringWidth(&life, 3.0f), 10+TILE_SIZE*ROWS+10, 0xFFFFFF, 3.0f);

    // draw finish tile
    if (objectiveComplete) {
        auto finish = grid->GetTile(0, 22);
        Utils::DrawFillRect(finish->x, finish->y, finish->x+30, finish->y+30, 0x00FF00);
    }

    shake = false;
    // draw bomb
    for (auto bomb : bombs) {
        // draw explosion
        if (bomb->Explode()) {
            if (!exit) {
                // enable shaking effect (impl in Utils)
                shake = true;
            }
            auto bombTile = grid->GetTile(bomb->column, bomb->row);
            Utils::DrawFillRect(bombTile->x+2, bombTile->y+2,bombTile->x+28,bombTile->y+28, 0xFF0000);
            auto neighbours = GetTileNeighbours(bomb->column, bomb->row);
            for (Tile* neighbour : neighbours) {
                if (neighbour == nullptr || neighbour->entity == WALL) {
                    continue;
                }
                Utils::DrawFillRect(neighbour->x+2, neighbour->y+2, neighbour->x+28, neighbour->y+28, 0xFF0000);
            }
        } else {
            bomb->Render();
        }
    }

    for (auto enemy : enemies) {
        // basic enemy face
        Utils::DrawRect(enemy->x+5, enemy->y+5, enemy->x+25, enemy->y+25, enemy->colour);
        Utils::DrawAnimLine(enemy->x+10, enemy->y+22.5f, enemy->x+10, enemy->y+16.5f, enemy->colour);
        Utils::DrawAnimLine(enemy->x+20, enemy->y+22.5f, enemy->x+20, enemy->y+16.5f, enemy->colour);
    }
}
