#ifndef DOT_T_H
#define DOT_T_H


class Dot_t {
    int x;
    int number_of_cells;
    int ellipse_width;
    int ellipse_height;
    int step;
    int position;
public:
    Dot_t();
    Dot_t(int number);
    void move_left();
    void move_right();
    int get_x() const;
    int get_ellipse_width() const;
    void move_with_the_position(int state);
    int get_ellipse_height() const;
};

#endif // DOT_T_H
