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

private:
    std::unordered_map<std::string, physicalObject> phyiscal_objects_;
};

#endif