#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

class CalendarException : public runtime_error {
public:
    CalendarException(const string& message) : runtime_error(message) {}
};

class OverlapException : public CalendarException {
public:
    OverlapException(const string& message) : CalendarException(message) {}
};

class InvalidIntervalException : public CalendarException {
public:
    InvalidIntervalException(const string& message) : CalendarException(message) {}
};

class ConfigurationException : public CalendarException {
public:
    ConfigurationException(const string& message) : CalendarException(message) {}
};

#endif