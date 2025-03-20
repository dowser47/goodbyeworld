#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QMouseEvent>
#include "hero.h"
#include "monster.h"
#include "sight.h"
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void sethero();
    void setmonster();
    int m_x_size = 1200;
    int m_y_size = 800;
    int m_monsnum = 10;
    QTimer timer;
    QTimer timer0;
    QPoint mpos;
    QRandomGenerator m_rand;
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void setscene();
    void collisionproof();
    void shotcheck();
    void deathcheck();
    void attackcheck();

    hero m_hero;
    monster m_monster;
    monster m_monsters[20];
    sight sig;
    float orient[2][8]={{0,0.707,1,0.707,0,-0.707,-1,-0.707},{1,0.707,0,-0.707,-1,-0.707,0,0.707}};
    int temp_orient;

    int test=0;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
