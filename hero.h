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


    int h_height=80;
    int h_width=80;
    int h_bspeed=20;
    bool orientation = 1;
    bool m_isup =0;
    bool m_isdown =0;
    bool m_isleft =0;
    bool m_isright =0;
    int m_firespeed = 100;
    int m_beganrecover = 5000;
    int m_recoverrate = 2000;
    int m_whichbullet = 0;
    // QPixmap m_image;
    QImage m_image;
    QTimer m_timer;
    QTimer m_recover;
    bullet magazine[50];
    weapon m_weapon;
    void movement();
    void shoot(int i);
    void recover0();
    void recover1();

signals:
    void beattacked();
};

#endif // HERO_H
