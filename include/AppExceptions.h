#pragma once
#include <stdexcept>
#include <string>

class MapLoadException : public std::exception {
public:
    explicit MapLoadException(const std::string& path)
        : m_msg("Failed to load file: " + path) {}

    const char* what() const noexcept override { return m_msg.c_str(); }

private:
    std::string m_msg;
};

class UnknownMarkerTypeException : public std::exception {
public:
    explicit UnknownMarkerTypeException(const std::string& type)
        : m_msg("Unknown marker type: " + type) {}

    const char* what() const noexcept override { return m_msg.c_str(); }

private:
    std::string m_msg;
};
