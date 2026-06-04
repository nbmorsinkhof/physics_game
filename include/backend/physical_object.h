#include <vector>
#include <memory>
#include "physics.h"
#include "shape.h"

#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

class physicalObject{
public:
    physicalObject(
        std::string name,
        std::unique_ptr<Physics>
);
    
    const std::string& getName(){return name_;}
    const Shape* getShape(){return shape_.get();}
    void setShape(std::unique_ptr<Shape> s){shape_ = std::move(s);};
    virtual const bool inArea(std::vector<float>) = 0;
    virtual void createBoundary(float dx) = 0;
    const std::vector<float>& getPosition() const {return position_;}
    std::vector<float>& getState(){return physics_->getState();}
    void update();

protected:
    std::vector<float> position_{0, 0};
    std::vector<std::vector<float>> boundary_;
    void updatePos();

private:
    std::unique_ptr<Physics> physics_;
    std::unique_ptr<Shape> shape_;
    std::string name_;
};

class ElasticObject : public physicalObject
{
public:
    ElasticObject(std::string name);

    void createBoundary(float dx) override;
    const bool inArea(std::vector<float>) override;
    bool isOverlap(physicalObject&);
private:
    float radius_ = 0.1;
};

class RigidRectObject : public physicalObject
{

};

#endif
