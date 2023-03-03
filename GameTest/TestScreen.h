#pragma once
#include "Screen.h"

class TestScreen : public Screen {
public:
    void InitScreenSpecific() override;
    void UpdateScreenSpecific() override;
    void ExitScreenSpecific() override;
    
public:
    ~TestScreen() = default;
};
