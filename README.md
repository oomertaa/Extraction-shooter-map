# ZeroDam Map Reference

An interactive map viewer for extraction shooter games. Markers for bosses, extractions, and loot containers are loaded from a JSON file and displayed on the map. Clicking a marker shows its details on the left panel. The right panel lets you filter by marker type and loot container kind.

## Design patterns

**Factory** — `src/MarkerFactory.cpp:8`
`MarkerFactory::create()` reads the `type` field from each JSON entry and constructs the correct subclass (`BossMarker`, `ExtractionMarker`, or `LootMarker`). The caller only sees `shared_ptr<MapMarker>`.

**Singleton** — `src/ConfigManager.cpp:8`
`ConfigManager::instance()` provides a single point of access to window dimensions and asset paths loaded from config.

## Build instructions

Requirements: CMake 3.16+, SFML 2.6, C++17 compiler.

```bash
mkdir build && cd build
cmake ..
cmake --build .
./ZeroDamMap
```
