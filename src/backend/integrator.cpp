#include <vector>
#include "integrator.h"

Integrator::Integrator()
{
}

void Integrator::step_next(std::vector<float>& state, const std::vector<float>& ddt_state){
	return;
}

void forwardEuler::step_next(std::vector<float>& state, const std::vector<float>& ddt_state){
    for(size_t index=0; index<state.size(); ++index){
        state[index] = state[index] + ddt_state[index]*stepsize_;
        std::cout<< index << "from euler func: " << state[index] << std::endl;
    }
}
