#pragma once
#include "Screen.h"

class EndScreen final : public Screen {
public:
    explicit EndScreen(bool w);
    void InitScreenSpecific() override;
private:
    
};
