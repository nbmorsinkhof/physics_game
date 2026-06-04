#include <vector>
#include <string>
#include <memory>
#include "integrator.h"


#ifndef PHYSICS_H
#define PHYSICS_H



class Physics{
public:
    Physics();

    std::vector<float>& getState(){return state_;}
    void printState(std::vector<float>& state, std::string name);

    void updateState();

    virtual void stateSpace();

protected:
    std::vector<float> state_;
    std::vector<float> ddt_state_;
    forwardEuler integrator_;
    float gravity_const_ = 9.81;

};


class springPhysics : public Physics{
public:
    springPhysics(){
	state_ = {0.5, 0}; //x, x_dot, y, y_dot
	ddt_state_ = {0, 0};
	}
    void stateSpace() override;

private:
    float spring_const_ = 1;
};

class ElasticObjectPhysics : public Physics{
public:
    explicit ElasticObjectPhysics();
    void stateSpace() override;
private:
    float spring_const_ = 1.0;
    float mass_ = 1;
    float d_stretch_x_ = 0.0;
    float d_stretch_y_ = 0.0;

};





#endif
