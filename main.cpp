#include <SFML/Graphics.hpp>
#include <algorithm>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Zero Dam - Map Reference");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("data/map.png"))
        return 1;

    sf::Sprite mapSprite(mapTexture);
    sf::Vector2u texSize = mapTexture.getSize();
    float scale = std::min(1600.f / static_cast<float>(texSize.x),
                            900.f / static_cast<float>(texSize.y));
    mapSprite.setScale(scale, scale);
    mapSprite.setPosition((1600.f - texSize.x * scale) / 2.f,
                           (900.f  - texSize.y * scale) / 2.f);

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
        }

        sf::Vector2i m = sf::Mouse::getPosition(window);
        float mx = static_cast<float>(m.x);
        float my = static_cast<float>(m.y);

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
        window.draw(hLine, 2, sf::Lines);
        window.draw(vLine, 2, sf::Lines);
        window.display();
    }

    return 0;
}
