#include "physical_object.h"

physicalObject::physicalObject()
{
}

void physicalObject::update(){
    physics_.updateState();
}
