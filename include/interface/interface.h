#include <string>
#include <unordered_map>
#include <mutex>

#include "shape.h"
#include "physical_object.h"
#include "space.h"

#ifndef INTERFACE_H
#define INTERFACE_H

const std::string CMD_TYPE{"cmd_type"};
const std::string START{"start"};
const std::string STOP{"stop"};

class sharedMessage
{
public:
    void setMessage(std::unordered_map<std::string, std::string> message);
    const std::unordered_map<std::string, std::string> getMessage();
    const bool messagePresent();
private:
    bool message_present_{false};
    std::unordered_map<std::string, std::string> message_;
    std::mutex mutex_;
};

class SharedItems
{
public:
    void addShape(std::string, const Shape*);
    const std::unordered_map<std::string, std::unique_ptr<Shape>> getShapes();

    void setSpaceObject(Space&);
    const Space getSpaceObject();

private:
    std::unordered_map<std::string, const Shape*> shapes_;
    Space* space_;
    std::mutex mutex_;
};

class Interface
{
public:
    Interface();

    void setStatus(std::unordered_map<std::string, std::string>);
    const std::unordered_map<std::string, std::string> getStatus();

    void setCommand(std::unordered_map<std::string, std::string>);
    const std::unordered_map<std::string, std::string> getCommand();
    const bool commandPresent();
private:
    sharedMessage command_msg_;
    sharedMessage status_msg_;
};


#endif
