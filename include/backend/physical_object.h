#include <vector>
#include "physics.h"

#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H


class physicalObject{
public:
    physicalObject();

    std::vector<float>& getPosition(){return position_;}
    std::vector<float>& getState(){return physics_.getState();}
    void update();

private:
    std::vector<float> position_{0, 0};
    springPhysics physics_;
};

#endif
