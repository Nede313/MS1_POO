#include "Activity.h"
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

long Activity::next_id = 1;
int Activity::activity_count = 0;

static string formatTime(double time) {
    int hours = static_cast<int>(time);
    int minutes = static_cast<int>((time - hours) * 60.0);

    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":"
       << setfill('0') << setw(2) << minutes;
    return ss.str();
}

Activity::Activity(const string& name, const string& description, double start_hour, double end_hour)
    : name(name), description(description), start_hour(start_hour), end_hour(end_hour), id(next_id++) {
    activity_count++;
}

Activity::~Activity() {
    activity_count--;
}

void Activity::show(ostream& out) const {
    string start_time_str = formatTime(start_hour);
    string end_time_str = formatTime(end_hour);

    out << "[" << next_id - id << "] " << name << " (" << start_time_str << " - " << end_time_str
        << ", Durata: " << calculateDuration() << "h)";
    displayDetails(out);
}

TimpLiber::TimpLiber(const string& name, const string& desc, double sh, double eh, int level)
    : Activity(name, desc, sh, eh), relaxing_level(level) {}

shared_ptr<Activity> TimpLiber::clone() const {
    return make_shared<TimpLiber>(*this);
}

double TimpLiber::calculatePriorityScore() const {
    return calculateDuration() * relaxing_level;
}

void TimpLiber::displayDetails(ostream& out) const {
    out << " | Tip: Timp Liber, Relaxare: " << relaxing_level << "/10";
}

Intalnire::Intalnire(const string& name, const string& desc, double sh, double eh, const string& loc, int req)
    : Activity(name, desc, sh, eh), location(loc), required_participants(req) {}

shared_ptr<Activity> Intalnire::clone() const {
    return make_shared<Intalnire>(*this);
}

double Intalnire::calculatePriorityScore() const {
    return calculateDuration() * pow(required_participants, 1.5);
}

void Intalnire::displayDetails(ostream& out) const {
    out << " | Tip: Intalnire, Locatie: " << location << ", Participanti: " << required_participants;
}

Deplasare::Deplasare(const string& name, const string& desc, double sh, double eh, const string& mode, double cost)
    : Activity(name, desc, sh, eh), transport_mode(mode), cost(cost) {}

shared_ptr<Activity> Deplasare::clone() const {
    return make_shared<Deplasare>(*this);
}

double Deplasare::calculatePriorityScore() const {
    return (cost > 0) ? calculateDuration() / cost : 0.0;
}

void Deplasare::displayDetails(ostream& out) const {
    out << " | Tip: Deplasare, Mod: " << transport_mode << ", Cost: " << cost << " RON";
}

ServiciuPlatit::ServiciuPlatit(const string& name, const string& desc, double sh, double eh, double venit, const string& client)
    : Activity(name, desc, sh, eh), venit_fix_sedinta(venit), client_name(client) {}

shared_ptr<Activity> ServiciuPlatit::clone() const {
    return make_shared<ServiciuPlatit>(*this);
}

double ServiciuPlatit::calculatePriorityScore() const {
    return venit_fix_sedinta * 5.0;
}

void ServiciuPlatit::displayDetails(ostream& out) const {
    out << " | Tip: Antrenament, Client: " << client_name
        << ", Venit Fix Sedinta: " << venit_fix_sedinta << " RON";
}