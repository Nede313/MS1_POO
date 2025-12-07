#include "Calendar.h"
#include "Transport.h"
#include "Activity.h"
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
    std::map<std::string, Calendar> weekly_agenda;

    vector<string> days = {"Luni", "Marti", "Miercuri", "Joi", "Vineri"};

    cout << "  INCARCAREA AGENDEI SAPTAMANALE (POO Demonstration) \n";

    Calendar agenda_luni;
    try {
        agenda_luni.setSleepTime(timeToDecimal(23, 30), 7.0); // 23:30 - 7:00

        agenda_luni.addTransport(Transport(METRO, timeToDecimal(7, 30), 8.0, "Pacii", "Lujerului"));
        auto facultate = make_shared<Intalnire>("Facultate", "Ore si Laboratoare", 8.0, 16.0, "PBTower", 10);
        agenda_luni.addActivity(facultate);
        agenda_luni.addTransport(Transport(METRO, 16.0, timeToDecimal(16, 40), "Lujerului", "Eroii Revolutiei"));

        auto antrenament_bogdan = make_shared<ServiciuPlatit>("Antrenament Bogdan", "Sesiune privata (1.5h)", 17.0, 18.5, 130.0, "Bogdan");
        agenda_luni.addActivity(antrenament_bogdan);
        auto antrenament_mihnea = make_shared<ServiciuPlatit>("Antrenament Mihnea", "Sesiune privata (1.5h)", 18.5, 20.0, 130.0, "Mihnea");
        agenda_luni.addActivity(antrenament_mihnea);

        agenda_luni.addTransport(Transport(CAR, 20.0, timeToDecimal(20, 30), "Sala", "Acasa", 20.0));
        auto timp_liber = make_shared<TimpLiber>("Timp Liber Acasa", "Relaxare/Masa", timeToDecimal(20, 30), timeToDecimal(23, 30), 5);
        agenda_luni.addActivity(timp_liber);

        weekly_agenda.insert({"Luni", agenda_luni});

    } catch (const exception& e) {
        cerr << " Eroare in adaugarea Luni: " << e.what() << endl;
    }

    Calendar agenda_marti;
    try {
        agenda_marti.setSleepTime(0.0, 9.0); // 00:00 - 9:00 (Somn lung)
        agenda_marti.addTransport(Transport(METRO, timeToDecimal(9, 20), timeToDecimal(9, 50), "Pacii", "Lujerului"));
        auto facultate = make_shared<Intalnire>("Facultate", "Ore si Laboratoare", 10.0, timeToDecimal(13, 40), "PBTower", 10);
        agenda_marti.addActivity(facultate);
        agenda_marti.addTransport(Transport(METRO, timeToDecimal(16, 30), timeToDecimal(17, 10), "Lujerului", "Eroii Revolutiei"));

        auto antrenament_sten = make_shared<ServiciuPlatit>("Antrenament Sten", "Sesiune 1.5h", timeToDecimal(17, 30), 19.0, 120.0, "Sten");
        agenda_marti.addActivity(antrenament_sten);
        auto antrenament_dragos = make_shared<ServiciuPlatit>("Antrenament Dragos", "Sesiune 1h", 19.0, 20.0, 90.0, "Dragos");
        agenda_marti.addActivity(antrenament_dragos);
        auto antrenament_david = make_shared<ServiciuPlatit>("Antrenament David", "Sesiune 1.5h", 20.0, timeToDecimal(21, 30), 130.0, "David");
        agenda_marti.addActivity(antrenament_david);

        agenda_marti.addTransport(Transport(CAR, timeToDecimal(21, 30), 22.0, "Sala", "Acasa", 25.0));

        weekly_agenda.insert({"Marti", agenda_marti});

    } catch (const exception& e) {
        cerr << "Eroare in adaugarea Marti: " << e.what() << endl;
    }

    Calendar agenda_miercuri;
    try {
        agenda_miercuri.setSleepTime(23.0, 10.0); // 23:00 - 10:00 (Somn foarte lung)
        agenda_miercuri.addTransport(Transport(METRO, timeToDecimal(11, 20), timeToDecimal(11, 50), "Pacii", "Piata Unirii"));

        auto antrenament_cosmin = make_shared<ServiciuPlatit>("Antrenament Cosmin", "Sesiune 1.5h", 12.0, timeToDecimal(13, 30), 100.0, "Cosmin");
        agenda_miercuri.addActivity(antrenament_cosmin);
        agenda_miercuri.addTransport(Transport(METRO, timeToDecimal(13, 30), 14.0, "Piata Unirii", "Lujerului"));

        auto facultate = make_shared<Intalnire>("Facultate", "Ore", 14.0, timeToDecimal(15, 50), "PBTower", 10);
        agenda_miercuri.addActivity(facultate);
        agenda_miercuri.addTransport(Transport(METRO, 16.0, timeToDecimal(16, 40), "Lujerului", "Eroii Revolutiei"));

        auto antrenament_ucrainean = make_shared<ServiciuPlatit>("Antrenament Ucrainean", "Sesiune 1.5h", 17.0, timeToDecimal(18, 30), 130.0, "Client U");
        agenda_miercuri.addActivity(antrenament_ucrainean);
        auto antrenament_raisa = make_shared<ServiciuPlatit>("Antrenament Raisa", "Sesiune 1h", timeToDecimal(18, 30), timeToDecimal(19, 30), 90.0, "Raisa");
        agenda_miercuri.addActivity(antrenament_raisa);

        agenda_miercuri.addTransport(Transport(METRO, timeToDecimal(19, 40), timeToDecimal(20, 30), "Eroii Revolutiei", "Pacii"));

        weekly_agenda.insert({"Miercuri", agenda_miercuri});

    } catch (const exception& e) {
        cerr << "Eroare in adaugarea Miercuri: " << e.what() << endl;
    }

    Calendar agenda_joi;
    try {
        agenda_joi.setSleepTime(timeToDecimal(0, 30), timeToDecimal(7, 30)); // 00:30 - 7:30

        agenda_joi.addTransport(Transport(METRO, 8.0, timeToDecimal(8, 50), "Pacii", "Eroii Revolutiei"));

        auto antrenament_alex = make_shared<ServiciuPlatit>("Antrenament Alex", "Sesiune 1.5h", 9.0, timeToDecimal(10, 30), 120.0, "Alex");
        agenda_joi.addActivity(antrenament_alex);
        auto antrenament_bogdan = make_shared<ServiciuPlatit>("Antrenament Bogdan (Premium)", "Sesiune 1.5h", timeToDecimal(10, 30), 12.0, 140.0, "Bogdan");
        agenda_joi.addActivity(antrenament_bogdan);

        agenda_joi.addTransport(Transport(MIXT, timeToDecimal(12, 10), timeToDecimal(13, 40), "Eroii Revolutiei", "Magurele", 6.0));

        auto facultate_fizica = make_shared<Intalnire>("Facultate Magurele", "Fizica/Laboratoare", 14.0, timeToDecimal(19, 50), "Magurele", 10);
        agenda_joi.addActivity(facultate_fizica);

        agenda_joi.addTransport(Transport(CAR, 20.0, 21.0, "Magurele", "Pacii", 40.0));

        auto teme = make_shared<TimpLiber>("Teme/Proiecte", "Studiu intens", timeToDecimal(21, 30), timeToDecimal(23, 30), 8);
        agenda_joi.addActivity(teme);

        weekly_agenda.insert({"Joi", agenda_joi});

    } catch (const exception& e) {
        cerr << "Eroare in adaugarea Joi: " << e.what() << endl;
    }

    Calendar agenda_vineri;
    try {
        agenda_vineri.setSleepTime(2.0, 6.0);

        auto alergare = make_shared<TimpLiber>("Alergare Park", "Antrenament fizic", timeToDecimal(6, 30), timeToDecimal(7, 30), 9);
        agenda_vineri.addActivity(alergare);
        auto relaxare_teme = make_shared<TimpLiber>("Relaxare si Teme", "Studiu usor", 8.0, 11.0, 5);
        agenda_vineri.addActivity(relaxare_teme);

        agenda_vineri.addTransport(Transport(METRO, timeToDecimal(11, 10), timeToDecimal(11, 40), "Pacii", "Lujerului"));

        auto facultate = make_shared<Intalnire>("Facultate", "Ore si Laboratoare", 12.0, timeToDecimal(17, 40), "PBTower", 10);
        agenda_vineri.addActivity(facultate);

        agenda_vineri.addTransport(Transport(METRO, 18.0, timeToDecimal(18, 30), "Lujerului", "Pacii"));

        auto drum_craiova = make_shared<Deplasare>("Drum Bucuresti-Craiova", "Calatorie", timeToDecimal(19, 30), timeToDecimal(21, 30), "Masina Proprie", 150.0);
        agenda_vineri.addActivity(drum_craiova);

        weekly_agenda.insert({"Vineri", agenda_vineri});

    } catch (const exception& e) {
        cerr << "Eroare in adaugarea Vineri: " << e.what() << endl;
    }

    cout << "          REZULTATELE AGENDEI SAPTAMANALE          \n";

    for (const string& day : days) {
        if (weekly_agenda.count(day)) {
            const Calendar& agenda = weekly_agenda.at(day);

            cout << "\n--- >>> ZIUA: " << day << " <<< ---\n";

            agenda.displayProgram();

            cout << "\nCost total deplasari: " << agenda.calculateTotalTravelCost() << " RON";
            cout << " | Venit TOTAL estimat: " << agenda.calculateTotalDailyRevenue() << " RON\n";

            agenda.checkSleep("Noaptea dintre " + day);

            agenda.displayByPriority();
            cout << "\n------------------------------------------------------\n";
        }
    }
}

int main() {
    runWeeklySchedule();
    return 0;
}