#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <iostream>
#include <string>
#include <memory> 

using namespace std; 

class Activity {
private:
    string name;
    string description;
    double start_hour;
    double end_hour;
    long id;

    static long next_id;
    static int activity_count;

protected:
    double calculateDuration() const {
        return end_hour - start_hour;
    }

public:

    Activity(const string& name, const string& description, double start_hour, double end_hour);
    virtual ~Activity();

    virtual shared_ptr<Activity> clone() const = 0;

    virtual double calculatePriorityScore() const = 0;

    virtual void displayDetails(ostream& out) const = 0;

    void show(ostream& out) const;

    double getStartHour() const { return start_hour; }
    double getEndHour() const { return end_hour; }

    friend ostream& operator<<(ostream& out, const Activity& a) {
        a.show(out);
        return out;
    }
};

class TimpLiber : public Activity {
private:
    int relaxing_level;
public:
    TimpLiber(const string& name, const string& desc, double sh, double eh, int level);
    shared_ptr<Activity> clone() const override;
    double calculatePriorityScore() const override;
    void displayDetails(ostream& out) const override;
};

class Intalnire : public Activity {
private:
    string location;
    int required_participants;
public:
    Intalnire(const string& name, const string& desc, double sh, double eh, const string& loc, int req);
    shared_ptr<Activity> clone() const override;
    double calculatePriorityScore() const override;
    void displayDetails(ostream& out) const override;
};

class Deplasare : public Activity {
private:
    string transport_mode;
    double cost;
public:
    Deplasare(const string& name, const string& desc, double sh, double eh, const string& mode, double cost);
    shared_ptr<Activity> clone() const override;
    double calculatePriorityScore() const override;
    void displayDetails(ostream& out) const override;

    double getCost() const { return cost; }
};

class ServiciuPlatit : public Activity {
private:
    double venit_fix_sedinta;
    string client_name;
public:
    ServiciuPlatit(const string& name, const string& desc, double sh, double eh, double venit, const string& client); // double
    shared_ptr<Activity> clone() const override;
    double calculatePriorityScore() const override;
    void displayDetails(ostream& out) const override;

    double calculateRevenue() const {
        return venit_fix_sedinta;
    }
};

#endif