#include <vector>
#include "integrator.h"


void Integrator::step_next(std::vector<float>& state, const std::vector<float>& ddt_state){
    for(size_t index=0; index<state.size(); ++index){
        state[index] = state[index] + ddt_state[index]*stepsize_;
    }
}