#include <vector>
#include <unordered_map>
#include <string>
#include "physical_object.h"
#include "interface.h"

#ifndef SIMULATOR_H
#define SIMULATOR_H

class Simulator{
public:
    Simulator(Interface&);

    void simulate(int simulate_time);
    void addPhysicalObject(std::string& name, physicalObject& physical_object);
    void handleCommandButtons();
private:
    std::unordered_map<std::string, physicalObject> physical_objects_;
    Interface& interface_;
    bool running_{false};
};

#endif
