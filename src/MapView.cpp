#include "MapView.h"
#include <algorithm>
#include <cmath>

MapView::MapView(sf::Vector2u texSize, unsigned winW, unsigned winH)
{
    m_scale  = std::min(static_cast<float>(winW) / static_cast<float>(texSize.x),
                        static_cast<float>(winH) / static_cast<float>(texSize.y));
    m_offset = {
        (static_cast<float>(winW) - texSize.x * m_scale) / 2.f,
        (static_cast<float>(winH) - texSize.y * m_scale) / 2.f
    };
}

sf::Vector2f MapView::mapToScreen(sf::Vector2f mapPos) const
{
    return { mapPos.x * m_scale + m_offset.x,
             mapPos.y * m_scale + m_offset.y };
}

sf::Vector2f MapView::screenToMap(sf::Vector2f screenPos) const
{
    return { (screenPos.x - m_offset.x) / m_scale,
             (screenPos.y - m_offset.y) / m_scale };
}

void MapView::applyToSprite(sf::Sprite& sprite) const
{
    sprite.setScale(m_scale, m_scale);
    sprite.setPosition(m_offset);
}

void MapView::onMousePressed(sf::Vector2f screenPos)
{
    m_dragging         = true;
    m_wasDrag          = false;
    m_dragAnchorMouse  = screenPos;
    m_dragAnchorOffset = m_offset;
}

void MapView::onMouseMoved(sf::Vector2f screenPos)
{
    if (!m_dragging) return;
    sf::Vector2f delta = screenPos - m_dragAnchorMouse;
    m_offset = m_dragAnchorOffset + delta;
    if (!m_wasDrag) {
        float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        if (dist > CLICK_THRESHOLD)
            m_wasDrag = true;
    }
}

void MapView::onMouseReleased(sf::Vector2f /*screenPos*/)
{
    m_dragging = false;
}

bool MapView::wasDragOnRelease() const
{
    return m_wasDrag;
}
