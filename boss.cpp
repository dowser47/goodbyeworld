#include "boss.h"
#include "math.h"

boss::boss() {}

void boss::shoot(int i)
{
    magazine[i].m_free = false;
    magazine[i].m_x = m_x;
    magazine[i].m_y = m_y;
    magazine[i].m_speed = m_bspeed;
    magazine[i].m_Rect.setRect(m_x,m_y,magazine[i].m_width,magazine[i].m_height);
    // magazine[i].aim();
}

void boss::attack0()
{
    float j = 0;
    for(int i = 0; i < 10; i++,which_bullet++)
    {

        magazine[which_bullet].sin = std::sin(j);
        magazine[which_bullet].cos = std::cos(j);
        // qDebug()<<magazine[which_bullet].sin<<magazine[which_bullet].cos ;
        this->shoot(which_bullet);
        if(which_bullet == m_bulletnum)
            which_bullet = 0;
        j += 0.628;
    }
}

void boss::attack1(position &p)
{
    disconnect(&m_timer,&QTimer::timeout,0,0);
    isattacking = true;
    connect(&m_timer,&QTimer::timeout,[&](){
        m_speed = m_racespeed;
        this->track0(p);
        m_body.m_free = false;
        m_body.m_x = m_x;
        m_body.m_y = m_y;
        m_body.m_speed = m_speed;
        m_body.m_Rect.setRect(m_x,m_y,m_width,m_height);
        isattacking = false;
        disconnect(&m_timer,&QTimer::timeout,0,0);
        m_attacktimer0.stop();

    });
    m_timer.start(2500);
    m_speed = 0;
}
