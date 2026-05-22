#pragma once
#include <functional>
#include <cstddef>
#include <type_traits>
#include "Repository.h"
#include "MapMarker.h"

template<typename T>
const T* findFirst(const Repository<T>& repo, std::function<bool(const T&)> pred)
{
    for (const auto& item : repo.all()) {
        if constexpr (std::is_base_of_v<MapMarker, T>)
            if (!item->visible()) continue;
        if (pred(*item))
            return item.get();
    }
    return nullptr;
}

template<typename T>
std::size_t countIf(const Repository<T>& repo, std::function<bool(const T&)> pred)
{
    std::size_t count = 0;
    for (const auto& item : repo.all())
        if (pred(*item)) ++count;
    return count;
}
