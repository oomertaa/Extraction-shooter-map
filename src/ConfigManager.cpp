#include "ConfigManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

ConfigManager& ConfigManager::instance()
{
    static ConfigManager inst;
    return inst;
}

ConfigManager::ConfigManager()
{
    std::ifstream f("data/config.json");
    if (!f) throw std::runtime_error("Cannot open data/config.json");
    json j = json::parse(f);
    m_windowWidth  = j["window"]["width"];
    m_windowHeight = j["window"]["height"];
    m_mapPath      = j["mapPath"];
}

unsigned ConfigManager::windowWidth()  const { return m_windowWidth; }
unsigned ConfigManager::windowHeight() const { return m_windowHeight; }
const std::string& ConfigManager::mapPath()   const { return m_mapPath; }
