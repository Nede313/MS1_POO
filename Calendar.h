#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include "Activity.h"
#include "Transport.h"

using namespace std;

class Calendar {
private:
    vector<shared_ptr<Activity>> activities;
    vector<Transport> transports;

    double ora_culcare;
    double ora_trezire;

    bool isOverlapping(const shared_ptr<Activity>& a, const shared_ptr<Activity>& b) const;
    bool isOverlapping(const Transport& t1, const Transport& t2) const;
    bool isOverlapping(const shared_ptr<Activity>& a, const Transport& t) const;

    void swap(Calendar& other) noexcept;

public:
    Calendar();
    ~Calendar() = default;

    Calendar(const Calendar& other);
    Calendar& operator=(Calendar other);

    void setSleepTime(double culcare, double trezire);

    void addActivity(shared_ptr<Activity> newActivity);
    void addTransport(const Transport& newTransport);

    void displayByPriority() const;
    double calculateTotalTravelCost() const;

    double calculateTotalDailyRevenue() const;

    void checkSleep(const string& day_name) const;

    void displayProgram() const;
};

#endif