#include "point_t.h"

int Point_t::get_x() const {
    return this->x;
}
int Point_t::get_y() const {
    return this->y;
}
int Point_t::get_width() const {
    return this->rect_width;
}
int Point_t::get_height() const {
    return this->rect_height;
}

bool Point_t::operator>(const Point_t& p) const{
    if(this->x > p.get_x()) {
        return true;
    }
    else if(this->x < p.get_x()) {
        return false;
    }
    else {
        if(this->y > p.get_y()) {
            return true;
        }
        else if(this->y < p.get_y()) {
            return false;
        }
    }
}

bool Point_t::operator<(const Point_t& p) const{
    if(this->x < p.get_x()) {
        return true;
    }
    else if(this->x > p.get_x()) {
        return false;
    }
    else {
        if(this->y < p.get_y()) {
            return true;
        }
        else if(this->y > p.get_y()) {
            return false;
        }
    }
}
