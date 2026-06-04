#include "physical_object.h"
#include "physics.h"
#include <numbers>
#include <cmath>


#define PI 3.1415926
physicalObject::physicalObject(
                    std::string name,
                    std::unique_ptr<Physics> physics
)
    : name_{name},
      physics_{std::move(physics)}
{
}

void physicalObject::update(){
    physics_->updateState();
}

void physicalObject::updatePos(){
    std::vector<float>& state = getState();
    position_[0] = state[0];
    position_[1] = 0.0;
}

// Elastic Object
ElasticObject::ElasticObject(std::string name)
                    : physicalObject(name,
                                     std::make_unique<ElasticObjectPhysics>())
{
    setShape(std::make_unique<Circle>(position_, radius_));
    createBoundary(0.001);
}

const bool ElasticObject::inArea(std::vector<float> pos){
    float dx = position_[0]-pos[0];
    float dy = position_[1]-pos[1];
    float distance_sq = dx*dx + dy*dy;
    if(distance_sq*distance_sq<radius_*radius_){
        return true;
    }
    else
    {
        return false;
    }
}

void ElasticObject::createBoundary(float dx){
    std::vector<std::vector<float>> boundary;
    int N = 2*PI/dx;
    float d_angle = dx/radius_;
    float angle{0.0};
    float x{0.0};
    float y{0.0};
    for(int n=0; n<N; ++n){
        x = radius_*std::cos(angle);
        y = radius_*std::sin(angle);
        boundary.push_back({x, y});
        angle += d_angle;
    }
    boundary_ = boundary;
}
