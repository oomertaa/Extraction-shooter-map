#pragma once
#include "MapMarker.h"
#include "LootContainer.h"

class LootMarker : public MapMarker {
public:
    LootMarker(sf::Vector2f position, LootContainer container);

    void        draw(sf::RenderWindow& window, sf::Vector2f screenPos) const override;
    bool        contains(sf::Vector2f mapPos) const override;
    const char* type() const override;

    const LootContainer& container() const;

private:
    LootContainer m_container;
    sf::Texture           m_texture;
    mutable sf::Sprite    m_sprite;

    static constexpr float HIT_RADIUS = 15.f;
};
