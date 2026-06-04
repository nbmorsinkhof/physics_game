#ifndef SPACE_H
#define SPACE_H

#include <vector>

class Space{
public:
    Space();

    void setXlims(std::vector<float> xlims){x_lims_=xlims;}
    void setYlims(std::vector<float> ylims){y_lims_=ylims;}
    const std::vector<float> getXlims(){return x_lims_;}
    const std::vector<float> getYlims(){return y_lims_;}

private:
    std::vector<float> x_lims_ = {-1.0, 1.0};
    std::vector<float> y_lims_ = {-1.0, 1.0};
};

#endif
