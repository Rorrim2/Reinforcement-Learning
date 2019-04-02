#include "dot_t.h"
#include "mainwindow.h"

Dot_t::Dot_t() {
    this->x = 0;
    this->y = 2;
    this->width = 15;
    this->height = 12;
    this->ellipse_width = 40;
    this->ellipse_height = 40;
    this->step = 1;
}

Dot_t::Dot_t(int width, int height) {
    this->x = 0;
    this->y = 0;
    this->width = width;
    this->height = height;
    this->ellipse_width = 40;
    this->ellipse_height = 40;
    this->step = 40;
}

void Dot_t::move_left() {
    if(this->x == 0) {
        return;
    }
    this->x -= 1;
}
void Dot_t::move_right() {
    if(this->x == this->width - 1) {
        return;
    }
    this->x += 1;
}
void Dot_t::move_up() {
    if(this->y == 0) {
        return;
    }
    this->y -= 1;
}
void Dot_t::move_down() {
    if(this->y == this->height - 1) {
        return;
    }
    this->y += 1;
}
int Dot_t::get_x() const {
    return this->x;
}
int Dot_t::get_y() const {
    return this->y;
}
int Dot_t::get_ellipse_width() const {
    return this->ellipse_width;
}
void Dot_t::move_to_position(int x, int y) {
    this->x = x;
    this->y = y;
}
int Dot_t::get_ellipse_height() const {
    return this->ellipse_height;
}


