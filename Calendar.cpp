#include "Calendar.h"
#include "Exceptions.h"
#include "Transport.h"
#include "Activity.h"
#include <algorithm>
#include <utility>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

static string formatTime(double time) {
    int hours = static_cast<int>(time);
    int minutes = static_cast<int>((time - hours) * 60.0);

    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":"
       << setfill('0') << setw(2) << minutes;
    return ss.str();
}

Calendar::Calendar() : ora_culcare(0.0), ora_trezire(0.0) {}

void Calendar::swap(Calendar& other) noexcept {
    using std::swap;
    swap(activities, other.activities);
    swap(transports, other.transports);
    swap(ora_culcare, other.ora_culcare);
    swap(ora_trezire, other.ora_trezire);
}

Calendar::Calendar(const Calendar& other)
    : ora_culcare(other.ora_culcare), ora_trezire(other.ora_trezire) {
    for (const auto& act_ptr : other.activities) {
        if (act_ptr) {
            activities.push_back(act_ptr->clone());
        }
    }
    transports = other.transports;
}

Calendar& Calendar::operator=(Calendar other) {
    swap(other);
    return *this;
}

void Calendar::setSleepTime(double culcare, double trezire) {
    if (culcare < 0 || culcare > 24 || trezire < 0 || trezire > 24) {
        throw InvalidIntervalException("Ora de culcare/trezire trebuie sa fie intre 0 si 24.");
    }
    ora_culcare = culcare;
    ora_trezire = trezire;
}

bool Calendar::isOverlapping(const shared_ptr<Activity>& a, const shared_ptr<Activity>& b) const {
    if (!a || !b) return false;
    return a->getStartHour() < b->getEndHour() && b->getStartHour() < a->getEndHour();
}

bool Calendar::isOverlapping(const Transport& t1, const Transport& t2) const {
    return t1.getStartHour() < t2.getEndHour() && t2.getStartHour() < t1.getEndHour();
}

bool Calendar::isOverlapping(const shared_ptr<Activity>& a, const Transport& t) const {
    if (!a) return false;
    return a->getStartHour() < t.getEndHour() && t.getStartHour() < a->getEndHour();
}

void Calendar::addActivity(shared_ptr<Activity> newActivity) {
    if (newActivity->getStartHour() >= newActivity->getEndHour()) {
        throw InvalidIntervalException("Ora de inceput trebuie sa fie inainte de ora de sfarsit.");
    }

    for (const auto& existingAct : activities) {
        if (isOverlapping(existingAct, newActivity)) {
            throw OverlapException("Activitatea se suprapune cu o activitate existenta.");
        }
    }

    for (const auto& existingTrans : transports) {
        if (isOverlapping(newActivity, existingTrans)) {
            throw OverlapException("Activitatea se suprapune cu un transport existent.");
        }
    }

    activities.push_back(newActivity);

    sort(activities.begin(), activities.end(), [](const shared_ptr<Activity>& a, const shared_ptr<Activity>& b) {
        return a->getStartHour() < b->getStartHour();
    });
}

void Calendar::addTransport(const Transport& newTransport) {
    if (newTransport.getStartHour() >= newTransport.getEndHour()) {
        throw InvalidIntervalException("Ora de inceput a transportului trebuie sa fie inainte de ora de sfarsit.");
    }

    for (const auto& existingTrans : transports) {
        if (isOverlapping(existingTrans, newTransport)) {
            throw OverlapException("Transportul se suprapune cu un alt transport existent.");
        }
    }

    for (const auto& existingAct : activities) {
        if (isOverlapping(existingAct, newTransport)) {
            throw OverlapException("Transportul se suprapune cu o activitate existenta.");
        }
    }

    transports.push_back(newTransport);

    sort(transports.begin(), transports.end(), [](const Transport& a, const Transport& b) {
        return a.getStartHour() < b.getStartHour();
    });
}

double Calendar::calculateTotalDailyRevenue() const {
    double totalRevenue = 0.0;
    for (const auto& act_ptr : activities) {
        if (auto serviciu_ptr = dynamic_pointer_cast<ServiciuPlatit>(act_ptr)) {
            totalRevenue += serviciu_ptr->calculateRevenue();
        }
    }
    return totalRevenue;
}

double Calendar::calculateTotalTravelCost() const {
    double totalCost = 0.0;

    for (const auto& act_ptr : activities) {
        if (auto deplasare_ptr = dynamic_pointer_cast<Deplasare>(act_ptr)) {
            totalCost += deplasare_ptr->getCost();
        }
    }

    for (const auto& t : transports) {
        totalCost += t.getCost();
    }

    return totalCost;
}

void Calendar::displayProgram() const {
    cout << "\n--- PROGRAMUL ZILEI (Sortat cronologic) ---\n";

    auto it_act = activities.begin();
    auto end_act = activities.end();
    auto it_trans = transports.begin();
    auto end_trans = transports.end();

    while (it_act != end_act || it_trans != end_trans) {
        bool print_activity = false;

        if (it_act == end_act) {
            print_activity = false;
        } else if (it_trans == end_trans) {
            print_activity = true;
        } else {
            print_activity = (*it_act)->getStartHour() <= it_trans->getStartHour();
        }

        if (print_activity) {
            cout << **it_act << "\n";
            ++it_act;
        } else if (it_trans != end_trans) {
            cout << *it_trans << "\n";
            ++it_trans;
        }
    }
}



void Calendar::displayByPriority() const {
    cout << "\n--- ACTIVITATI SORTATE DUPA SCOR DE PRIORITATE ---\n";

    vector<shared_ptr<Activity>> sortedActivities = activities;

    // Sortare bazata pe metoda virtuala calculatePriorityScore() (Polimorfism)
    sort(sortedActivities.begin(), sortedActivities.end(), [](const shared_ptr<Activity>& a, const shared_ptr<Activity>& b) {
        return a->calculatePriorityScore() > b->calculatePriorityScore();
    });

    for (const auto& act : sortedActivities) {
        cout << *act << " (Scor: " << act->calculatePriorityScore() << ")" << "\n";
    }
}

void Calendar::checkSleep(const string& day_name) const {
    if (ora_culcare == 0.0 && ora_trezire == 0.0) {
        cout << "\n\n!AVERTISMENT! Orele de culcare si trezire nu au fost setate pentru " << day_name << ". Verificarea preciza a somnului este sarita." << endl;
        return;
    }

    double sleep_duration;

    if (ora_culcare <= ora_trezire) {
        sleep_duration = ora_trezire - ora_culcare;
    } else {
        sleep_duration = (24.0 - ora_culcare) + ora_trezire;
    }

    bool is_overlapping = false;

    auto check_segment = [&](double start, double end) {
        for (const auto& act_ptr : activities) {
            if (act_ptr->getStartHour() < end && start < act_ptr->getEndHour()) {
                return true;
            }
        }
        for (const auto& t : transports) {
            if (t.getStartHour() < end && start < t.getEndHour()) {
                return true;
            }
        }
        return false;
    };

    if (ora_culcare <= ora_trezire) {
        if (check_segment(ora_culcare, ora_trezire)) {
            is_overlapping = true;
        }
    } else {

        if (check_segment(ora_culcare, 24.0)) {
            is_overlapping = true;
        }

        if (!is_overlapping && check_segment(0.0, ora_trezire)) {
            is_overlapping = true;
        }
    }

    if (is_overlapping) {
        cout << fixed << setprecision(2);
        cout << "\n\n EROARE CRITICA SOMN (" << day_name << "): Somnul (" << formatTime(ora_culcare) << " - " << formatTime(ora_trezire)
             << ") SE SUPRAPUNE cu o activitate programata! Ajustati orarul de somn." << endl;
        return;
    }

    double required_min = 6.0;
    double required_max = 8.0;

    cout << fixed << setprecision(1);

    if (sleep_duration < required_min) {
        cout << "\n\n⚠️ AVERTISMENT SOMN (" << day_name << "): Vei dormi doar " << sleep_duration
             << " ore (" << formatTime(ora_culcare) << " - " << formatTime(ora_trezire) << "). Ideal este peste " << required_min << " ore!" << endl;
    } else if (sleep_duration > required_max) {
        cout << "\n⚠️ AVERTISMENT SOMN (" << day_name << "): Durata somnului este mai mare decat cea optima ("
             << sleep_duration << " ore). Ajustati orarul." << endl;
    } else {
        cout << "\n✅ VERIFICARE SOMN (" << day_name << "): Durata somnului este OPTIMA ("
             << sleep_duration << " ore)." << endl;
    }
}