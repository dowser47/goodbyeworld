#include "monster1.h"

monster1::monster1(){}

void monster1::attack(position &p1)
{
    isattacking = true;
    connect(&m_timer,&QTimer::timeout,[&](){
        if(isattacking == false)
            disconnect(&m_timer,&QTimer::timeout,0,0);
        if(d<attackrad)
        {
            magazine[which_bullet].target_x = p1.m_x;
            magazine[which_bullet].target_y = p1.m_y;
            this->shoot(which_bullet);
            which_bullet++;
            if(which_bullet == 10)
                which_bullet = 0;
        }
        else
        {
            m_timer.stop();
            isattacking = false;
            disconnect(&m_timer,&QTimer::timeout,0,0);
        }
    });
    m_timer.start(attackrate);
}
void monster1::shoot(int i)
{
    magazine[i].m_free = false;
    magazine[i].m_x = m_x;
    magazine[i].m_y = m_y;
    magazine[i].m_speed = m_bspeed;
    magazine[i].m_Rect.setRect(m_x,m_y,magazine[i].m_width,magazine[i].m_height);
    magazine[i].aim();
}

