#ifndef CALENDARMANAGER_H
#define CALENDARMANAGER_H

#include "Calendar.h"
#include <map>
#include <string>

class CalendarManager {
private:
    std::map<std::string, Calendar> weekly_agenda;
    CalendarManager() = default;

public:
    CalendarManager(const CalendarManager&) = delete;
    void operator=(const CalendarManager&) = delete;

    static CalendarManager& getInstance() {
        static CalendarManager instance;
        return instance;
    }

    std::map<std::string, Calendar>& getAgenda() { return weekly_agenda; }
};
#endif