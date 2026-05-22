#include "LootContainer.h"

LootContainer::LootContainer(std::string kind, std::vector<std::string> notableDrops)
    : m_kind(std::move(kind)), m_notableDrops(std::move(notableDrops))
{}

const std::string& LootContainer::kind() const { return m_kind; }
bool               LootContainer::isSafe() const { return m_kind == "Safe"; }
const std::vector<std::string>& LootContainer::notableDrops() const { return m_notableDrops; }
