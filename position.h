#ifndef POSITION_H
#define POSITION_H


#include <QtMath>
#include <QRect>
#include <QTimer>

class position
{

public:

    position();
    float m_x = 0;
    float m_y = 0;
    float m_speed = 0;
    int m_xrange_l = 0;
    int m_xrange_r = 1200;
    int m_yrange_t = 0;
    int m_yrange_b = 800;
    int shield;
    int fullshield;
    int blood;
    int fullblood;
    QRect m_Rect;
    float E_distance(position p2);
    int M_distance(position p2);
    //float angle(position p2);
    enum orientation{up,down,left,right};


};

#endif // POSITION_H
