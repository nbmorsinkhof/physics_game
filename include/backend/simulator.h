#include <vector>
#include <unordered_map>
#include <string>
#include "physical_object.h"
#include "interface.h"
#include "space.h"

#ifndef SIMULATOR_H
#define SIMULATOR_H

class Simulator{
public:
    Simulator(
            Interface&,
            SharedItems&
    );

    void simulate(int simulate_time);
    void checkCollisions();
    void addPhysicalObject(std::string& name, std::unique_ptr<physicalObject> physical_object);
    void handleCommandButtons();
private:
    std::unordered_map<std::string, std::unique_ptr<physicalObject>> physical_objects_;
    Space space_;
    Interface& interface_;
    SharedItems& shared_items_;
    bool running_{false};
};

#endif
