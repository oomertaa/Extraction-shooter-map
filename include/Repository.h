#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <fstream>
#include <stdexcept>
#include "nlohmann/json.hpp"

template<typename T>
class Repository {
public:
    using Factory = std::function<std::unique_ptr<T>(const nlohmann::json&)>;

    void load(const std::string& path, Factory factory)
    {
        std::ifstream file(path);
        if (!file.is_open())
            throw std::runtime_error("Cannot open: " + path);
        nlohmann::json arr = nlohmann::json::parse(file);
        m_items.clear();
        for (const auto& entry : arr)
            m_items.push_back(factory(entry));
    }

    const std::vector<std::unique_ptr<T>>& all() const { return m_items; }
    std::size_t size() const { return m_items.size(); }

private:
    std::vector<std::unique_ptr<T>> m_items;
};
