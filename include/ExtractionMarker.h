#pragma once
#include "MapMarker.h"
#include <string>

class ExtractionMarker : public MapMarker {
public:
    ExtractionMarker(sf::Vector2f position, std::string description);

    void        draw(sf::RenderWindow& window, sf::Vector2f screenPos) const override;
    bool        contains(sf::Vector2f mapPos) const override;
    const char* type() const override;

    const std::string& description() const;
    std::vector<std::string> info() const override;
    float drawRadius() const override;

private:
    std::string m_description;

    static constexpr float HIT_RADIUS  = 18.f;
    static constexpr float DRAW_RADIUS = 10.f;
};
