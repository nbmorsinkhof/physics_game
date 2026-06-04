#include "mainwindow.h"
#include "simulation_widget.h"
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <unordered_map>
#include <QTimer>

MainWindow::MainWindow(
                    Interface& interface,
                    SharedItems& shared_items,
                    QWidget* parent)
    : interface_{interface},
      shared_items_{shared_items},
      QMainWindow(parent)
{
    setWindowTitle("Physics Game");
    resize(SCREEN_WIDTH_, SCREEN_HEIGHT_);
    screen_timer_ = new QTimer(this);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    QFont buttonFont;
    buttonFont.setPointSize(18);

    /*Control Frame */
    QFrame* controlsFrame = new QFrame(centralWidget);
    controlsFrame->setFrameShape(QFrame::StyledPanel);
    controlsFrame->setGeometry(0, 0, CONTROL_BOX_WIDTH_, SCREEN_HEIGHT_);
    QVBoxLayout* controlsLayout = new QVBoxLayout(controlsFrame);
    /*Simulation Frame*/
    QFrame* simulationFrame = new QFrame(centralWidget);

    simulationFrame->setFrameShape(QFrame::StyledPanel);
    simulationFrame->setGeometry(250, 0, SCREEN_WIDTH_-CONTROL_BOX_WIDTH_, SCREEN_HEIGHT_);
    QVBoxLayout* simulationLayout = new QVBoxLayout(simulationFrame);
    simulation_widget_ = new SimulationWidget(
                SCREEN_WIDTH_-CONTROL_BOX_WIDTH_,
                SCREEN_HEIGHT_,
                shared_items_,
                simulationFrame);
    connect(screen_timer_, &QTimer::timeout, this ,[this]()
    {
        simulation_widget_ -> update();
    });
    /*Start button*/
    startButton_ = new QPushButton("Start", controlsFrame);
    controlsLayout->addWidget(startButton_);
    startButton_->setFixedSize(200,50);
    startButton_->setFont(buttonFont);
    connect(startButton_, &QPushButton::clicked, this, &MainWindow::start);

    /*Stop Button*/
    stopButton_ = new QPushButton("Stop", controlsFrame);
    controlsLayout->addWidget(stopButton_);
    stopButton_->setFixedSize(200, 50);
    stopButton_->setFont(buttonFont);
    connect(stopButton_, &QPushButton::clicked, this, &MainWindow::stop);
}

void MainWindow::start(){
    std::unordered_map<std::string, std::string> command;
    command[CMD_TYPE] = START;
    interface_.setCommand(command);
    screen_timer_->start(16);
}

void MainWindow::stop(){
    std::unordered_map<std::string, std::string> command;
    command[CMD_TYPE] = STOP;
    interface_.setCommand(command);
    screen_timer_->stop();
}
