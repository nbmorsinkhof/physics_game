#include <chrono>
#include <thread>
#include <iostream>
#include <unordered_map>
#include "simulator.h"


Simulator::Simulator(Interface& interface)
    : interface_{interface}
{
}

using steady_clock = std::chrono::steady_clock;

void Simulator::simulate(int simulate_time){
    
    steady_clock::time_point first_time = steady_clock::now();
    steady_clock::time_point last_time = steady_clock::now();
    std::chrono::milliseconds dt = std::chrono::milliseconds(100);
    bool simulation_done{false};
    while(not simulation_done){
        for(std::pair<const std::string, physicalObject>& object_pair : physical_objects_){
            physicalObject& physical_object = object_pair.second;
            physical_object.update();
            std::vector<float>& state = physical_object.getState();
            std::cout<<object_pair.first<<std::endl;
            for(size_t idx=0; idx<state.size(); ++idx){
                std::cout << "state_" << idx << ":" << state[idx] << std::endl;
            }
        }
        std::cout<<std::endl;
        std::this_thread::sleep_until(last_time+dt);
        last_time = steady_clock::now();
        steady_clock::duration elapsed = last_time - first_time;
        if (std::chrono::seconds(simulate_time)<elapsed){
            simulation_done = true;
        }
    }

}

void Simulator::addPhysicalObject(std::string& name, physicalObject& physical_object){
    physical_objects_[name] = physical_object;
    std::cout<<"Adding: " << name << std::endl;
    std::cout<<"Size: " << physical_objects_.size() << std::endl;
}
