#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interface.h"
#include "simulation_widget.h"

class QLabel;
class QPushButton;
class QTimer;

class MainWindow : public QMainWindow
{
public:
    MainWindow(
            Interface& interface,
            SharedItems& shared_items,
            QWidget* parent = nullptr);

    void start();
    void stop();

    void paintObject(QPainter& painter, std::vector<float> position);
private:
    QTimer* screen_timer_ = nullptr;
    QLabel* statusLabel_;
    QPushButton* startButton_;
    QPushButton* stopButton_;
    SimulationWidget* simulation_widget_;
    Interface& interface_;
    SharedItems& shared_items_;

    const int SCREEN_WIDTH_{1400};
    const int SCREEN_HEIGHT_{900};
    const int CONTROL_BOX_WIDTH_{250};
};

#endif
