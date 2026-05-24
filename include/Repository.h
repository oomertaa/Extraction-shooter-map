#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include "AppExceptions.h"

template<typename T>
class Repository {
public:
    using Factory = std::function<std::shared_ptr<T>(const nlohmann::json&)>;

    void load(const std::string& path, Factory factory)
    {
        std::ifstream file(path);
        if (!file.is_open())
            throw MapLoadException(path);
        nlohmann::json arr = nlohmann::json::parse(file);
        m_items.clear();
        for (const auto& entry : arr)
            m_items.push_back(factory(entry));
    }

    void add(std::shared_ptr<T> item) { m_items.push_back(std::move(item)); }

    const std::vector<std::shared_ptr<T>>& all() const { return m_items; }
    std::size_t size() const { return m_items.size(); }

private:
    std::vector<std::shared_ptr<T>> m_items;
};
