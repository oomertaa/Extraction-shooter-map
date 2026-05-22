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

    const sf::Vector2f markerMapPos(500.f, 400.f);
    const float        markerRadius = 12.f;

    sf::CircleShape markerShape(markerRadius);
    markerShape.setFillColor(sf::Color(220, 50, 50, 200));
    markerShape.setOrigin(markerRadius, markerRadius);

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

                if (!mapView.wasDragOnRelease())
                {
                    sf::Vector2f markerScreen = mapView.mapToScreen(markerMapPos);
                    sf::Vector2f diff         = releasePos - markerScreen;
                    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
                    if (dist <= markerRadius)
                        std::cout << "clicked\n";
                }
            }
        }

        sf::Vector2i m  = sf::Mouse::getPosition(window);
        float        mx = static_cast<float>(m.x);
        float        my = static_cast<float>(m.y);

        mapView.applyToSprite(mapSprite);
        markerShape.setPosition(mapView.mapToScreen(markerMapPos));

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
        window.draw(markerShape);
        window.draw(hLine, 2, sf::Lines);
        window.draw(vLine, 2, sf::Lines);
        window.display();
    }

    return 0;
}
