#pragma once

class Component {
public:
    virtual void Render(float percent) {}
    virtual void MouseOver() {}
    virtual void KeyPress() {}

    float x, y;
protected:
    ~Component() = default;
};
