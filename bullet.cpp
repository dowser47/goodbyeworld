#include "bullet.h"

bullet::bullet(QWidget *parent)
    : QWidget{parent}
{
    m_image.load(":/image/resource/bullet0.png");
}

void bullet::aim()
{
    x = target_x - m_x0;
    y = target_y - m_y0;
    d = sqrt(x*x + y*y);
    sin = y/d;
    cos = x/d;
}

void bullet::fly()
{

    m_x += m_speed * cos;
    m_y += m_speed * sin;
    m_Rect.moveTo(m_x, m_y);
}
