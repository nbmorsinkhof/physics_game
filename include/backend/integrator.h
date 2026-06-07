#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <vector>
#include <iostream>
#include "physics.h"


class Physics;

class Integrator{
public:
    Integrator();

    virtual void step_next(
                std::vector<float>& state, 
                const std::vector<float>& ddt_state,
                Physics*);

protected:
    float stepsize_{0.02};
};



class forwardEuler : public Integrator{
public:
    void step_next(
            std::vector<float>& state,
            const std::vector<float>& ddt_state,
            Physics*) override;
};

class RungeKutta : public Integrator{
public:
    void step_next(
            std::vector<float>& state,
            const std::vector<float>& ddt_state,
            Physics*) override;
private:
    std::vector<float> k1_;
    std::vector<float> k2_;
    std::vector<float> k3_;
    std::vector<float> k4_;
};

#endif
