#include "interface.h"

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

