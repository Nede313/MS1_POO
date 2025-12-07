#include "Transport.h"
#include <iomanip>
#include <sstream>

using namespace std;

static long next_transport_id = 1;

static string formatTime(double time) {
    int hours = static_cast<int>(time);
    int minutes = static_cast<int>((time - hours) * 60.0);

    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":"
       << setfill('0') << setw(2) << minutes;
    return ss.str();
}

Transport::Transport(TransportType type, double start_hour, double end_hour,
                     const string& start_station, const string& end_station, double cost)
    : type(type), start_hour(start_hour), end_hour(end_hour),
      start_station(start_station), end_station(end_station), cost(cost), id(next_transport_id++) {
}

void Transport::show(ostream& out) const {
    string typeStr;

    switch (type) {
        case BUS: typeStr = "BUS"; break;
        case METRO: typeStr = "METRO"; break;
        case CAR: typeStr = "CAR"; break;
        case MIXT: typeStr = "MIXT"; break;
        default: typeStr = "NECUNOSCUT"; break;
    }

    string start_time_str = formatTime(start_hour);
    string end_time_str = formatTime(end_hour);

    out << "[TID:" << id << "] Transport " << typeStr << " (" << start_time_str << " - " << end_time_str
        << ", De la: " << start_station << ", La: " << end_station << ")";

    if (cost > 0) {
        out << ", Cost: " << fixed << setprecision(2) << cost << " RON";
    }
}

ostream& operator<<(ostream& out, const Transport& t) {
    t.show(out);
    return out;
}