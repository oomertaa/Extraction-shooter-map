#pragma once
#include <string>
#include <vector>

class LootContainer {
public:
    LootContainer(std::string kind, std::vector<std::string> notableDrops = {});

    const std::string& kind()         const;
    bool               isSafe()       const;
    const std::vector<std::string>& notableDrops() const;

private:
    std::string              m_kind;
    std::vector<std::string> m_notableDrops;
};
