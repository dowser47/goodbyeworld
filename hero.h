#ifndef HERO_H
#define HERO_H


#include <QWidget>
#include <QKeyEvent>
#include <QRect>

#include "position.h"
#include "bullet.h"
#include "weapon.h"
class hero : public QWidget, public position
{
    Q_OBJECT
public:
    explicit hero(QWidget *parent = nullptr);


    int h_height=100;
    int h_width=100;
    int h_bspeed=20;
    bool orientation = 1;
    bool m_isup =0;
    bool m_isdown =0;
    bool m_isleft =0;
    bool m_isright =0;
    bool m_tot;
    bool m_tob;
    bool m_tol;
    bool m_tor;
    bool m_skillready;
    int m_firespeed = 100;
    int m_beganrecover = 5000;
    int m_recoverrate = 2000;
    int m_skillrate = 10000;
    int m_skillstop = 5000;
    int m_whichbullet = 0;
    int m_power = 10;
    // QPixmap m_image;
    QImage m_image;
    QImage m_image1;
    QTimer m_timer;
    QTimer m_recover;
    QTimer m_skill;
    bullet magazine[50];
    weapon m_weapon;
    void movement();
    void shoot(int i);
    void recover0();
    void recover1();
    void rangecheck();
    void skill();

signals:
    void beattacked();
};

#endif // HERO_H
