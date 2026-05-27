#include "physics.h"

void Physics::updateState(){
    //update ddt_state
    stateSpace();
    //update state
    integrator_.step_next(state_, ddt_state_);
}