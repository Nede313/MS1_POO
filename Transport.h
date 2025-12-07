#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <string>

using namespace std;

enum TransportType { BUS, METRO, CAR, MIXT };

class Transport {
private:
    TransportType type;
    double start_hour;
    double end_hour;
    string start_station;
    string end_station;
    double cost;
    long id;

public:
    Transport(TransportType type, double start_hour, double end_hour,
              const string& start_station, const string& end_station,
              double cost = 0.0);

    Transport(const Transport &transport_cp) = default;
    Transport& operator=(const Transport &transport_eq) = default;
    ~Transport() = default;

    double getStartHour() const { return start_hour; }
    double getEndHour() const { return end_hour; }
    double getCost() const { return cost; }

    void show(ostream& out) const;

    friend ostream& operator<<(ostream& out, const Transport& t);
};

#endif