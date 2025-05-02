#include "bullet.h"

bullet::bullet(QWidget *parent)
    : QWidget{parent}
{

}

void bullet::aim()
{
    x = target_x - m_x;
    y = target_y - m_y;
    d = sqrt(x*x + y*y);
    sin = y/d;
    cos = x/d;
}

void bullet::fly()
{
    m_x += m_speed * cos;
    m_y += m_speed * sin;
    m_Rect.moveTo(m_x - 0.5 * m_width,m_y - 0.5 * m_height);
}
