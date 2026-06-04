#include "shape.h"

// Base Class
Shape::Shape(std::vector<float>& position)
    : position_{position}
{}


// Circle
Circle::Circle(
                std::vector<float>& position,
                float& radius
)
    :   Shape(position),
        radius_{radius}
{}

void Circle::draw(QPainter& painter, SimulationWidget& sim_widget) const{
    QPointF pos = sim_widget.worldToScreen(position_);
    painter.drawEllipse(QPointF{pos, radius_, radius_);
}

std::unique_ptr<Shape> Circle::clone() const{
    return std::make_unique<Circle>(*this);
}


