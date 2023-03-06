#pragma once
#include <functional>
#include <string>

#include "Component.h"

/**
 * \brief Simple button for the end and title screens
 */
class Button final : public Component {
public:
    // The action function is called when the button is clicked
    Button(float x, float y, float w, float h, std::string text, std::function<void()> action);

    void Render() override;
    void Update() override;
    
    float w, h;
    int hoverColour = 0x00FF00;
    std::function<void()> onClick;
private:
    std::string buttonText;
};