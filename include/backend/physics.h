#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include <string>
#include <memory>
#include "integrator.h"

class Integrator;
class forwardEuler;

class Physics{
public:
    Physics();

    std::vector<float>& getState(){return state_;}
    void setState(const std::vector<float> state){state_=state;}
    void printState(std::vector<float>& state, std::string name);

    void updateState();

    virtual std::vector<float> stateSpace(std::vector<float>);

protected:
    std::vector<float> state_;
    std::vector<float> ddt_state_;
    std::unique_ptr<Integrator> integrator_;
    const float gravity_const_ = 9.81;

};


class springPhysics : public Physics{
public:
    springPhysics(){
	state_ = {0.5, 0}; //x, x_dot, y, y_dot
	ddt_state_ = {0, 0};
	}
    std::vector<float> stateSpace(std::vector<float>) override;

private:
    float spring_const_ = 1;
};

// Elastic object

class ElasticObjectPhysics : public Physics{
public:
    explicit ElasticObjectPhysics(float&, float&);
    std::vector<float> stateSpace(std::vector<float>) override;
private:
    float spring_const_ = 1.0;
    float damping_ = 10.0;
    float mass_ = 1;
    float& d_stretch_x_;
    float& d_stretch_y_;
    float diss_energy_y{0.0};
    

};


// RigidStaticBodyPhysics
class RigidStaticBodyPhysics : public Physics{
public:
    explicit RigidStaticBodyPhysics();
    std::vector<float> stateSpace(std::vector<float>) override;
};


#endif
