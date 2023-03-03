#pragma once
#include "Component.h"

class RectComponent : public Component {
public:
    RectComponent(float x, float y, float w, float h);
    
    void Render(float percent) override;
    float w, h;
    int colour = 0xFFFFFF;
    
    virtual ~RectComponent() = default;
};
