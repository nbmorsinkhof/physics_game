#include <vector>
#include "physics.h"

#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H


class physicalObject{
public:
    physicalObject();

    std::vector<float>& getPosition(){return position_;}
    void update();

private:
    std::vector<float> position_{0, 0};
    Physics physics_;
};

#endif