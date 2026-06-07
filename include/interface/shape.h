#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <memory>
#include <QPainter>
#include <QPointF>

#include "simulation_widget.h"
class QPainter;
class SimulationWidget;

class Shape
{
public:
    Shape(std::vector<float>& position);
    virtual ~Shape() = default;

    virtual void draw(QPainter&, SimulationWidget&) const = 0;

    virtual std::unique_ptr<Shape> clone() const = 0;

    std::vector<float> getPos(){return position_;}
protected:
    std::vector<float>& position_;
private:
};

// Circle
class Circle : public Shape
{
public:
    Circle(std::vector<float>&position, float& radius_x, float& radius_y);

    void draw(QPainter&, SimulationWidget&) const override;

    std::unique_ptr<Shape> clone() const override;

protected:

private:
    float& radius_x_;
    float& radius_y_;
};

//Rectangle
class Rectangle : public Shape
{
public:
    Rectangle(std::vector<float>& position, float& width, float& height);

    void draw(QPainter&, SimulationWidget&) const override;

    std::unique_ptr<Shape> clone() const override;

private:
    float& width_;
    float& height_;
};
#endif
