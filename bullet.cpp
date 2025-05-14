#include "bullet.h"

bullet::bullet(QWidget *parent)
    : QWidget{parent}
{

}

void bullet::aim()
{
    sin = (target_y - m_y)/sqrt((target_x - m_x)*(target_x - m_x) + (target_y - m_y)*(target_y - m_y));
    cos = (target_x - m_x)/sqrt((target_x - m_x)*(target_x - m_x) + (target_y - m_y)*(target_y - m_y));
}

void bullet::fly()
{
    m_x += m_speed * cos;
    m_y += m_speed * sin;
    m_Rect.moveTo(m_x - 0.5 * m_width,m_y - 0.5 * m_height);
}
