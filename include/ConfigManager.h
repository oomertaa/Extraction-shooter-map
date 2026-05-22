#pragma once
#include <string>

class ConfigManager {
public:
    static ConfigManager& instance();

    ConfigManager(const ConfigManager&)            = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    ConfigManager(ConfigManager&&)                 = delete;
    ConfigManager& operator=(ConfigManager&&)      = delete;

    unsigned windowWidth()      const;
    unsigned windowHeight()     const;
    unsigned leftPanelWidth()   const;
    unsigned rightPanelWidth()  const;
    const std::string& mapPath() const;

private:
    ConfigManager();

    unsigned    m_windowWidth{1600};
    unsigned    m_windowHeight{900};
    unsigned    m_leftPanelWidth{251};
    unsigned    m_rightPanelWidth{251};
    std::string m_mapPath;
};
