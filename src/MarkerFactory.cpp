#include "MarkerFactory.h"
#include "LootMarker.h"
#include "ExtractionMarker.h"
#include "BossMarker.h"
#include "LootContainer.h"
#include <stdexcept>

std::unique_ptr<MapMarker> MarkerFactory::create(const nlohmann::json& j)
{
    const std::string type = j.at("type").get<std::string>();
    const float x = j.at("x").get<float>();
    const float y = j.at("y").get<float>();

    if (type == "loot") {
        ContainerKind kind = containerKindFromString(j.at("kind").get<std::string>());
        std::vector<std::string> notable;
        if (j.contains("notable"))
            notable = j["notable"].get<std::vector<std::string>>();
        return std::make_unique<LootMarker>(
            sf::Vector2f{x, y}, LootContainer{kind, std::move(notable)});
    }
    if (type == "extraction") {
        return std::make_unique<ExtractionMarker>(
            sf::Vector2f{x, y}, j.value("description", ""));
    }
    if (type == "boss") {
        return std::make_unique<BossMarker>(
            sf::Vector2f{x, y}, j.value("description", ""));
    }
    throw std::invalid_argument("Unknown marker type: " + type);
}
