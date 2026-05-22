#include "ExtractionMarker.h"

ExtractionMarker::ExtractionMarker(sf::Vector2f position, std::string description)
    : MapMarker(position), m_description(std::move(description))
{}

void ExtractionMarker::draw(sf::RenderWindow& window, sf::Vector2f screenPos) const
{
    sf::CircleShape shape(DRAW_RADIUS);
    shape.setOrigin(DRAW_RADIUS, DRAW_RADIUS);
    shape.setFillColor(sf::Color(0, 220, 80));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1.5f);
    shape.setPosition(screenPos);
    window.draw(shape);
}

bool ExtractionMarker::contains(sf::Vector2f mapPos) const
{
    sf::Vector2f d = mapPos - m_position;
    return (d.x * d.x + d.y * d.y) <= HIT_RADIUS * HIT_RADIUS;
}

const char* ExtractionMarker::type() const { return "extraction"; }

const std::string& ExtractionMarker::description() const { return m_description; }
