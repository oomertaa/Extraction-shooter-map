#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "MapView.h"
#include "ConfigManager.h"

int main()
{
    auto& cfg = ConfigManager::instance();

    sf::RenderWindow window(
        sf::VideoMode(cfg.windowWidth(), cfg.windowHeight()),
        "Zero Dam - Map Reference");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile(cfg.mapPath()))
        return 1;

    MapView mapView(mapTexture.getSize(), cfg.windowWidth(), cfg.windowHeight());

    sf::Sprite mapSprite(mapTexture);
    mapView.applyToSprite(mapSprite);

    sf::Texture testTexture;
    if (!testTexture.loadFromFile("data/test_sprite.png"))
        return 1;

    // center origin so the sprite sits on top of the map coordinate
    sf::Sprite testSprite(testTexture);
    testSprite.setOrigin(testTexture.getSize().x / 2.f, testTexture.getSize().y / 2.f);

    // two test positions matching markers.json
    const std::vector<sf::Vector2f> markerPositions = {
        {500.f, 400.f},
        {600.f, 350.f}
    };

    const float ARM = 10.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                mapView.onMousePressed({
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y)
                });
            }
            if (event.type == sf::Event::MouseMoved)
            {
                mapView.onMouseMoved({
                    static_cast<float>(event.mouseMove.x),
                    static_cast<float>(event.mouseMove.y)
                });
            }
            if (event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f releasePos(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y)
                );
                mapView.onMouseReleased(releasePos);
            }
        }

        sf::Vector2i m  = sf::Mouse::getPosition(window);
        float        mx = static_cast<float>(m.x);
        float        my = static_cast<float>(m.y);

        mapView.applyToSprite(mapSprite);

        sf::Vertex hLine[] = {
            sf::Vertex(sf::Vector2f(mx - ARM, my), sf::Color::White),
            sf::Vertex(sf::Vector2f(mx + ARM, my), sf::Color::White)
        };
        sf::Vertex vLine[] = {
            sf::Vertex(sf::Vector2f(mx, my - ARM), sf::Color::White),
            sf::Vertex(sf::Vector2f(mx, my + ARM), sf::Color::White)
        };

        window.clear(sf::Color::Black);
        window.draw(mapSprite);
        for (const auto& pos : markerPositions)
        {
            testSprite.setPosition(mapView.mapToScreen(pos));
            window.draw(testSprite);
        }
        window.draw(hLine, 2, sf::Lines);
        window.draw(vLine, 2, sf::Lines);
        window.display();
    }

    return 0;
}
