#ifndef MONSTER1_H
#define MONSTER1_H

#include <QWidget>
#include <QTimer>
#include "monster.h"

class monster1 : public monster
{
    Q_OBJECT
public:
    monster1();
    int which_bullet = 0;
    int runawayrange = 200;
    bullet magazine[10];
    virtual void attack(position & p1);
    void shoot(int i);
signals:
};

#endif // MONSTER1_H
