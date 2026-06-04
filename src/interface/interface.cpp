#include "interface.h"
#include <mutex>

Interface::Interface(){};

void Interface::setStatus(std::unordered_map<std::string, std::string> status_msg){
    status_msg_.setMessage(status_msg);
}

const std::unordered_map<std::string, std::string> Interface::getStatus(){
    return status_msg_.getMessage();
}

void Interface::setCommand(std::unordered_map<std::string, std::string> command_msg){
    command_msg_.setMessage(command_msg);
}

const std::unordered_map<std::string, std::string> Interface::getCommand(){
    return command_msg_.getMessage();
}

const bool Interface::commandPresent(){
    return command_msg_.messagePresent();
}

/*Shared Message*/
void sharedMessage::setMessage(const std::unordered_map<std::string, std::string> message){
    std::lock_guard<std::mutex> lock(mutex_);
    message_ = message;
    message_present_ = true;
}

const std::unordered_map<std::string, std::string> sharedMessage::getMessage(){
    std::lock_guard<std::mutex> lock(mutex_);
    message_present_ = false;
    return message_;
}

const bool sharedMessage::messagePresent(){
    std::lock_guard<std::mutex> lock(mutex_);
    return message_present_;
}

/*Shared Items*/

void SharedItems::addShape(std::string name, const Shape* shape){
    std::lock_guard<std::mutex> lock(mutex_);
    shapes_[name] = shape;
}

const std::unordered_map <std::string, std::unique_ptr<Shape>> SharedItems::getShapes(){
    std::lock_guard<std::mutex> lock(mutex_);
    std::unordered_map<std::string, std::unique_ptr<Shape>> cloned_shapes;
    for(auto& [name, shape] : shapes_){
        cloned_shapes[name] = shape->clone();
    }
    return cloned_shapes;
}

void SharedItems::setSpaceObject(Space& space){
    std::lock_guard<std::mutex> lock(mutex_);
    space_ = &space;
}

const Space SharedItems::getSpaceObject(){
    std::lock_guard<std::mutex> lock(mutex_);
    if(space_==nullptr){
        std::cout << "space_ is nullptr" << std::endl;
    }
    return *space_;
}
