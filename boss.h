#ifndef BOSS_H
#define BOSS_H
#include "monster.h"


class boss: public monster
{
public:
    boss();
    int which_bullet = 0;
    int m_currspeed;
    int m_racespeed;
    int m_bulletnum = 25;

    bullet magazine[25];
    bullet m_body;
    QTimer m_attacktimer0;
    QTimer m_attacktimer1;
    void shoot(int i);
    void attack0();
    void attack1(position &p);
signals:

};

#endif // BOSS_H
