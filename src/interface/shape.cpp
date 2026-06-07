#include "shape.h"

// Base Class
Shape::Shape(std::vector<float>& position)
    : position_{position}
{}


// Circle
Circle::Circle(
                std::vector<float>& position,
                float& radius_x,
                float& radius_y
)
    :   Shape(position),
        radius_x_{radius_x},
        radius_y_{radius_y}
{}

void Circle::draw(QPainter& painter, SimulationWidget& sim_widget) const{
    QPointF pos = sim_widget.worldToScreen(position_[0], position_[1]);
    std::cout<<"x: " << position_[0] << "y: " << position_[1] <<std::endl;
    std::vector<int> pixel_radius = sim_widget.distanceToPixel(radius_x_, radius_y_);
    painter.drawEllipse(pos, pixel_radius[0], pixel_radius[1]);
}

std::unique_ptr<Shape> Circle::clone() const{
    return std::make_unique<Circle>(*this);
}

// Rectangle
Rectangle::Rectangle(
                    std::vector<float>& position,
                    float& width,
                    float& height
)
    : Shape(position),
      width_{width},
      height_{height}
{}

void Rectangle::draw(QPainter& painter, SimulationWidget& sim_widget) const{
    QPointF pos = sim_widget.worldToScreen(position_[0]-width_/2.0f, position_[1]+height_/2.0f);
    std::vector<int> pixel_dimensions = sim_widget.distanceToPixel(width_, height_);
    painter.drawRect(pos.x(), pos.y(), pixel_dimensions[0], pixel_dimensions[1]);
}

std::unique_ptr<Shape> Rectangle::clone() const{
    std::cout << "Clone shape. x: " << position_[0] << "y: " << position_[1] << std::endl;
    return std::make_unique<Rectangle>(*this);
}
