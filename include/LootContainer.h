#pragma once
#include <string>
#include <vector>

enum class ContainerKind {
    Server, CementTruck, Clothing, PremiumStorageBox,
    ComputerCase, FlightCase, PremiumSuitcase, MedKit,
    MedSupplies, HiddenStash, StorageBox, TravelBag,
    BriefCase, GarbageBin, Drawer, CourierCarton,
    FieldSupplyBox, ToolCabinet, Safe
};

// throws std::invalid_argument if the string is not a known kind
ContainerKind containerKindFromString(const std::string& s);
std::string   containerKindToString(ContainerKind k);

class LootContainer {
public:
    LootContainer(ContainerKind kind, std::vector<std::string> notableDrops = {});

    ContainerKind kind()   const;
    bool          isSafe() const;
    const std::vector<std::string>& notableDrops() const;

private:
    ContainerKind            m_kind;
    std::vector<std::string> m_notableDrops;
};
