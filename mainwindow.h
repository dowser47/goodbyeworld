#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QMouseEvent>
#include "hero.h"
#include "monster.h"
#include "monster1.h"
#include "sight.h"
#include "boss.h"
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

    int m_x_size = 1200;
    int m_y_size = 800;
    int m_mapx;
    int m_mapy;
    int m_mapwidth;
    int m_mapheight;
    int m_monsnum;
    int m_monsnum1;
    int m_bossnum;
    int m_alivenum;
    int fullflour = 2;
    int currflour = 0;
    bool currflourwin = 0;
    hero m_hero;
    monster m_monster;
    monster m_monsters[20];
    monster1 m_monsters1[20];
    boss m_boss;
    sight sig;
    float orient[2][8]={{0,0.707,1,0.707,0,-0.707,-1,-0.707},{1,0.707,0,-0.707,-1,-0.707,0,0.707}};
    int temp_orient;
    int pnum;
    position *positions[500];
    int test=0;
    QTimer timer;
    QTimer timer0;
    QPointF mpos;
    QRandomGenerator m_rand;
    QPixmap sigimage0;
    QPixmap sigimage1;
    QCursor sigcursor0;
    QCursor sigcursor1;
    QPixmap map;
    QPixmap door;
    QPixmap blood;
    QPixmap shield;
    QFont font;
    QPen pen;

    void creatworld(int cf = 0);
    void sethero();
    void setmonster();
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void setscene();
    void collisionproof();//防止怪物相互重叠
    void shotcheck();//怪物是否中弹
    void deathcheck();//怪物是否死亡
    void attackcheck();//怪物是否发动攻击
    void othersmove();//为了保证人物在屏幕较中心区域移动，当人物到达一定范围时，人物不动，让地图、怪物、子弹相对人物运动   

signals:
    void gameover();
    void gamecontinue();
    void gamewin();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
