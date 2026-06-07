#ifndef SIMULATION_WIDGET_H
#define SIMULATION_WIDGET_H

#include <QWidget>
#include <QPointF>
#include <vector>

#include "physical_object.h"
#include "interface.h"

class SimulationWidget : public QWidget
{
public:
    explicit SimulationWidget(int screen_width,
                              int screen_height,
                              SharedItems& shared_items,
                              QWidget* parent = nullptr);

    void setWorldCoordinates(
               const std::vector<float> x_lims,
               const std::vector<float> y_lims
            );

    const QPointF worldToScreen(float x, float y);
    const std::vector<int> distanceToPixel(float x, float y);
protected:
    void paintEvent(QPaintEvent* event) override;

private:
    int screen_width_;
    int screen_height_;
    SharedItems& shared_items_;
    std::vector<float> world_x_lims_ = {-1, 1};
    std::vector<float> world_y_lims_ = {-1, 1};

    void paintBackground(QPainter& painter);
    void paintBody(QPainter& painter, const physicalObject* object);
};

#endif
