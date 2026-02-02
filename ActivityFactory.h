#ifndef ACTIVITYFACTORY_H
#define ACTIVITYFACTORY_H

#include "Activity.h"
#include <memory>
#include <string>

class ActivityFactory {
public:
    enum Type { LIBER, INTALNIRE, SERVICIU, DEPLASARE };

    static std::shared_ptr<Activity> create(Type t, std::string n, std::string d, double s, double e) {
        if (t == LIBER) return std::make_shared<TimpLiber>(n, d, s, e, 5);
        if (t == INTALNIRE) return std::make_shared<Intalnire>(n, d, s, e, "PBTower", 10);
        if (t == SERVICIU) return std::make_shared<ServiciuPlatit>(n, d, s, e, 130.0, "Client");
        if (t == DEPLASARE) return std::make_shared<Deplasare>(n, d, s, e, "Masina", 50.0);
        return nullptr;
    }
};
#endif