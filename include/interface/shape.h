#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <memory>
#include <QPainter>
#include <QPointF>

#include "simulation_widget.h"
class QPainter;

class Shape
{
public:
    Shape(std::vector<float>& position);
    virtual ~Shape() = default;

    virtual void draw(QPainter&, SimulationWidget&) const = 0;

    virtual std::unique_ptr<Shape> clone() const = 0;

    
protected:
    std::vector<float>& position_;
private:
};

class Circle : public Shape
{
public:
    Circle(std::vector<float>&position, float& radius);

    void draw(QPainter&) const override;

    std::unique_ptr<Shape> clone() const override;

protected:

private:
    float& radius_;
};

#endif
