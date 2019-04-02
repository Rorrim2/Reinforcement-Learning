#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QPainter>
#include <QkeyEvent>
#include "point_t.h"
#include "dot_t.h"

using namespace std;

struct state_and_flag_of_terminal {
  int x;
  int y;
  int flag;
};

namespace Ui {
class MainWindow;
}

enum Direction {
    UP =  0,
    RIGHT,
    DOWN,
    LEFT
};

enum Field {
    NOTHING = 0,
    WALL,
    START,
    FINISH
};


class MainWindow : public QMainWindow {
    Q_OBJECT
    map<Point_t, vector<float>> map_of_points;
    int EPSILON = 9;
    int NUMBER_OF_EPISODES = 1000;
    float GAMMA = 0.9;
    float ALPHA = 0.1;
    Dot_t player;
public:
    int tab[12][15] {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
        {2, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 3},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    explicit MainWindow(QWidget *parent = nullptr);
    Direction choose_action(map<Point_t, vector<float>> &map_of_points, int x, int y);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    Direction find_max(map<Point_t, vector<float>> &map_of_points, int x, int y);
    float sum_this_shit(map<Point_t, vector<float>> &map_of_points, int x, int y);
    Field can_go_there(Direction action, int x, int y);
    state_and_flag_of_terminal move_the_dot(int x, int y, Direction action, state_and_flag_of_terminal st);
    void update_env(Direction action, int episode, int step_counter);
    void func_that_does_everything();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
