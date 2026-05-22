#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "MapView.h"

class App {
public:
    App();
    void run();

    App(const App&)            = delete;
    App& operator=(const App&) = delete;

private:
    void handleEvents();
    void render();

    sf::RenderWindow       m_window;
    sf::Texture            m_mapTexture;
    sf::Sprite             m_mapSprite;
    std::optional<MapView> m_mapView;

    sf::Texture            m_markerTexture;
    sf::Sprite             m_markerSprite;

    // temporary placeholder — will be replaced by Repository<MapMarker>
    std::vector<sf::Vector2f> m_markerPositions;
};
