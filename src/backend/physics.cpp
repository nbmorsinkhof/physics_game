#include "physics.h"
#include <iostream>

Physics::Physics()
    : integrator_{std::make_unique<RungeKutta>()}
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
    ddt_state_ = stateSpace(state_);
    //update state
    integrator_->step_next(state_, ddt_state_, this);
}

std::vector<float> Physics::stateSpace(std::vector<float> state){
    return state;
}

std::vector<float> springPhysics::stateSpace(std::vector<float> state){
    std::vector<float> ddt_state = {0, 0};
    ddt_state[0] = state[1];
    ddt_state[1] = -spring_const_*state[0];
    return ddt_state;
}

// Elastic object

ElasticObjectPhysics::ElasticObjectPhysics(
                            float& stretch_x,
                            float& stretch_y)
    : d_stretch_x_{stretch_x},
      d_stretch_y_{stretch_y}
{
    state_ = {0, 0, 0, 0};//x, dx, y, dy
    ddt_state_ = {0, 0, 0, 0};
}
std::vector<float> ElasticObjectPhysics::stateSpace(std::vector<float> state){
    std::vector<float> ddt_state = {0, 0, 0, 0};
    ddt_state[0] = state[1];
    ddt_state[1] = -spring_const_*d_stretch_x_/mass_;
    ddt_state[2] = state[3];
    ddt_state[3] = -200*spring_const_*d_stretch_y_/mass_ -10000.0*spring_const_*d_stretch_y_*d_stretch_y_*d_stretch_y_/mass_ - 10*state[3]*float(std::abs(d_stretch_y_)>0) - 0.1*state[3] - gravity_const_;
    std::cout<<"Spring force: " << ddt_state[3] << std::endl;
    return ddt_state;
}

//rigid rect body
RigidStaticBodyPhysics::RigidStaticBodyPhysics(){
    state_ = {0, 0, 0, 0};
    ddt_state_ = {0, 0, 0, 0};
}

std::vector<float> RigidStaticBodyPhysics::stateSpace(std::vector<float> state){
    std::vector<float> ddt_state = {0, 0, 0, 0};
    return ddt_state;
}

