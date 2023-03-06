#pragma once
#include <string>

#include "Component.h"

/**
 * \brief Simple text component
 */
class Label final : public Component {
public:
    Label(float x, float y, std::string text, float scale = 1.0f);

    void Render() override;
    float scale;
    std::string text;
    
    virtual ~Label() = default;
};
