#include "dot_t.h"
#include <iostream>

Dot_t::Dot_t() {
    this->x = 0;
    this->number_of_cells = 6;
    this->step = 40;
    this->ellipse_height = 40;
    this->ellipse_width = 40;
    this->position = 0;
}

Dot_t::Dot_t(int number) {
    this->x = 0;
    this->number_of_cells = number;
    this->step = 40;
    this->ellipse_height = 40;
    this->ellipse_width = 40;
    this->position = 0;
}

void Dot_t::move_left() {
    if(this->position == 0) {
        return;
    }
    this->position--;
    this->x -= this->ellipse_width;
}
void Dot_t::move_right() {
    if(this->position == 5) {
        return;
    }
    this->position++;
    this->x += this->ellipse_width;
}
void Dot_t::move_with_the_position(int state) {
    this->position = state;
    this->x = state * this->ellipse_width;
}
int Dot_t::get_x() const {
    return this->x;
}
int Dot_t::get_ellipse_width() const {
    return this->ellipse_width;
}
int Dot_t::get_ellipse_height() const {
    return this->ellipse_height;
}
