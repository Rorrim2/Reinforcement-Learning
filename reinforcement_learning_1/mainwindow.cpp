#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dot_t.h"

#include <QPainter>
#include <QString>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <sstream>
#include <string>

#define LEFT 0
#define RIGHT 1

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(0));
    ui->setupUi(this);
    player = new Dot_t();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter paint(this);
    paint.setPen(Qt::black);
    paint.drawRect(0, 0, 40, 40);
    paint.drawRect(40, 0, 40, 40);
    paint.drawRect(80, 0, 40, 40);
    paint.drawRect(120, 0, 40, 40);
    paint.drawRect(160, 0, 40, 40);
    paint.drawRect(200, 0, 40, 40);
    paint.setBrush(Qt::blue);
    paint.drawEllipse(player->get_x(), 0, player->get_ellipse_height(), player->get_ellipse_width());


}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    switch(event->key()) {
        case Qt::Key_S:
        {
            func_that_does_everything();
            break;
        }
        case Qt::Key_E:
        {
            return;
            break;
        }
    }
}

int MainWindow::choose_action(float* table, int state) {
    int a = -1;
    int max = -1;
    if(*(table + state * 2) > *(table + state * 2 + 1)) {
        max = LEFT;
    }
    else {
        max = RIGHT;
    }
    if(*(table + state * 2) + *(table + state * 2 + 1) == 0.f || rand()%11 > EPSILON) {
        int x = rand()%100;
        if(x < 50) {
            a = 1;
        }
        else {
            a = 0;
        }
    }
    else {
        a = max;
    }
    return a;

}

state_and_flag_of_terminal MainWindow::move_the_dot(int state, int action, state_and_flag_of_terminal st) {
    //update();
    //repaint();
    if(action == RIGHT) {
        //player->move_right();

        if(state == lenght_of_the_way - 2) {
            st.current_state = lenght_of_the_way - 1;
            st.flag = 1;
        }
        else {
            st.current_state = state + 1;
            st.flag = 0;
        }
    }
    else {
        //player->move_left();
        st.flag = 0;
        if(state == 0) {
            st.current_state = state;
        }
        else {
            st.current_state = state - 1;
        }
    }
    return st;
}

void MainWindow::update_env(int action, int state,int episode,int step_counter) {
    repaint();
    player->move_with_the_position(state);
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
        if(GetTickCount() - time1 > 200) {
            is_over = 0;
        }
    }
}


void MainWindow::func_that_does_everything() {
    float table[6][2]; //zaalokuj to potem, żeby magicznych liczb nie było
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 2; ++j) {
            table[i][j] = 0.f;
        }
    }
    float* table_p = *table;
    for(int episode = 0; episode < NUMBER_OF_EPISODES; episode++) {
        int state = 0;
        int step_counter = 0;
        bool is_not_terminated = true;
        int action = -1;
        float q_predict;
        float q_target;
        state_and_flag_of_terminal safot;
        safot.current_state = 0;
        safot.flag = 1;
        player->move_with_the_position(0);
        while(is_not_terminated) {
            cout << state << endl;
            action = choose_action(table_p, state);
            safot = move_the_dot(state, action, safot);
            //cout << safot.current_state << endl;
            cout << "x: " << player->get_x() << endl;
            q_predict = table[state][action];
            if(safot.current_state != lenght_of_the_way - 1) {
                float max = table[safot.current_state][0];
                if(max < table[safot.current_state][1]) {
                    max = table[safot.current_state][1];
                }
                q_target = safot.flag + GAMMA * max;
            }
            else {
                q_target = safot.flag;
                is_not_terminated = false;
                cout << "JJEEESSSSTTT" << endl;
                update_env(action, safot.current_state, episode + 1, step_counter + 1);
            }
            table[state][action] += ALPHA * (q_target - q_predict);
            state = safot.current_state;
            update_env(action, state, episode + 1, step_counter + 1);
            step_counter += 1;

        }
        unsigned int time1 = GetTickCount();
        bool is_over = 1;
        while(is_over) {
            if(GetTickCount() - time1 > 2000) {
                is_over = 0;
            }
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
