#ifndef POINT_T_H
#define POINT_T_H


class Point_t {
    int x;
    int y;
    int rect_width;
    int rect_height;
public:
    Point_t():x(0), y(0), rect_width(0), rect_height(0){}
    Point_t(int x, int y, int width, int height):x(x), y(y), rect_width(width), rect_height(height){}
    int get_x() const;
    int get_y() const;
    int get_width() const;
    int get_height() const;
    bool operator>(const Point_t& p) const;
    bool operator<(const Point_t& p) const;
};

#endif // POINT_T_H
