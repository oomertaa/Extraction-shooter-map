#pragma once
#include <SFML/Graphics.hpp>

class MapMarker {
public:
    explicit MapMarker(sf::Vector2f position);
    virtual ~MapMarker() = default;

    virtual void draw(sf::RenderWindow& window, sf::Vector2f screenPos) const = 0;
    virtual bool contains(sf::Vector2f mapPos) const = 0;
    virtual const char* type() const = 0;

    sf::Vector2f position() const;
    bool         visible()  const;
    void         setVisible(bool v);

protected:
    sf::Vector2f m_position;
    bool         m_visible{true};
};
