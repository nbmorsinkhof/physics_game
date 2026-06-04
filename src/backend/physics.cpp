#include "physics.h"
#include <iostream>

Physics::Physics()
{
}

void Physics::printState(std::vector<float>& state, std::string name){
    std::cout<<"Printing State with size: " << state.size() << std::endl;
    for(size_t idx=0; idx<state_.size(); ++idx){
        std::cout << name << idx << ": " << state[idx] <<std::endl; 
    }
}

void Physics::updateState(){
    //update ddt_state
    stateSpace();
    //update state
    integrator_.step_next(state_, ddt_state_);
}

void Physics::stateSpace(){
    return;
}

void springPhysics::stateSpace(){
    ddt_state_[0] = state_[1];
    ddt_state_[1] = -spring_const_*state_[0];
}



// Elastic object

ElasticObjectPhysics::ElasticObjectPhysics(){
    state_ = {0, 0, 0, 0};//x, dx, y, dy
    ddt_state_ = {0, 0, 0, 0};
}
void ElasticObjectPhysics::stateSpace(){
    ddt_state_[0] = state_[1];
    ddt_state_[1] = -spring_const_*d_stretch_x_/mass_;
    ddt_state_[2] = state_[3];
    ddt_state_[3] = -spring_const_*d_stretch_y_/mass_;
}
