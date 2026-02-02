#include "Calendar.h"
#include "Transport.h"
#include "Activity.h"
#include "ActivityFactory.h"
#include "CalendarManager.h"
#include "HistoryManager.h"
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <vector>

using namespace std;

double timeToDecimal(int hours, int minutes) {
    return hours + (minutes / 60.0);
}

void runWeeklySchedule() {
    CalendarManager& manager = CalendarManager::getInstance();
    auto& weekly_agenda = manager.getAgenda();
    HistoryLog<shared_ptr<Activity>> activity_log;
    HistoryLog<double> financial_log;

    vector<string> days = {"Luni", "Marti", "Miercuri", "Joi", "Vineri"};

    // --- Luni ---
    Calendar agenda_luni;
    try {
        agenda_luni.setSleepTime(timeToDecimal(23, 30), 7.0);
        agenda_luni.addTransport(Transport(METRO, timeToDecimal(7, 30), 8.0, "Pacii", "Lujerului"));
        auto facultate = ActivityFactory::create(ActivityFactory::INTALNIRE, "Facultate", "Ore si Laboratoare", 8.0, 16.0);
        agenda_luni.addActivity(facultate);
        activity_log.addEntry(facultate);
        agenda_luni.addTransport(Transport(METRO, 16.0, timeToDecimal(16, 40), "Lujerului", "Eroii Revolutiei"));
        agenda_luni.addActivity(make_shared<ServiciuPlatit>("Antrenament Bogdan", "Sesiune privata (1.5h)", 17.0, 18.5, 130.0, "Bogdan"));
        agenda_luni.addActivity(make_shared<ServiciuPlatit>("Antrenament Mihnea", "Sesiune privata (1.5h)", 18.5, 20.0, 130.0, "Mihnea"));
        agenda_luni.addTransport(Transport(CAR, 20.0, timeToDecimal(20, 30), "Sala", "Acasa", 20.0));
        agenda_luni.addActivity(make_shared<TimpLiber>("Timp Liber Acasa", "Relaxare/Masa", timeToDecimal(20, 30), timeToDecimal(23, 30), 5));
        weekly_agenda.insert({"Luni", agenda_luni});
        financial_log.addEntry(agenda_luni.calculateTotalDailyRevenue());
    } catch (const exception& e) { cerr << " Eroare Luni: " << e.what() << endl; }

    // --- Marti ---
    Calendar agenda_marti;
    try {
        agenda_marti.setSleepTime(0.0, 9.0);
        agenda_marti.addTransport(Transport(METRO, timeToDecimal(9, 20), timeToDecimal(9, 50), "Pacii", "Lujerului"));
        agenda_marti.addActivity(make_shared<Intalnire>("Facultate", "Ore si Laboratoare", 10.0, timeToDecimal(13, 40), "PBTower", 10));
        agenda_marti.addTransport(Transport(METRO, timeToDecimal(16, 30), timeToDecimal(17, 10), "Lujerului", "Eroii Revolutiei"));
        agenda_marti.addActivity(make_shared<ServiciuPlatit>("Antrenament Sten", "Sesiune 1.5h", timeToDecimal(17, 30), 19.0, 120.0, "Sten"));
        agenda_marti.addActivity(make_shared<ServiciuPlatit>("Antrenament Dragos", "Sesiune 1h", 19.0, 20.0, 90.0, "Dragos"));
        agenda_marti.addActivity(make_shared<ServiciuPlatit>("Antrenament David", "Sesiune 1.5h", 20.0, timeToDecimal(21, 30), 130.0, "David"));
        agenda_marti.addTransport(Transport(CAR, timeToDecimal(21, 30), 22.0, "Sala", "Acasa", 25.0));
        weekly_agenda.insert({"Marti", agenda_marti});
    } catch (const exception& e) { cerr << "Eroare Marti: " << e.what() << endl; }

    // --- Miercuri ---
    Calendar agenda_miercuri;
    try {
        agenda_miercuri.setSleepTime(23.0, 10.0);
        agenda_miercuri.addTransport(Transport(METRO, timeToDecimal(11, 20), timeToDecimal(11, 50), "Pacii", "Piata Unirii"));
        agenda_miercuri.addActivity(make_shared<ServiciuPlatit>("Antrenament Cosmin", "Sesiune 1.5h", 12.0, timeToDecimal(13, 30), 100.0, "Cosmin"));
        agenda_miercuri.addTransport(Transport(METRO, timeToDecimal(13, 30), 14.0, "Piata Unirii", "Lujerului"));
        agenda_miercuri.addActivity(make_shared<Intalnire>("Facultate", "Ore", 14.0, timeToDecimal(15, 50), "PBTower", 10));
        agenda_miercuri.addTransport(Transport(METRO, 16.0, timeToDecimal(16, 40), "Lujerului", "Eroii Revolutiei"));
        agenda_miercuri.addActivity(make_shared<ServiciuPlatit>("Antrenament Ucrainean", "Sesiune 1.5h", 17.0, timeToDecimal(18, 30), 130.0, "Client U"));
        agenda_miercuri.addActivity(make_shared<ServiciuPlatit>("Antrenament Raisa", "Sesiune 1h", timeToDecimal(18, 30), timeToDecimal(19, 30), 90.0, "Raisa"));
        agenda_miercuri.addTransport(Transport(METRO, timeToDecimal(19, 40), timeToDecimal(20, 30), "Eroii Revolutiei", "Pacii"));
        weekly_agenda.insert({"Miercuri", agenda_miercuri});
    } catch (const exception& e) { cerr << "Eroare Miercuri: " << e.what() << endl; }

    // --- Joi ---
    Calendar agenda_joi;
    try {
        agenda_joi.setSleepTime(timeToDecimal(0, 30), timeToDecimal(7, 30));
        agenda_joi.addTransport(Transport(METRO, 8.0, timeToDecimal(8, 50), "Pacii", "Eroii Revolutiei"));
        agenda_joi.addActivity(make_shared<ServiciuPlatit>("Antrenament Alex", "Sesiune 1.5h", 9.0, timeToDecimal(10, 30), 120.0, "Alex"));
        agenda_joi.addActivity(make_shared<ServiciuPlatit>("Antrenament Bogdan (Premium)", "Sesiune 1.5h", timeToDecimal(10, 30), 12.0, 140.0, "Bogdan"));
        agenda_joi.addTransport(Transport(MIXT, timeToDecimal(12, 10), timeToDecimal(13, 40), "Eroii Revolutiei", "Magurele", 6.0));
        agenda_joi.addActivity(make_shared<Intalnire>("Facultate Magurele", "Fizica/Laboratoare", 14.0, timeToDecimal(19, 50), "Magurele", 10));
        agenda_joi.addTransport(Transport(CAR, 20.0, 21.0, "Magurele", "Pacii", 40.0));
        agenda_joi.addActivity(make_shared<TimpLiber>("Teme/Proiecte", "Studiu intens", timeToDecimal(21, 30), timeToDecimal(23, 30), 8));
        weekly_agenda.insert({"Joi", agenda_joi});
    } catch (const exception& e) { cerr << "Eroare Joi: " << e.what() << endl; }

    // --- Vineri ---
    Calendar agenda_vineri;
    try {
        agenda_vineri.setSleepTime(2.0, 6.0);
        agenda_vineri.addActivity(make_shared<TimpLiber>("Alergare Park", "Antrenament fizic", timeToDecimal(6, 30), timeToDecimal(7, 30), 9));
        agenda_vineri.addActivity(make_shared<TimpLiber>("Relaxare si Teme", "Studiu usor", 8.0, 11.0, 5));
        agenda_vineri.addTransport(Transport(METRO, timeToDecimal(11, 10), timeToDecimal(11, 40), "Pacii", "Lujerului"));
        agenda_vineri.addActivity(make_shared<Intalnire>("Facultate", "Ore si Laboratoare", 12.0, timeToDecimal(17, 40), "PBTower", 10));
        agenda_vineri.addTransport(Transport(METRO, 18.0, timeToDecimal(18, 30), "Lujerului", "Pacii"));
        agenda_vineri.addActivity(make_shared<Deplasare>("Drum Bucuresti-Craiova", "Calatorie", timeToDecimal(19, 30), timeToDecimal(21, 30), "Masina Proprie", 150.0));
        weekly_agenda.insert({"Vineri", agenda_vineri});
    } catch (const exception& e) { cerr << "Eroare Vineri: " << e.what() << endl; }

    vector<double> venituri_totale;
    for(auto const& [zi, cal] : weekly_agenda) venituri_totale.push_back(cal.calculateTotalDailyRevenue());
    double v_total = calculateSum(venituri_totale);
    int total_zile = calculateSum(vector<int>{1, 1, 1, 1, 1});

    for (const string& day : days) {
        if (weekly_agenda.count(day)) {
            const Calendar& agenda = weekly_agenda.at(day);
            cout << "\n--- >>> ZIUA: " << day << " <<< ---\n";
            agenda.displayProgram();
            cout << "\nCost: " << agenda.calculateTotalTravelCost() << " | Venit: " << agenda.calculateTotalDailyRevenue() << " RON\n";
            agenda.checkSleep("Noaptea dintre " + day);
        }
    }
    cout << "\n[T3 STATS] Venit saptamanal: " << v_total << " RON\n";
    activity_log.printStatus("Activitati");
}

int main() {
    runWeeklySchedule();
    return 0;
}