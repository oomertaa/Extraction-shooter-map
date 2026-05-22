#pragma once
#include <memory>
#include "MapMarker.h"
#include "nlohmann/json.hpp"

class MarkerFactory {
public:
    static std::unique_ptr<MapMarker> create(const nlohmann::json& entry);

    MarkerFactory()                              = delete;
    MarkerFactory(const MarkerFactory&)          = delete;
    MarkerFactory& operator=(const MarkerFactory&) = delete;
};
