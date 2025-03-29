#ifndef MONSTER_H
#define MONSTER_H

#include <QWidget>
#include <QRect>
#include "position.h"

#include <QDebug>

class monster : public QWidget, public position
{
    Q_OBJECT
public:
    explicit monster(QWidget *parent = nullptr);
    void track0(position p1);
    void track1();
    void attack(position & p1);

    int m_height=50;
    int m_width=50;
    int m_free = 0;
    int power =1;
    float attackrad = 50;
    int attackrate = 500;
    float sightrange = 400;
    bool isattacking = 0;
    bool istracking = 0;
    float x;
    float y;
    float d;
    float sin;
    float cos;
    QTimer m_timer;
    QPixmap m_image;

    int test = 0;
signals:
    void harm();
};

#endif // MONSTER_H
