#pragma once
#include "Screen.h"

class EndScreen final : public Screen {
public:
    /**
     * \brief Screen displayed after the game.
     * \param w did player win
     */
    explicit EndScreen(bool w);
};
