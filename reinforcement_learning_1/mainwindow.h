#ifndef MAINWINDOW_T_H
#define MAINWINDOW_T_H

#include <QMainWindow>
#include <QkeyEvent>
#include "dot_t.h"

struct state_and_flag_of_terminal {
  int current_state;
  int flag;
};
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    Dot_t *player;
    int EPSILON = 9;
    int NUMBER_OF_EPISODES = 13;
    int lenght_of_the_way = 6;
    float GAMMA = 0.9;
    float ALPHA = 0.1;

public:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* event);
    int choose_action(float* table, int state);
    struct state_and_flag_of_terminal move_the_dot(int state, int action, state_and_flag_of_terminal st);
    void update_env(int action, int state,int episode,int step_counter);
    void func_that_does_everything();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif

