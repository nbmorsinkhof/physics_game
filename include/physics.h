#include <vector>
#include "integrator.h"


#ifndef PHYSICS_H
#define PHYSICS_H



class Physics{
public:
    Physics();

    std::vector<float>& getState(){return state_;}
    
    void updateState();

    virtual void stateSpace();

private:
    std::vector<float> state_;
    std::vector<float> ddt_state_;
    forwardEuler integrator_;

};


class springPhysics : public Physics{
public:
    void stateSpace() override;
};

#endif