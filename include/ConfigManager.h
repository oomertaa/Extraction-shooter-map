#pragma once
#include <string>

class ConfigManager {
public:
    static ConfigManager& instance();

    ConfigManager(const ConfigManager&)            = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    ConfigManager(ConfigManager&&)                 = delete;
    ConfigManager& operator=(ConfigManager&&)      = delete;

    unsigned windowWidth()  const;
    unsigned windowHeight() const;
    const std::string& mapPath() const;

private:
    ConfigManager();

    unsigned    m_windowWidth{1600};
    unsigned    m_windowHeight{900};
    std::string m_mapPath;
};
