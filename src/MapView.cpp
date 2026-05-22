#include "MapView.h"
#include <algorithm>
#include <cmath>

MapView::MapView(sf::Vector2u texSize, unsigned winW, unsigned winH,
                 unsigned leftPanel, unsigned rightPanel)
    : m_texSize(texSize)
{
    m_viewLeft   = static_cast<float>(leftPanel);
    m_viewRight  = static_cast<float>(winW - rightPanel);
    m_viewTop    = 0.f;
    m_viewBottom = static_cast<float>(winH);

    float viewW = m_viewRight - m_viewLeft;
    float viewH = m_viewBottom - m_viewTop;

    m_scale  = std::min(viewW / static_cast<float>(texSize.x),
                        viewH / static_cast<float>(texSize.y));
    m_offset = {
        m_viewLeft + (viewW - texSize.x * m_scale) / 2.f,
        m_viewTop  + (viewH - texSize.y * m_scale) / 2.f
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
    clampOffset();
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

void MapView::onMouseWheelScrolled(sf::Vector2f mousePos, float delta)
{
    float factor = (delta > 0.f) ? ZOOM_STEP : (1.f / ZOOM_STEP);
    float newScale = std::clamp(m_scale * factor, MIN_SCALE, MAX_SCALE);
    float applied  = newScale / m_scale;
    m_offset = mousePos + (m_offset - mousePos) * applied;
    m_scale  = newScale;
    clampOffset();
}

void MapView::clampOffset()
{
    float mapW = m_texSize.x * m_scale;
    float mapH = m_texSize.y * m_scale;
    float viewW = m_viewRight - m_viewLeft;
    float viewH = m_viewBottom - m_viewTop;

    if (mapW <= viewW)
        m_offset.x = m_viewLeft + (viewW - mapW) / 2.f;
    else
        m_offset.x = std::clamp(m_offset.x, m_viewRight - mapW, m_viewLeft);

    if (mapH <= viewH)
        m_offset.y = m_viewTop + (viewH - mapH) / 2.f;
    else
        m_offset.y = std::clamp(m_offset.y, m_viewBottom - mapH, m_viewTop);
}
