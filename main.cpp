#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// ==================== CLASS ACTIVITY ====================
class Activity {
private:
    string Name;
    string Description;
    int start_hour;
    int end_hour;
    long id;

public:
    Activity(string Name, string Description, int start_hour, int end_hour) {
        this->id = rand();
        this->Name = Name;
        this->Description = Description;
        this->start_hour = start_hour;
        this->end_hour = end_hour;
    }

    Activity(const Activity &activity_cp) {
        this->id = activity_cp.id;
        this->Name = activity_cp.Name;
        this->Description = activity_cp.Description;
        this->start_hour = activity_cp.start_hour;
        this->end_hour = activity_cp.end_hour;
    }

    Activity& operator=(const Activity &activity_eq) {
        if (this != &activity_eq) {
            this->id = activity_eq.id;
            this->Name = activity_eq.Name;
            this->Description = activity_eq.Description;
            this->start_hour = activity_eq.start_hour;
            this->end_hour = activity_eq.end_hour;
        }
        return *this;
    }

    ~Activity() {}

    string getName() { return Name; }
    void setName(string Name) { this->Name = Name; }

    string getDescription() { return Description; }
    void setDesc(string Description) { this->Description = Description; }

    int getStartHour() const { return start_hour; }
    void setStartHr(int start_hour) { this->start_hour = start_hour; }

    int getEndHour() const { return end_hour; }
    void setEndHr(int end_hour) { this->end_hour = end_hour; }

    long getId() const { return id; }

    friend ostream& operator<<(ostream& out, const Activity& m) {
        out << "Name: " << m.Name
            << ", Description: " << m.Description
            << ", Start Hour: " << m.start_hour
            << ", End Hour: " << m.end_hour;
        return out;
    }
};

// ==================== CLASS TRANSPORT ====================
class Transport {
public:
    enum Transport_Type { BUS, METRO, CAR };

private:
    Transport_Type type;
    int start_hour;
    int end_hour;
    string start_station;
    string end_station;
    long id;

public:
    Transport(Transport_Type type, int start_hour, int end_hour, const string& start_station, string end_station) {
        this->id = rand();
        this->type = type;
        this->start_hour = start_hour;
        this->end_hour = end_hour;
        this->start_station = start_station;
        this->end_station = end_station;
    }

    Transport(const Transport &transport_cp) {
        this->id = transport_cp.id;
        this->type = transport_cp.type;
        this->start_hour = transport_cp.start_hour;
        this->end_hour = transport_cp.end_hour;
        this->start_station = transport_cp.start_station;
        this->end_station = transport_cp.end_station;
    }

    Transport& operator=(const Transport &transport_eq) {
        if (this != &transport_eq) {
            this->id = transport_eq.id;
            this->type = transport_eq.type;
            this->start_hour = transport_eq.start_hour;
            this->end_hour = transport_eq.end_hour;
            this->start_station = transport_eq.start_station;
            this->end_station = transport_eq.end_station;
        }
        return *this;
    }

    ~Transport() {}

    Transport_Type getType() const { return type; }
    void setType(Transport_Type type) { this->type = type; }

    int getStartHour() const { return start_hour; }
    void setStartHour(int start_hour) { this->start_hour = start_hour; }

    int getEndHour() const { return end_hour; }
    void setEndHour(int end_hour) { this->end_hour = end_hour; }

    string getStartStation() const { return start_station; }
    void setStartStation(const string& start_station) { this->start_station = start_station; }

    string getEndStation() const { return end_station; }
    void setEndStation(string end_station) { this->end_station = end_station; }

    long getId() const { return id; }
};

// ==================== CLASS CALENDAR ====================
class Calendar {
private:
    vector<Activity> activities;
    vector<Transport> transports;

public:
    Calendar() {}

    Calendar(const Calendar& calendar_cp) {
        activities = calendar_cp.activities;
        transports = calendar_cp.transports;
    }

    Calendar& operator=(const Calendar &calendar_eq) {
        if (this != &calendar_eq) {
            activities = calendar_eq.activities;
            transports = calendar_eq.transports;
        }
        return *this;
    }

    bool addActivity(const Activity& activity) {
        if (activity.getStartHour() >= activity.getEndHour() || activity.getEndHour() > 7*24)
            return false;

        for (const auto& act : activities)
            if (act.getStartHour() < activity.getEndHour() && activity.getStartHour() < act.getEndHour())
                return false;

        for (const auto& tr : transports)
            if (tr.getStartHour() < activity.getEndHour() && activity.getStartHour() < tr.getEndHour())
                return false;

        activities.push_back(activity);
        sort(activities.begin(), activities.end(), [](const Activity &a, const Activity &b) {
            return a.getStartHour() < b.getStartHour();
        });
        return true;
    }

    bool removeActivity(int id) {
        for (size_t i = 0; i < activities.size(); ++i) {
            if (activities[i].getId() == id) {
                activities.erase(activities.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool addTransport(const Transport &transport) {
        if (transport.getStartHour() >= transport.getEndHour() || transport.getEndHour() > 7*24)
            return false;

        for (const auto& tr : transports)
            if (tr.getStartHour() < transport.getEndHour() && transport.getStartHour() < tr.getEndHour())
                return false;

        for (const auto& act : activities)
            if (act.getStartHour() < transport.getEndHour() && transport.getStartHour() < act.getEndHour())
                return false;

        transports.push_back(transport);
        sort(transports.begin(), transports.end(), [](const Transport &a, const Transport &b) {
            return a.getStartHour() < b.getStartHour();
        });
        return true;
    }

    bool removeTransport(int id) {
        for (size_t i = 0; i < transports.size(); ++i) {
            if (transports[i].getId() == id) {
                transports.erase(transports.begin() + i);
                return true;
            }
        }
        return false;
    }

    void checkSleep() {
        vector<pair<int,int>> intervals;
        for (const auto& a : activities)
            intervals.push_back({a.getStartHour(), a.getEndHour()});
        for (const auto& t : transports)
            intervals.push_back({t.getStartHour(), t.getEndHour()});

        sort(intervals.begin(), intervals.end());

        vector<pair<int,int>> intervalsToCheck;
        for(int i = 0; i < 6; i++)
            intervalsToCheck.push_back({22 + i*24, 22 + i*24 + 12});

        vector<bool> sleepHoursCheck(6, true);

        for (size_t i = 0; i < intervalsToCheck.size(); ++i) {
            for (size_t j = 0; j < intervals.size(); ++j) {
                if (intervalsToCheck[i].first < intervals[j].second && intervals[j].second < intervalsToCheck[i].second) {
                    if (j < intervals.size() - 1 && intervalsToCheck[i].first < intervals[j+1].first && intervals[j+1].first < intervalsToCheck[i].second) {
                        if (intervals[j+1].first - intervals[j].second < 9)
                            sleepHoursCheck[i] = false;
                        else {
                            sleepHoursCheck[i] = true;
                            break;
                        }
                    } else {
                        if (intervals[j].second < intervalsToCheck[i].second && intervals[j].second > intervalsToCheck[i].second-9) {
                            sleepHoursCheck[i] = false;
                            break;
                        }
                    }
                } else if (intervalsToCheck[i].first < intervals[j].first && intervals[j].first < intervalsToCheck[i].second) {
                    if (intervals[j].first < intervalsToCheck[i].second-3) {
                        sleepHoursCheck[i] = false;
                        break;
                    }
                }
            }
        }

        for (bool b : sleepHoursCheck)
            cout << b << " ";
        cout << endl;
    }
};

// ==================== MAIN ====================
int main() {
    srand(time(NULL));

    const Transport T1 = Transport(Transport::BUS, 12, 15, "Pacii", "Unirii");
    const Transport T2 = Transport(Transport::BUS, 11, 12, "Pacii", "Unirii");

    Calendar C1;
    bool ret = C1.addTransport(T1);
    cout << ret << endl;
    ret = C1.addTransport(T2);
    cout << ret << endl;

    ret = C1.removeTransport(T2.getId());
    cout << ret << endl;
    ret = C1.removeTransport(T2.getId());
    cout << ret << endl;

    cout << endl;

    const Activity A1 = Activity("antrenament", "am antrenament cu alex", 18, 20);
    const Activity A2 = Activity("antrenament", "am antrenament cu cosmin", 15, 17);

    bool ret2 = C1.addActivity(A1);
    cout << ret2 << endl;
    ret2 = C1.addActivity(A2);
    cout << ret2 << endl;

    ret2 = C1.removeActivity(A2.getId());
    cout << ret2 << endl;
    ret2 = C1.removeActivity(A2.getId());
    cout << ret2 << endl;

    cout << endl;

    C1.checkSleep();

    return 0;
}
