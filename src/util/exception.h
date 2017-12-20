#pragma once

#include <exception>
#include <stdexcept>

// Distinguish our exceptions from external code
class NgException : public std::runtime_error {
   public:
    explicit NgException(const std::string& what_arg)
        : std::runtime_error(what_arg) {}
    explicit NgException(const char* what_arg) : std::runtime_error(what_arg) {}
};