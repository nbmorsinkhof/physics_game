#include <vector>
#include <unordered_map>
#include <string>
#include "physical_object.h"

#ifndef SIMULATOR_H
#define SIMULATOR_H

class Simulator{
public:
    Simulator();

    void simulate(int simulate_time);
    void addPhysicalObject(std::string& name, physicalObject& physical_object);
private:
    std::unordered_map<std::string, physicalObject> physical_objects_;
};

#endif
