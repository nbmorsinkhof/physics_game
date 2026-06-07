#include <vector>
#include <memory>
#include "physics.h"
#include "shape.h"

#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H


class Shape;

class physicalObject{
public:
    physicalObject(
        std::string name,
        std::unique_ptr<Physics>
);
    virtual ~physicalObject() = default;

    const std::string& getName(){return name_;}
    const Shape* getShape(){return shape_.get();}
    void setShape(std::unique_ptr<Shape> s){shape_ = std::move(s);};
    virtual const bool inArea(std::vector<float>) = 0;
    virtual void createBoundary(float dx) = 0;
    std::vector<std::vector<float>> getBoundary(){return boundary_;}
    virtual void checkCollision(physicalObject&) = 0;
    void setPosition(float x, float y){position_={x, y};}
    const std::vector<float>& getPosition() const {return position_;}
    std::vector<float>& getState(){return physics_->getState();}
    virtual void setDimensions(std::vector<float>) = 0;
    void update();

protected:
    std::vector<float> position_;
    std::vector<std::vector<float>> boundary_;
    virtual void updatePos();
    std::unique_ptr<Physics> physics_;
    std::unique_ptr<Shape> shape_;
    std::string name_;
};

// Elastic object
class ElasticObject : public physicalObject
{
public:
    ElasticObject(std::string name, float x=0.0, float y=0.0);

    void createBoundary(float dx) override;
    void checkCollision(physicalObject&);
    const bool inArea(std::vector<float>) override;
    bool isOverlap(physicalObject&);
    void setDimensions(std::vector<float>) override;
protected:
    void updatePos() override;
private:
    float radius_ = 0.1;
    float radius_y_ = 0.1;
    float radius_x_ = 0.1;
    float stretch_x_{0.0};
    float stretch_y_{0.0};
    bool left_stretch_{false};
    bool right_stretch_{false};
    bool up_stretch_{false};
    bool down_stretch_{false};
    bool in_collision_{false};
};

//Rigid Rect object
class RigidRectObject : public physicalObject
{
public:
    RigidRectObject(std::string name, float x=0.0f, float y=0.0f);

    void createBoundary(float dx) override;
    void checkCollision(physicalObject&) override;
    const bool inArea(std::vector<float>) override;

    std::vector<float> getDimensions(){return std::vector<float> {width_, height_};}
    void setDimensions(std::vector<float>) override;
protected:
    void updatePos() override;
private:
    float width_{1.0};
    float height_{0.2};
};

#endif
