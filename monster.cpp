#include "monster.h"

monster::monster(QObject *parent)
    : QObject{parent}
{}

void monster::track0(position p1)
{
    x = p1.m_x - this->m_x;
    y = p1.m_y - this->m_y;
    d = sqrt(x * x + y * y);
    if(d>0)
    {
        sin = y/d;
        cos = x/d;
        // m_x += m_speed * cos;
        // m_y += m_speed * sin;
    }
}

void monster::track1()
{

    //if(m_y>(m_yrange_t+m_height/2) && m_y<(m_yrange_b-m_height/2))
    m_y += m_speed * sin;
    //if(m_x>(m_xrange_l+m_width/2) && m_x<(m_xrange_r-m_width/2))
    m_x += m_speed * cos;
    if(m_y<(m_yrange_t+m_height/2))
        m_y=(m_yrange_t+m_height/2);
    else if(m_y>(m_yrange_b-m_height/2))
        m_y=(m_yrange_b-m_height/2);
    if(m_x<(m_xrange_l+m_width/2))
        m_x=(m_xrange_l+m_width/2);
    else if(m_x>(m_xrange_r-m_width/2))
        m_x=(m_xrange_r-m_width/2);
    m_Rect.moveTo(m_x,m_y);
}



void monster::attack(position & p1)
{
    isattacking = true;
    m_speed *= 0.5;
    connect(&m_timer, &QTimer::timeout, [&](){
        m_timer.stop();
        if(d > attackrad)
        {
            isattacking = false;
            m_speed *= 2;
            disconnect(&m_timer, &QTimer::timeout, nullptr, nullptr);

            return;
        }
        if(p1.shield>0)
        {
            if(p1.shield >= power)
                p1.shield -= power;
            else
            {
                p1.shield = 0;
                p1.blood -=(power - p1.shield);
            }
        }
        else
        {
            p1.blood -= power;

        }
        isattacking = false;
        m_speed *= 2;
        emit harm();
        disconnect(&m_timer, &QTimer::timeout, nullptr, nullptr);

    });
    m_timer.start(attackrate);

}




