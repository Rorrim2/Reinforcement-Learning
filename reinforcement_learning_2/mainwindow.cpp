#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QString>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <string>
#include <sstream>

#include "dot_t.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(0));
    ui->setupUi(this);
    for(int x = 0; x < 15; ++x) {
        for(int y = 0; y < 12; ++y) {
            map_of_points[Point_t(x, y, 40, 40)] = vector<float>(4, 0);
        }
    }
}

Field MainWindow::can_go_there(Direction action, int x, int y) {
    if(action == UP) {
        return (Field)this->tab[y - 1][x];
    }
    else if(action == RIGHT) {
        return (Field)this->tab[y][x + 1];
    }
    else if(action == DOWN) {
        return (Field)this->tab[y + 1][x];
    }
    else if(action == LEFT) {
        if(x == 0) {
            return WALL;
        }
        return (Field)this->tab[y][x - 1];
    }
    return WALL;
}
void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter paint(this);
    int i = 0;
    int j = 0;
    paint.setBrush(Qt::white);
    for(i = 0; i < 12; ++i) {
        for(j = 0; j < 15; ++j) {
            if(tab[i][j] == 0) {
                paint.drawRect(40*j, 40*i, 40, 40);
            }
        }
    }
    paint.setBrush(Qt::black);
    for(i = 0; i < 12; ++i) {
        for(j = 0; j < 15; ++j) {
            if(tab[i][j] == 1) {
                paint.drawRect(40*j, 40*i, 40, 40);
            }
        }
    }
    paint.setBrush(Qt::blue);
    paint.drawEllipse(player.get_x() * 40, player.get_y() * 40, 40, 40);
    cout << "x " << player.get_x() * 40 << " " << "y " << player.get_y() * 40 << " ";
    Point_t temp_point_2(player.get_x(), player.get_y(), 40, 40);
    for(int i = 0; i < 4; ++i) {
        cout << map_of_points[temp_point_2][i] << " ";
    }
    cout << endl;
    if(player.get_x() == 11 && player.get_y() == 1) {
        cout << "cokolwiek" << endl;
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event) {

    switch(event->key()) {
        case Qt::Key_S:
        {
            func_that_does_everything();
            break;
        }
    default: break;
    }
}

Direction MainWindow::find_max(map<Point_t, vector<float>> &map_of_points, int x, int y) {
    Point_t temp(x, y, 40, 40);
    vector<float>temp_vector = map_of_points[temp];
    float max = temp_vector[0];
    int max_index = 0;
    for(int i = 1; i < (int)temp_vector.size(); ++i) {
        if(max < temp_vector[i]) {
            max = temp_vector[i];
            max_index = i;
        }
        else if(max == temp_vector[i]) {
            if(rand()%100 < 50) {
                max_index = i;
            }
        }
    }
    return (Direction)max_index;
}

float MainWindow::sum_this_shit(map<Point_t, vector<float>> &map_of_points, int x, int y) {
    Point_t temp(x, y, 40, 40);
    vector<float>temp_vector = map_of_points[temp];
    float sum = 0.f;
    for(unsigned int i = 0; i < (unsigned int)temp_vector.size(); ++i) {
        sum += temp_vector[i];
    }
    return sum;
}

Direction MainWindow::choose_action(map<Point_t, vector<float>> &map_of_points, int x, int y) {
    Direction a = UP;
    Direction max = find_max(map_of_points, x, y);
    if(sum_this_shit(map_of_points, x, y) == 0.f || rand()%11 > EPSILON) {
        int x = rand()%100;
        a = (Direction)(x / 25);
    }
    else {
        a = max;
    }
    return a;
}

state_and_flag_of_terminal MainWindow::move_the_dot(int x, int y, Direction action, state_and_flag_of_terminal st) {
    //update();
    //repaint();
    Field temp;
    st.flag = 0;
    switch(action) {
        case UP:
        {
            temp = can_go_there(action, player.get_x(), player.get_y());
            st.flag = -1;
            if(temp == NOTHING) {
                player.move_up();
                st.y = y - 1;
                st.x = x;
            }
            else {
                st.flag = -100;
                st.y = y;
                st.x = x;
            }
            break;
        }
        case RIGHT:
        {
            temp = can_go_there(action, player.get_x(), player.get_y());
            st.flag = -1;
            if(temp == FINISH) {
                st.flag = 1000;
                st.x = x + 1;
                st.y = y; //czy x i y nie są na odwrót?
                player.move_right();
            }
            else if (temp == NOTHING) {
                player.move_right();
                st.y = y;
                st.x = x + 1;
            }
            else {
                st.flag = -100;
                st.y = y;
                st.x = x;
            }
            break;
        }
        case DOWN:
        {
            temp = can_go_there(action, player.get_x(), player.get_y());
            st.flag = -1;
            if(temp == NOTHING) {
                player.move_down();
                st.y = y + 1;
                st.x = x;
            }
            else {
                st.flag = -100;
                st.y = y;
                st.x = x;
            }
            break;
        }
        case LEFT:
        {
            temp = can_go_there(action, player.get_x(), player.get_y());
            st.flag = -1;
            if(temp == NOTHING) {
                player.move_left();
                st.y = y;
                st.x = x - 1;
            }
            else {
                st.flag = -100;
                st.y = y;
                st.x = x;
            }
            break;
        }
    }
    return st;
}

void MainWindow::update_env(Direction action, int episode, int step_counter) {
    repaint();
    //player->move_with_the_position(state);
    stringstream ss;
    ss << "Episode: " << episode << endl;
    string s = ss.str();
    ui->label->setText(QString(s.c_str()));
    ss.clear();
    ss << "Step_counter: " << step_counter << endl;
    s = ss.str();
    ui->label->setText(QString(s.c_str()));
    ss.clear();

    /*tu by można coś wypisać jeśli się skończy*/
    unsigned int time1 = GetTickCount();
    bool is_over = 1;
    while(is_over) {
        if(GetTickCount() - time1 > 10) {
            is_over = 0;
        }
    }
}

void MainWindow::func_that_does_everything() {
    for(int episode = 0; episode < NUMBER_OF_EPISODES; episode++) {
        int state_x = 0;
        int state_y = 2;
        int step_counter = 0;
        bool is_not_terminated = true;
        Direction action = LEFT;
        float q_predict;
        float q_target;
        state_and_flag_of_terminal safot;
        safot.x = 0;
        safot.y = 2;
        safot.flag = 0;
        player.move_to_position(state_x, state_y);
        while(is_not_terminated) {
            action = choose_action(map_of_points, state_x, state_y);
            safot = move_the_dot(state_x, state_y, action, safot);
            //cout << "x: " << player.get_x() << endl;
            Point_t temp_point(state_x, state_y, 40, 40);
            q_predict = map_of_points[temp_point][(int)action];
            //tu jestem
            if(safot.flag != 1000 && safot.flag != -100) {
                Direction temp_action = find_max(map_of_points, safot.x, safot.y);
                Point_t temp_point_2(safot.x, safot.y, 40, 40);
                float max = map_of_points[temp_point_2][(int)temp_action];
                q_target = safot.flag + GAMMA * max;
            }
            else {
                q_target = safot.flag;
                is_not_terminated = false;
                update_env(action, episode + 1, step_counter + 1);
            }
            map_of_points[temp_point][(int)action] = ALPHA * (q_target - q_predict);
            state_x = safot.x;
            state_y = safot.y;
            update_env(action, episode + 1, step_counter + 1);
            step_counter += 1;
        }
        unsigned int time1 = GetTickCount();
        bool is_over = 1;
        while(is_over) {
            if(GetTickCount() - time1 > 1000) {
                is_over = 0;
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
//odwołanie do opowiedniej komórki vectora w mapie + label
