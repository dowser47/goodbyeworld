#ifndef BULLET_H
#define BULLET_H
#include "position.h"

class bullet: public position
{
public:
    bullet();
    bool m_free = 1;
    int target_x;
    int target_y;
    int m_x0;
    int m_y0;
    int m_height = 10;
    int m_width = 10;
    float x;
    float y;
    float d;
    float sin;
    float cos;
    void aim();//计算弹道
    void fly();//让子弹飞
};

#endif // BULLET_H
