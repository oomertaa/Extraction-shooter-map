#include "LootMarker.h"

LootMarker::LootMarker(sf::Vector2f position, LootContainer container)
    : MapMarker(position), m_container(std::move(container))
{}

void LootMarker::draw(sf::RenderWindow& window, sf::Vector2f screenPos) const
{
    sf::CircleShape shape(DRAW_RADIUS);
    shape.setOrigin(DRAW_RADIUS, DRAW_RADIUS);
    shape.setFillColor(sf::Color(255, 220, 0));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1.f);
    shape.setPosition(screenPos);
    window.draw(shape);
}

bool LootMarker::contains(sf::Vector2f mapPos) const
{
    sf::Vector2f d = mapPos - m_position;
    return (d.x * d.x + d.y * d.y) <= HIT_RADIUS * HIT_RADIUS;
}

const char* LootMarker::type() const { return "loot"; }

const LootContainer& LootMarker::container() const { return m_container; }
float LootMarker::drawRadius() const { return DRAW_RADIUS; }

std::vector<std::string> LootMarker::info() const
{
    std::vector<std::string> lines;
    lines.push_back("LOOT CONTAINER");
    lines.push_back("Kind: " + containerKindToString(m_container.kind()));
    if (m_container.isSafe())
        lines.push_back("[ Safe ]");
    if (!m_container.notableDrops().empty()) {
        lines.push_back("");
        lines.push_back("Notable drops:");
        for (const auto& drop : m_container.notableDrops())
            lines.push_back("  " + drop);
    }
    return lines;
}
