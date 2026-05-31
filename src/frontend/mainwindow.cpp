#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <unordered_map>

MainWindow::MainWindow(Interface& interface, QWidget* parent)
    : QMainWindow(parent),
      interface_{interface}
{
    setWindowTitle("Physics Game");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    QFont buttonFont;
    buttonFont.setPointSize(18);

    /*Start button*/
    startButton_ = new QPushButton("Start", centralWidget);
    layout->addWidget(startButton_);
    startButton_->setFixedSize(200,50);
    startButton_->setFont(buttonFont);
    connect(startButton_, &QPushButton::clicked, this, &MainWindow::start);

    /*Stop Button*/
    stopButton_ = new QPushButton("Stop", centralWidget);
    layout->addWidget(stopButton_);
    stopButton_->setFixedSize(200, 50);
    stopButton_->setFont(buttonFont);
}

void MainWindow::start(){
    std::unordered_map<std::string, std::string> command;
    command[CMD_TYPE] = START;
    interface_.setCommand(command);
}
