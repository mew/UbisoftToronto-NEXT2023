#pragma once
#include <string>

#include "Component.h"

class RectComponent : public Component {
public:
    RectComponent(float x, float y, float w, float h);
    
    void Render(float percent) override;
    float w, h;
    int colour = 0xFFFFFF;
    
    virtual ~RectComponent() = default;
};

class Label : public Component {
public:
    Label(float x, float y, std::string text, float scale = 1.0f);

    void Render(float percent) override;
    int colour = 0xFFFFFF;
    float scale;
    std::string text;
    
    virtual ~Label() = default;
};