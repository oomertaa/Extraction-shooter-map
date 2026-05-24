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

inline const std::vector<ContainerKind>& allContainerKinds()
{
    static const std::vector<ContainerKind> kinds = {
        ContainerKind::Server,           ContainerKind::CementTruck,
        ContainerKind::Clothing,         ContainerKind::PremiumStorageBox,
        ContainerKind::ComputerCase,     ContainerKind::FlightCase,
        ContainerKind::PremiumSuitcase,  ContainerKind::MedKit,
        ContainerKind::MedSupplies,      ContainerKind::HiddenStash,
        ContainerKind::StorageBox,       ContainerKind::TravelBag,
        ContainerKind::BriefCase,        ContainerKind::GarbageBin,
        ContainerKind::Drawer,           ContainerKind::CourierCarton,
        ContainerKind::FieldSupplyBox,   ContainerKind::ToolCabinet,
        ContainerKind::Safe,
    };
    return kinds;
}

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
