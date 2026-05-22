#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "MapView.h"
#include "MapMarker.h"
#include "Repository.h"
#include <memory>
#include <string>

class App {
public:
    App();
    void run();

    App(const App&)            = delete;
    App& operator=(const App&) = delete;

private:
    void handleEvents();
    void render();

    sf::RenderWindow           m_window;
    sf::Texture                m_mapTexture;
    sf::Sprite                 m_mapSprite;
    std::optional<MapView>     m_mapView;
    Repository<MapMarker>      m_markers;

    sf::RectangleShape         m_leftPanel;
    sf::RectangleShape         m_rightPanel;
    sf::Font                   m_font;
    std::weak_ptr<MapMarker>   m_selectedMarker;
};
