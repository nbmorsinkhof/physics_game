#include <chrono>
#include <thread>
#include <iostream>
#include <unordered_map>
#include "simulator.h"


using steady_clock = std::chrono::steady_clock;

void Simulator::simulate(int simulate_time){
    
    steady_clock::time_point first_time = steady_clock::now();
    steady_clock::time_point last_time = steady_clock::now();
    std::chrono::milliseconds dt = std::chrono::milliseconds(100);
    bool simulation_done{false};
    while(not simulation_done){
        for(const std::pair<const std::string, physicalObject>& object_pair : phyiscal_objects_){
            physicalObject physical_object = object_pair.second;
            physical_object.update();
        }
        std::this_thread::sleep_until(last_time+dt);
        last_time = steady_clock::now();
        steady_clock::duration elapsed = last_time - first_time;
        if (std::chrono::seconds(simulate_time)>elapsed){
            simulation_done = true;
        }
    }

}