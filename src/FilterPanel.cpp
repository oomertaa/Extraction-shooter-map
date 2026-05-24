#include "FilterPanel.h"

FilterPanel::FilterPanel(float x, float y, float width, float height, const sf::Font& font)
    : m_font(font), m_x(x), m_y(y), m_width(width)
{
    m_background.setPosition(x, y);
    m_background.setSize({width, height});
    m_background.setFillColor(sf::Color(72, 40, 15));

    m_typeToggles = {
        {"Boss",       "boss",       true, {}},
        {"Extraction", "extraction", true, {}},
        {"Loot",       "loot",       true, {}},
    };

    for (ContainerKind k : allContainerKinds())
        m_kindToggles.push_back({k, true, {}});

    rebuildLayout();
}

void FilterPanel::rebuildLayout()
{
    float y = m_y + PADDING + SEC_H + HEADER_GAP + SEC_H + SEP_H;
    for (auto& t : m_typeToggles) {
        t.hitbox = {m_x, y, m_width, ROW_H};
        y += ROW_H;
    }

    y += SEP_H + SEC_H + SEP_H;
    for (auto& k : m_kindToggles) {
        k.hitbox = {m_x, y, m_width, ROW_H};
        y += ROW_H;
    }
}

void FilterPanel::addLootContainer(std::shared_ptr<LootContainer> lc)
{
    m_lootRepo.add(std::move(lc));
}

void FilterPanel::handleClick(sf::Vector2f pos)
{
    for (auto& t : m_typeToggles)
        if (t.hitbox.contains(pos)) { t.on = !t.on; return; }
    for (auto& k : m_kindToggles)
        if (k.hitbox.contains(pos)) { k.on = !k.on; return; }
}

bool FilterPanel::isTypeVisible(const char* type) const
{
    for (const auto& t : m_typeToggles)
        if (t.typeKey == type) return t.on;
    return true;
}

bool FilterPanel::isKindVisible(ContainerKind kind) const
{
    for (const auto& k : m_kindToggles)
        if (k.kind == kind) return k.on;
    return true;
}

bool FilterPanel::contains(sf::Vector2f pos) const
{
    return m_background.getGlobalBounds().contains(pos);
}

void FilterPanel::drawCheckbox(sf::RenderWindow& window, sf::Vector2f pos, bool checked) const
{
    sf::RectangleShape box({BOX_SIZE, BOX_SIZE});
    box.setPosition(pos);
    box.setOutlineColor(sf::Color(210, 195, 175));
    box.setOutlineThickness(1.5f);
    box.setFillColor(checked ? sf::Color(210, 195, 175) : sf::Color::Transparent);
    window.draw(box);
}

void FilterPanel::drawTypeSection(sf::RenderWindow& window) const
{
    std::size_t activeTypes = 0;
    for (const auto& t : m_typeToggles) if (t.on) ++activeTypes;

    sf::Text sec;
    sec.setFont(m_font);
    sec.setCharacterSize(12u);
    sec.setFillColor(sf::Color(160, 140, 110));
    sec.setString("MARKER TYPES  " + std::to_string(activeTypes) + " / " + std::to_string(m_typeToggles.size()));
    sec.setPosition(m_x + PADDING, m_typeToggles[0].hitbox.top - SEC_H);
    window.draw(sec);

    for (const auto& t : m_typeToggles) {
        float bx = m_x + PADDING;
        float by = t.hitbox.top + (ROW_H - BOX_SIZE) / 2.f;
        drawCheckbox(window, {bx, by}, t.on);

        sf::Text label;
        label.setFont(m_font);
        label.setString(t.label);
        label.setCharacterSize(14u);
        label.setFillColor(t.on ? sf::Color::White : sf::Color(130, 110, 85));
        label.setPosition(bx + BOX_SIZE + 7.f, t.hitbox.top + (ROW_H - 14.f) / 2.f - 1.f);
        window.draw(label);
    }
}

void FilterPanel::drawKindSection(sf::RenderWindow& window) const
{
    if (m_kindToggles.empty()) return;

    float sepY = m_typeToggles.back().hitbox.top + ROW_H + SEP_H / 2.f;
    sf::RectangleShape sep({m_width - 2.f * PADDING, 1.f});
    sep.setPosition(m_x + PADDING, sepY);
    sep.setFillColor(sf::Color(110, 75, 40));
    window.draw(sep);

    bool lootVisible = isTypeVisible("loot");

    std::size_t activeKinds = 0;
    for (const auto& k : m_kindToggles) if (k.on) ++activeKinds;

    sf::Text sec;
    sec.setFont(m_font);
    sec.setCharacterSize(12u);
    sec.setFillColor(sf::Color(160, 140, 110));
    sec.setString("CONTAINERS  " + std::to_string(activeKinds) + " / " + std::to_string(m_kindToggles.size()));
    sec.setPosition(m_x + PADDING, m_kindToggles[0].hitbox.top - SEC_H);
    window.draw(sec);
    for (const auto& k : m_kindToggles) {
        float bx = m_x + PADDING;
        float by = k.hitbox.top + (ROW_H - BOX_SIZE) / 2.f;
        drawCheckbox(window, {bx, by}, k.on && lootVisible);

        sf::Text label;
        label.setFont(m_font);
        label.setString(containerKindToString(k.kind));
        label.setCharacterSize(13u);
        bool active = k.on && lootVisible;
        label.setFillColor(active ? sf::Color::White : sf::Color(130, 110, 85));
        label.setPosition(bx + BOX_SIZE + 7.f, k.hitbox.top + (ROW_H - 13.f) / 2.f - 1.f);
        window.draw(label);
    }
}

void FilterPanel::draw(sf::RenderWindow& window) const
{
    window.draw(m_background);

    sf::Text header;
    header.setFont(m_font);
    header.setString("FILTERS");
    header.setCharacterSize(15u);
    header.setFillColor(sf::Color(200, 180, 150));
    header.setPosition(m_x + PADDING, m_y + PADDING);
    window.draw(header);

    drawTypeSection(window);
    drawKindSection(window);
}
