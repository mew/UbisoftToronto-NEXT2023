#pragma once
#include "Screen.h"

class TitleScreen : public Screen {
public:
    void InitScreenSpecific() override;
    void UpdateScreenSpecific() override;
    void ExitScreenSpecific() override;
};
