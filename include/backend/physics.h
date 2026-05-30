#include <vector>
#include <string>
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

};


class springPhysics : public Physics{
public:
    springPhysics(){
	state_ = {2, 0};
	ddt_state_ = {0, 0};
	}
    void stateSpace() override;

private:
    float spring_const_ = 1;
};

#endif
