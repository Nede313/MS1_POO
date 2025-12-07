#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

class CalendarException : public std::runtime_error {
public:
    explicit CalendarException(const std::string& message)
        : std::runtime_error(message) {}
};

class OverlapException : public CalendarException {
public:
    explicit OverlapException(const std::string& message)
        : CalendarException(message) {}
};

class InvalidIntervalException : public CalendarException {
public:
    explicit InvalidIntervalException(const std::string& message)
        : CalendarException(message) {}
};

class ConfigurationException : public CalendarException {
public:
    explicit ConfigurationException(const std::string& message)
        : CalendarException(message) {}
};

#endif