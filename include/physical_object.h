#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <vector>

class physicalObject{
public:
    physicalObject();

    std::vector<float>& getPosition(){return position_;}

private:
    std::vector<float> position_{0, 0};
};

#endif