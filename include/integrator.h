#include <vector>

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

class Integrator{
public:
    Integrator();
    
    virtual void step_next(std::vector<float>& state, const std::vector<float>& ddt_state);

private:
    float stepsize_{0.1};
};



class forwardEuler : public Integrator{
public:
    void step_next(std::vector<float>& state, const std::vector<float>& ddt_state) override;
};

#endif