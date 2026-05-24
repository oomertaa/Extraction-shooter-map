#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "LootContainer.h"
#include "Repository.h"

class FilterPanel {
public:
    FilterPanel(float x, float y, float width, float height, const sf::Font& font);

    void addLootContainer(std::shared_ptr<LootContainer> lc);
    void handleClick(sf::Vector2f screenPos);
    bool isTypeVisible(const char* type) const;
    bool isKindVisible(ContainerKind kind) const;
    bool contains(sf::Vector2f screenPos) const;
    void draw(sf::RenderWindow& window) const;

private:
    struct TypeToggle {
        std::string   label;
        std::string   typeKey;
        bool          on{true};
        sf::FloatRect hitbox;
    };

    struct KindToggle {
        ContainerKind kind;
        bool          on{true};
        sf::FloatRect hitbox;
    };

    void rebuildLayout();
    void drawCheckbox(sf::RenderWindow& window, sf::Vector2f pos, bool checked) const;
    void drawTypeSection(sf::RenderWindow& window) const;
    void drawKindSection(sf::RenderWindow& window) const;

    Repository<LootContainer>  m_lootRepo;
    std::vector<TypeToggle>    m_typeToggles;
    std::vector<KindToggle>    m_kindToggles;

    sf::RectangleShape m_background;
    const sf::Font&    m_font;
    float              m_x, m_y, m_width;

    static constexpr float PADDING    = 12.f;
    static constexpr float ROW_H      = 22.f;
    static constexpr float BOX_SIZE   = 12.f;
    static constexpr float SEC_H      = 18.f;
    static constexpr float SEP_H      = 10.f;
    static constexpr float HEADER_GAP = 18.f;
};
