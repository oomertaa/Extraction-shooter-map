#include "MapMarker.h"

MapMarker::MapMarker(sf::Vector2f position)
    : m_position(position)
{}

sf::Vector2f MapMarker::position() const { return m_position; }
bool         MapMarker::visible()  const { return m_visible; }
void         MapMarker::setVisible(bool v) { m_visible = v; }
