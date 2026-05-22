#include "LootMarker.h"
#include <stdexcept>

LootMarker::LootMarker(sf::Vector2f position, LootContainer container)
    : MapMarker(position), m_container(std::move(container))
{
    if (!m_texture.loadFromFile("data/15px_loot_sprite.png"))
        throw std::runtime_error("Cannot load loot sprite");
    m_sprite.setTexture(m_texture);
    auto size = m_texture.getSize();
    m_sprite.setOrigin(size.x / 2.f, size.y / 2.f);
}

void LootMarker::draw(sf::RenderWindow& window, sf::Vector2f screenPos) const
{
    m_sprite.setPosition(screenPos);
    window.draw(m_sprite);
}

bool LootMarker::contains(sf::Vector2f mapPos) const
{
    sf::Vector2f d = mapPos - m_position;
    return (d.x * d.x + d.y * d.y) <= HIT_RADIUS * HIT_RADIUS;
}

const char* LootMarker::type() const { return "loot"; }

const LootContainer& LootMarker::container() const { return m_container; }
