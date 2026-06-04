#include <QApplication>
#include <thread>
#include <atomic>
#include <memory>

#include "simulator.h"
#include "interface.h"
#include "physical_object.h"
#include "mainwindow.h"

int main(int argc, char* argv[]){
    /*Interface between UI and backend*/
    Interface interface;
    SharedItems shared_items;
    /*UI*/
    QApplication app(argc, argv);
    MainWindow window(interface, shared_items);
    /*Simulator */
    Simulator simulator(interface, shared_items);
    std::string object_name{"object1"};
    simulator.addPhysicalObject(object_name, std::make_unique<ElasticObject>(object_name));
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
