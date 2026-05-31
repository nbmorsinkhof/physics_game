#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interface.h"

class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
public:
    MainWindow(Interface& interface, QWidget* parent = nullptr);

    void start();
    void stop();
private:
    QLabel* statusLabel_;
    QPushButton* startButton_;
    QPushButton* stopButton_;
    Interface& interface_;
};

#endif
