#ifndef DOT_T_H
#define DOT_T_H


class Dot_t {
    int x;
    int y;
    int width;
    int height;
    int ellipse_width;
    int ellipse_height;
    int step;
public:
    Dot_t();
    Dot_t(int width, int height);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    int get_x() const;
    int get_y() const;
    int get_ellipse_width() const;
    void move_to_position(int x, int y);
    int get_ellipse_height() const;
};

#endif // DOT_T_H
