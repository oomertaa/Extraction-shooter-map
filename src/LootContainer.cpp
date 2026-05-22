#include "LootContainer.h"
#include <stdexcept>
#include <unordered_map>

static const std::unordered_map<std::string, ContainerKind> s_fromString = {
    {"Server",             ContainerKind::Server},
    {"CementTruck",        ContainerKind::CementTruck},
    {"Clothing",           ContainerKind::Clothing},
    {"PremiumStorageBox",  ContainerKind::PremiumStorageBox},
    {"ComputerCase",       ContainerKind::ComputerCase},
    {"FlightCase",         ContainerKind::FlightCase},
    {"PremiumSuitcase",    ContainerKind::PremiumSuitcase},
    {"MedKit",             ContainerKind::MedKit},
    {"MedSupplies",        ContainerKind::MedSupplies},
    {"HiddenStash",        ContainerKind::HiddenStash},
    {"StorageBox",         ContainerKind::StorageBox},
    {"TravelBag",          ContainerKind::TravelBag},
    {"BriefCase",          ContainerKind::BriefCase},
    {"GarbageBin",         ContainerKind::GarbageBin},
    {"Drawer",             ContainerKind::Drawer},
    {"CourierCarton",      ContainerKind::CourierCarton},
    {"FieldSupplyBox",     ContainerKind::FieldSupplyBox},
    {"ToolCabinet",        ContainerKind::ToolCabinet},
    {"Safe",               ContainerKind::Safe},
};

static const std::unordered_map<ContainerKind, std::string> s_toString = {
    {ContainerKind::Server,             "Server"},
    {ContainerKind::CementTruck,        "CementTruck"},
    {ContainerKind::Clothing,           "Clothing"},
    {ContainerKind::PremiumStorageBox,  "PremiumStorageBox"},
    {ContainerKind::ComputerCase,       "ComputerCase"},
    {ContainerKind::FlightCase,         "FlightCase"},
    {ContainerKind::PremiumSuitcase,    "PremiumSuitcase"},
    {ContainerKind::MedKit,             "MedKit"},
    {ContainerKind::MedSupplies,        "MedSupplies"},
    {ContainerKind::HiddenStash,        "HiddenStash"},
    {ContainerKind::StorageBox,         "StorageBox"},
    {ContainerKind::TravelBag,          "TravelBag"},
    {ContainerKind::BriefCase,          "BriefCase"},
    {ContainerKind::GarbageBin,         "GarbageBin"},
    {ContainerKind::Drawer,             "Drawer"},
    {ContainerKind::CourierCarton,      "CourierCarton"},
    {ContainerKind::FieldSupplyBox,     "FieldSupplyBox"},
    {ContainerKind::ToolCabinet,        "ToolCabinet"},
    {ContainerKind::Safe,               "Safe"},
};

ContainerKind containerKindFromString(const std::string& s)
{
    auto it = s_fromString.find(s);
    if (it == s_fromString.end())
        throw std::invalid_argument("Unknown container kind: " + s);
    return it->second;
}

std::string containerKindToString(ContainerKind k)
{
    return s_toString.at(k);
}

LootContainer::LootContainer(ContainerKind kind, std::vector<std::string> notableDrops)
    : m_kind(kind), m_notableDrops(std::move(notableDrops))
{}

ContainerKind LootContainer::kind()   const { return m_kind; }
bool          LootContainer::isSafe() const { return m_kind == ContainerKind::Safe; }
const std::vector<std::string>& LootContainer::notableDrops() const { return m_notableDrops; }
