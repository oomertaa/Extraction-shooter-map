#include "BossMarker.h"

BossMarker::BossMarker(sf::Vector2f position, std::string description)
    : MapMarker(position), m_description(std::move(description))
{}

void BossMarker::draw(sf::RenderWindow& window, sf::Vector2f screenPos) const
{
    sf::CircleShape shape(DRAW_RADIUS);
    shape.setOrigin(DRAW_RADIUS, DRAW_RADIUS);
    shape.setFillColor(sf::Color(200, 0, 0));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.f);
    shape.setPosition(screenPos);
    window.draw(shape);
}

bool BossMarker::contains(sf::Vector2f mapPos) const
{
    sf::Vector2f d = mapPos - m_position;
    return (d.x * d.x + d.y * d.y) <= HIT_RADIUS * HIT_RADIUS;
}

const char* BossMarker::type() const { return "boss"; }

const std::string& BossMarker::description() const { return m_description; }
float BossMarker::drawRadius() const { return DRAW_RADIUS; }

std::vector<std::string> BossMarker::info() const
{
    return { "BOSS SPAWN", m_description };
}
