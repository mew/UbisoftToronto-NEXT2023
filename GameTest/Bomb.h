#pragma once
#include "GameObjects.h"

class Bomb final : public TileObject {
public:
    Bomb(int column, int row);

    void Render() override;
    void Update() override;
    
    /**
     * \brief Play the explosion sound once per bomb
     */
    void Sound();
    /**
     * \brief Checks if the timer is up
     * \return Is the bomb exploding?
     */
    bool Explode();
    /**
     * \brief Check if the bomb has been exploding for longer than a second
     * \return Is the bomb done exploding?
     */
    bool PostExplode();

private:
    // 3.5 seconds
    int timer = 210;

    bool played = false;
};
