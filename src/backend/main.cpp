#include "simulator.h"
#include "physical_object.h"
#include <thread>
int main(){
    physicalObject physical_object1;
    std::string object_name{"object1"};
    Simulator simulator;
    simulator.addPhysicalObject(object_name, physical_object1);

    std::thread simThread(&Simulator::simulate, &simulator, 5);
    simThread.join();
}
