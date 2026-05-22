#pragma once
#include "MapMarker.h"
#include <string>

class BossMarker : public MapMarker {
public:
    BossMarker(sf::Vector2f position, std::string description);

    void        draw(sf::RenderWindow& window, sf::Vector2f screenPos) const override;
    bool        contains(sf::Vector2f mapPos) const override;
    const char* type() const override;

    const std::string& description() const;

private:
    std::string m_description;

    static constexpr float HIT_RADIUS  = 20.f;
    static constexpr float DRAW_RADIUS = 13.f;
};
