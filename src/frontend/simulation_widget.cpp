#include "simulation_widget.h"
#include "space.h"
#include "physical_object.h"

#include <QPainter>
#include <unordered_map>

SimulationWidget::SimulationWidget(int screen_width,
                                   int screen_height,
                                   SharedItems& shared_items,
                                   QWidget* parent)
    : screen_width_{screen_width},
      screen_height_{screen_height},
      shared_items_{shared_items},
      QWidget(parent)
{
    setMinimumSize(screen_width_, screen_height_);
}

void SimulationWidget::setWorldCoordinates(
                                const std::vector<float> x_lims,
                                const std::vector<float> y_lims
){
    world_x_lims_ = x_lims;
    world_y_lims_ = y_lims;
}

void SimulationWidget::paintEvent(QPaintEvent* event){

    Q_UNUSED(event);//Unused event

    //drawing tool paints on the simulationWidget
    QPainter painter(this);
    //draw smooth edges
    painter.setRenderHint(QPainter::Antialiasing);

    //Clear simulation screen
    painter.fillRect(rect(), Qt::white);
    //draw border around screen
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    Space space = shared_items_.getSpaceObject();
    std::unordered_map<std::string, std::unique_ptr<Shape>> shapes = shared_items_.getShapes();
    setWorldCoordinates(space.getXlims(), space.getYlims());
    //for(auto& [name, s] : shapes){
    //    std::cout << "From paint: " << name << std::endl;
    //    s->draw(painter);
    //}
}

const QPointF SimulationWidget::worldToScreen(float x, float y){
    QPointF screen_pos(0, 0);
    float x_width = world_x_lims_[1] - world_x_lims_[0];
    float y_height = world_y_lims_[1] - world_y_lims_[0];
    if(!x_width>0 || !y_height>0){
        return screen_pos;
    }

    int x_pixel = screen_width_*(x-world_x_lims_[0])/x_width;
    int y_pixel = screen_height_-screen_height_*(y-world_y_lims_[0])/y_height;
    screen_pos = QPointF(x_pixel, y_pixel);
    return screen_pos;
}



void SimulationWidget::paintBackground(QPainter& painter){
    return;
}

void SimulationWidget::paintBody(QPainter& painter, const physicalObject* object){
    const std::vector<float> position = object->getPosition();
    QPointF Qpos = worldToScreen(position[0], position[1]);
    std::cout<<"posx: " << position[0] <<std::endl;
    std::cout<<"Qposx: " << Qpos.x() << " " <<"Qposy: " << Qpos.y() <<std::endl; 
    float radius{30.0};
    painter.drawEllipse(Qpos, radius, radius);
}

