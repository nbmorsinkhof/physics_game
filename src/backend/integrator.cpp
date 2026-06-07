#include <vector>
#include "integrator.h"

Integrator::Integrator()
{
}

void Integrator::step_next(
                    std::vector<float>& state, 
                    const std::vector<float>& ddt_state,
                    Physics* physics=nullptr){
	return;
}

void forwardEuler::step_next(
                    std::vector<float>& state,
                    const std::vector<float>& ddt_state,
                    Physics* physics = nullptr){
    for(size_t index=0; index<state.size(); ++index){
        state[index] = state[index] + ddt_state[index]*stepsize_;
        //std::cout<< index << "from euler func: " << state[index] << std::endl;
    }
}


void RungeKutta::step_next(
                std::vector<float>& state,
                const std::vector<float>& ddt_state,
                Physics* physics = nullptr){
    std::vector<float> fun_input = state;
    k1_ = physics->stateSpace(fun_input);
    for(size_t idx=0; idx<state.size(); ++idx){
        fun_input[idx] = state[idx] + k1_[idx]*stepsize_/2;
    }
    k2_ = physics->stateSpace(fun_input);
    for(size_t idx=0; idx<state.size(); ++idx){
        fun_input[idx] = state[idx] + k2_[idx]*stepsize_/2;
    }
    k3_ = physics->stateSpace(fun_input);
    for(size_t idx=0; idx<state.size(); ++idx){
        fun_input[idx] = state[idx] + stepsize_*k3_[idx];
    }
    k4_ = physics->stateSpace(fun_input);
    //calc state
    for(size_t idx=0; idx<state.size(); ++idx){
        state[idx] = state[idx] + (stepsize_/6.0f)*(k1_[idx] + 2.0f*k2_[idx] + 2.0f*k3_[idx] + k4_[idx]);
    }
}
