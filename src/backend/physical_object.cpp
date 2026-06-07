#include "physical_object.h"
#include "physics.h"
#include <numbers>
#include <cmath>
#include <algorithm>

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
    updatePos();
}

void physicalObject::updatePos(){
    std::vector<float>& state = getState();
    position_[0] = state[0];
    position_[1] = 0.0;
}

// Elastic Object
ElasticObject::ElasticObject(std::string name, float x, float y)
                    : physicalObject(name,
                                     std::make_unique<ElasticObjectPhysics>(stretch_x_, stretch_y_))
{
    position_ = {x, y};
    physics_->setState({x, 0.0f, y, 0.0f});
    setShape(std::make_unique<Circle>(position_, radius_x_, radius_y_));
    createBoundary(0.001);
}

const bool ElasticObject::inArea(std::vector<float> pos){
    float dx = position_[0]-pos[0];
    float dy = position_[1]-pos[1];
    float distance_sq = dx*dx + dy*dy;
    if(distance_sq<radius_*radius_){
        return true;
    }
    else
    {
        return false;
    }
}

void ElasticObject::checkCollision(physicalObject& object){
    std::vector<std::vector<float>> object_boundary = object.getBoundary();
    std::vector<std::vector<float>> points_in_area;
    std::vector<float> distance_to_center;
    bool in_area{false};
    std::cout<<"boundary size: "<<object_boundary.size()<<std::endl; 
    for(std::vector<float> boundary_point : object_boundary){
        //std::cout<<boundary_point[0]<<std::endl;
        if(inArea(boundary_point)){
            points_in_area.push_back(boundary_point);
            float x = boundary_point[0];
            float y = boundary_point[1];
            distance_to_center.push_back(std::sqrt(x*x + y*y));
            in_area = true;
            std::cout<<"Collision detected" << std::endl;
        }
    }
    if(in_area){
        auto minIt = std::min_element(distance_to_center.begin(), distance_to_center.end());
        float minDistance = *minIt;
        std::size_t min_idx = std::distance(distance_to_center.begin(), minIt);
        std::vector<float> min_point = points_in_area[min_idx];
        
        if(min_point[1]>position_[1] && !in_collision_){
            down_stretch_ = true;
            std::cout<<"above:" << min_point[1]-position_[1]<< std::endl;
            stretch_y_ = radius_-(min_point[1]-position_[1]);
        }else if(min_point[1]<=position_[1] && !in_collision_){
            up_stretch_ = true;
            std::cout<<"below: "<< position_[1] - min_point[1] <<std::endl;
            stretch_y_ = -(radius_-(position_[1] - min_point[1]));
        }
        if(up_stretch_){
            stretch_y_ = -(2.0f * radius_ - (min_point[1]-(position_[1]-radius_)));
            stretch_y_ = -((position_[1] + radius_) - min_point[1]);
        }else if(down_stretch_){
            stretch_y_ = 2.0f * radius_ - ((position_[1]+radius_) - min_point[1]);
            stretch_y_ = (position_[1]-radius_) - min_point[1];
        }
        radius_y_ = radius_*(3.0f*radius_-std::abs(stretch_y_))/(3.0f*radius_);

        in_collision_ = true;
    }else{
        stretch_x_ = 0.0f;
        stretch_y_ = 0.0f;
        in_collision_ = false;
        left_stretch_ = false;
        right_stretch_ = false;
        up_stretch_ = false;
        down_stretch_ = false;
        radius_y_ = radius_;
    }
    return;
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

void ElasticObject::updatePos(){
    std::vector<float> state = getState();
    position_[0] = state[0];
    position_[1] = state[2];
    std::cout<<state[2]<<std::endl;
}

void ElasticObject::setDimensions(std::vector<float> dims){
    radius_ = dims[0];
}
// Rigid Rectangular object
RigidRectObject::RigidRectObject(std::string name, float x, float y)
                    : physicalObject(name,
                                     std::make_unique<RigidStaticBodyPhysics>())
{
    setShape(std::make_unique<Rectangle>(position_, width_, height_));
    position_ = {x, y};
    std::vector<float> state = {x, 0.0f, y, 0.0f};
    physics_->setState(state);
    createBoundary(0.005);
}


const bool RigidRectObject::inArea(std::vector<float> position){
    bool within_x = (position[0]>position_[0]-0.5f*width_) &&
                    (position[0]<position_[0]+0.5f*width_);
    bool within_y = (position[1]>position_[1]-0.5f*height_) && 
                    (position[1]<position_[1]+0.5f*height_);
    if(within_x && within_y){return true;} else {return false;}
}

void RigidRectObject::checkCollision(physicalObject& object){
    return;
}

void RigidRectObject::createBoundary(float dx){
    std::vector<std::vector<float>> boundary;
    int N = (2*width_+2*height_)/dx;
    int side{0};
    float x{position_[0]-0.5f*width_};
    float y{position_[1]-0.5f*height_};
    for(int n=0; n<N; ++n){
        boundary.push_back({x, y});
        if(side==0){
            y += dx;
            if(y>position_[1]+0.5f*height_){
                side=1;
            }
        }
        else if(side==1){
            x += dx;
            if(x>position_[0]+0.5f*width_){
                side = 2;
            }
        }
        else if(side==2){
            y -= dx;
            if(y<position_[1]-0.5f*height_){
                side = 3;
            }
        }
        else if(side==3){
            x -= dx;
            if(x<position_[0]-0.5f*width_){
                return;
            }
        }
    }
    std::cout<< " boundary created with size: " << boundary.size() <<std::endl;
    boundary_ = boundary;
}

void RigidRectObject::updatePos(){
    std::vector<float> state = getState();
    position_[0] = state[0];
    position_[1] = state[2];
}

void RigidRectObject::setDimensions(std::vector<float> dims){
    width_ = dims[0];
    height_ = dims[1];
}
