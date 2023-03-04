#pragma once
#include <functional>
#include <string>

class Component {
public:
    virtual void Render(float percent) {}
    virtual void Update() {}
    virtual void KeyPress() {}

    float x = 0;
    float y = 0;
    int colour = 0xFFFFFF;
protected:
    ~Component() = default;
};

class RectComponent : public Component {
public:
    RectComponent(float x, float y, float w, float h);
    
    void Render(float percent) override;
    float w, h;
    
    virtual ~RectComponent() = default;
};

class Label : public Component {
public:
    Label(float x, float y, std::string text, float scale = 1.0f);

    void Render(float percent) override;
    float scale;
    std::string text;
    
    virtual ~Label() = default;
};

class Button final : public Component {
public:
    Button(float x, float y, float w, float h, std::string text, std::function<void()> action);

    void Render(float percent) override;
    void Update() override;
    
    float w, h;
    int hoverColour = 0x00FF00;
    std::function<void()> onClick;
private:
    std::string buttonText;
};