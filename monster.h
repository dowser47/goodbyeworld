#ifndef MONSTER_H
#define MONSTER_H

#include <QWidget>
#include <QRect>
#include "position.h"
#include "bullet.h"
#include <QDebug>
#include "weapon.h"

class monster : public QWidget, public position
{
    Q_OBJECT
public:
    explicit monster(QWidget *parent = nullptr);
    void track0(position &p1);
    void track1();
    virtual void attack(position & p1);
    virtual void shoot(int i);
    int m_height=100;
    int m_width=100;
    int m_free = 0;
    int power =1;
    float attackrad = 200;
    int attackrate = 2000;
    float sightrange = 500;
    int m_bspeed = 6;
    bool isattacking = false;
    bool istracking = false;
    float x;
    float y;
    float d;
    float sin;
    float cos;
    bullet m_bullet0;
    bullet m_bullet1;
    weapon m_weapon;

    QTimer m_timer;
    QPixmap m_image;
    QPixmap m_image0;

    int test = 0;
signals:
    void harm();
};

#endif // MONSTER_H
