#include <QApplication>
#include <thread>
#include <atomic>

#include "simulator.h"
#include "interface.h"
#include "physical_object.h"
#include "mainwindow.h"

int main(int argc, char* argv[]){
    /*Interface between UI and backend*/
    Interface interface;
    /*UI*/
    QApplication app(argc, argv);
    MainWindow window(interface);
    /*Simulator */
    Simulator simulator(interface);
    physicalObject physical_object1;
    std::string object_name{"object1"};
    simulator.addPhysicalObject(object_name, physical_object1);
    std::thread simThread(&Simulator::simulate, &simulator, 5);

    std::atomic<bool> running = true;
    window.show();
    int result = app.exec();
    running = false;

    if (simThread.joinable()){
        simThread.join();
    }
    return result;
}
