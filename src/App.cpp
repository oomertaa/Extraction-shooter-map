#include "App.h"
#include "ConfigManager.h"
#include <stdexcept>

App::App()
{
    auto& cfg = ConfigManager::instance();

    m_window.create(sf::VideoMode(cfg.windowWidth(), cfg.windowHeight()),
                    "Zero Dam - Map Reference");
    m_window.setFramerateLimit(60);
    m_window.setMouseCursorVisible(false);

    if (!m_mapTexture.loadFromFile(cfg.mapPath()))
        throw std::runtime_error("Cannot load map texture: " + cfg.mapPath());

    m_mapView.emplace(m_mapTexture.getSize(), cfg.windowWidth(), cfg.windowHeight());
    m_mapSprite.setTexture(m_mapTexture);

    if (!m_markerTexture.loadFromFile("data/test_sprite.png"))
        throw std::runtime_error("Cannot load marker texture");

    m_markerSprite.setTexture(m_markerTexture);
    m_markerSprite.setOrigin(m_markerTexture.getSize().x / 2.f,
                             m_markerTexture.getSize().y / 2.f);

    m_markerPositions = {{500.f, 400.f}, {600.f, 350.f}};
}

void App::run()
{
    constexpr float ARM = 10.f;

    while (m_window.isOpen())
    {
        handleEvents();

        sf::Vector2i mouse = sf::Mouse::getPosition(m_window);
        float mx = static_cast<float>(mouse.x);
        float my = static_cast<float>(mouse.y);

        m_mapView->applyToSprite(m_mapSprite);

        sf::Vertex hLine[] = {
            sf::Vertex(sf::Vector2f(mx - ARM, my), sf::Color::White),
            sf::Vertex(sf::Vector2f(mx + ARM, my), sf::Color::White)
        };
        sf::Vertex vLine[] = {
            sf::Vertex(sf::Vector2f(mx, my - ARM), sf::Color::White),
            sf::Vertex(sf::Vector2f(mx, my + ARM), sf::Color::White)
        };

        m_window.clear(sf::Color::Black);
        render();
        m_window.draw(hLine, 2, sf::Lines);
        m_window.draw(vLine, 2, sf::Lines);
        m_window.display();
    }
}

void App::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape)
            m_window.close();

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
            m_mapView->onMousePressed({
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
            });

        if (event.type == sf::Event::MouseMoved)
            m_mapView->onMouseMoved({
                static_cast<float>(event.mouseMove.x),
                static_cast<float>(event.mouseMove.y)
            });

        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left)
            m_mapView->onMouseReleased({
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
            });
    }
}

void App::render()
{
    m_window.draw(m_mapSprite);
    for (const auto& pos : m_markerPositions)
    {
        m_markerSprite.setPosition(m_mapView->mapToScreen(pos));
        m_window.draw(m_markerSprite);
    }
}
