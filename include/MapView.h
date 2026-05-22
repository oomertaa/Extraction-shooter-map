#pragma once
#include <SFML/Graphics.hpp>

class MapView {
    sf::Vector2f m_offset;
    float        m_scale{1.f};

    bool         m_dragging{false};
    sf::Vector2f m_dragAnchorMouse;
    sf::Vector2f m_dragAnchorOffset;
    bool         m_wasDrag{false};

    static constexpr float CLICK_THRESHOLD = 4.f;

public:
    MapView(sf::Vector2u texSize, unsigned winW, unsigned winH);

    // map coords (texture pixels) <-> screen coords (window pixels)
    sf::Vector2f mapToScreen(sf::Vector2f mapPos) const;
    sf::Vector2f screenToMap(sf::Vector2f screenPos) const;

    void applyToSprite(sf::Sprite& sprite) const;

    void onMousePressed(sf::Vector2f screenPos);
    void onMouseMoved(sf::Vector2f screenPos);
    void onMouseReleased(sf::Vector2f screenPos);
    void onMouseWheelScrolled(sf::Vector2f mousePos, float delta);

    // true when press→release involved movement beyond click threshold
    bool wasDragOnRelease() const;

private:
    static constexpr float ZOOM_STEP = 1.15f;
    static constexpr float MIN_SCALE = 0.1f;
    static constexpr float MAX_SCALE = 8.f;
};
