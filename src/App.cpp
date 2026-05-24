#include "App.h"
#include "ConfigManager.h"
#include "MarkerFactory.h"
#include "LootMarker.h"
#include "RepoUtils.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>

App::App()
{
    auto& cfg = ConfigManager::instance();

    m_window.create(sf::VideoMode(cfg.windowWidth(), cfg.windowHeight()),
                    "Zero Dam - Map Reference");
    m_window.setFramerateLimit(60);
    m_window.setMouseCursorVisible(false);

    if (!m_mapTexture.loadFromFile(cfg.mapPath()))
        throw std::runtime_error("Cannot load map texture: " + cfg.mapPath());

    m_mapView = std::make_unique<MapView>(m_mapTexture.getSize(), cfg.windowWidth(), cfg.windowHeight(),
                                          cfg.leftPanelWidth(), cfg.rightPanelWidth());
    m_mapSprite.setTexture(m_mapTexture);

    m_markers.load("data/markers.json", MarkerFactory::create);

    float winH = static_cast<float>(cfg.windowHeight());
    float leftW = static_cast<float>(cfg.leftPanelWidth());
    float rightW = static_cast<float>(cfg.rightPanelWidth());
    float winW = static_cast<float>(cfg.windowWidth());

    m_leftPanel.setSize({leftW, winH});
    m_leftPanel.setPosition(0.f, 0.f);
    m_leftPanel.setFillColor(sf::Color(72, 40, 15));

    if (!m_font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
        throw std::runtime_error("Cannot load font");

    m_filterPanel = std::make_unique<FilterPanel>(
        winW - rightW, 0.f, rightW, winH, m_font);

    for (const auto& marker : m_markers.all()) {
        if (std::string(marker->type()) == "loot") {
            auto lm = std::dynamic_pointer_cast<LootMarker>(marker);
            if (lm)
                m_filterPanel->addLootContainer(
                    std::make_shared<LootContainer>(lm->container()));
        }
    }

    std::size_t lootCount = countIf<MapMarker>(m_markers,
        [](const MapMarker& m){ return std::string(m.type()) == "loot"; });
    std::cout << "Loaded " << lootCount << " loot markers\n";
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

        m_window.clear(sf::Color(40, 40, 40));
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
        {
            sf::Vector2f pos(static_cast<float>(event.mouseButton.x),
                             static_cast<float>(event.mouseButton.y));
            if (!m_filterPanel->contains(pos))
                m_mapView->onMousePressed(pos);
        }

        if (event.type == sf::Event::MouseMoved)
            m_mapView->onMouseMoved({
                static_cast<float>(event.mouseMove.x),
                static_cast<float>(event.mouseMove.y)
            });

        if (event.type == sf::Event::MouseWheelScrolled &&
            event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            m_mapView->onMouseWheelScrolled(
                { static_cast<float>(event.mouseWheelScroll.x),
                  static_cast<float>(event.mouseWheelScroll.y) },
                event.mouseWheelScroll.delta
            );

        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f releasePos(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
            );

            if (m_filterPanel->contains(releasePos)) {
                m_filterPanel->handleClick(releasePos);
            } else {
                m_mapView->onMouseReleased(releasePos);

                if (!m_mapView->wasDragOnRelease())
                {
                    sf::Vector2f mapPos = m_mapView->screenToMap(releasePos);
                    auto hit = findFirst<MapMarker>(m_markers,
                        [&](const MapMarker& m){ return m.contains(mapPos); });
                    if (hit) {
                        m_selectedMarker = hit;
                        std::cout << "Clicked: " << hit->type()
                                  << " at (" << std::fixed << std::setprecision(0)
                                  << hit->position().x << ", " << hit->position().y << ")\n";
                    } else {
                        m_selectedMarker.reset();
                        std::cout << "  { \"type\": \"loot\", \"x\": " << std::fixed << std::setprecision(0)
                                  << mapPos.x << ", \"y\": " << mapPos.y << ", \"kind\": \"StorageBox\" },\n";
                    }
                }
            }
        }
    }
}

void App::render()
{
    m_window.draw(m_mapSprite);
    auto selected = m_selectedMarker.lock();
    for (const auto& marker : m_markers.all())
    {
        if (!marker->visible()) continue;
        if (!m_filterPanel->isTypeVisible(marker->type())) continue;
        if (std::string(marker->type()) == "loot") {
            auto lm = std::dynamic_pointer_cast<LootMarker>(marker);
            if (lm && !m_filterPanel->isKindVisible(lm->container().kind())) continue;
        }
        sf::Vector2f screenPos = m_mapView->mapToScreen(marker->position());
        if (selected && marker == selected) {
            float r = marker->drawRadius() + 7.f;
            sf::CircleShape ring(r);
            ring.setOrigin(r, r);
            ring.setFillColor(sf::Color(255, 255, 255, 50));
            ring.setOutlineColor(sf::Color(255, 255, 255, 140));
            ring.setOutlineThickness(2.f);
            ring.setPosition(screenPos);
            m_window.draw(ring);
        }
        marker->draw(m_window, screenPos);
    }
    m_window.draw(m_leftPanel);
    m_filterPanel->draw(m_window);

    if (auto selected = m_selectedMarker.lock()) {
        const float padding = 14.f;
        float y = padding;
        const auto lines = selected->info();
        for (const auto& line : lines) {
            sf::Text text;
            text.setFont(m_font);
            text.setString(line);
            text.setCharacterSize(line == lines.front() ? 15u : 13u);
            text.setFillColor(line == lines.front()
                ? sf::Color::White : sf::Color(210, 195, 175));
            text.setPosition(padding, y);
            m_window.draw(text);
            y += text.getLocalBounds().height + 6.f;
        }
    }
}
