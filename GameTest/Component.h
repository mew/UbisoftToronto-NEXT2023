#pragma once

/**
 * \brief for ui elements , mostly
 */
class Component {
public:
    virtual void Render() {}
    virtual void Update() {}

    float x = 0;
    float y = 0;
    int colour = 0xFFFFFF;
protected:
    ~Component() = default;
};
