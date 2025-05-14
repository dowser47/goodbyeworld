#include "monster.h"

monster::monster(QWidget *parent)
    : QWidget{parent}
{}

void monster::track0(position &p1)
{
    x = p1.m_x - this->m_x;
    y = p1.m_y - this->m_y;
    d = sqrt(x * x + y * y);
    if(d>0)
    {
        sin = y/d;
        cos = x/d;
    }
}

void monster::track1()
{
    //在地图中则行动，触碰到边界时改变方向
    if(m_y>=(m_yrange_t+m_height/2) && m_y<=(m_yrange_b-m_height/2))
    {
        m_y += m_speed * sin;
    }
    else if(m_y<(m_yrange_t+m_height/2))
    {
        m_y = m_yrange_t+m_height/2;
        sin *= -1;
    }
    else
    {
        m_y = m_yrange_b-m_height/2;
        sin *= -1;
    }
    if(m_x>=(m_xrange_l+m_width/2) && m_x<=(m_xrange_r-m_width/2))
    {
        m_x += m_speed * cos;
    }
    else if(m_x<(m_xrange_l+m_width/2))
    {
        m_x = m_xrange_l+m_width/2;
        cos *= -1;
    }
    else
    {
        m_x = m_xrange_r-m_width/2;
        cos *= -1;
    }
    m_Rect.moveTo(m_x - 0.5 * m_width,m_y - 0.5 * m_height);

}



void monster::attack(position & p1)
{
    isattacking = true;
    connect(&m_timer,&QTimer::timeout,[&](){
        if(isattacking == false)
            disconnect(&m_timer,&QTimer::timeout,0,0);
        if(d<attackrad)
        {
            m_bullet0.target_x = p1.m_x;
            m_bullet0.target_y = p1.m_y;
            m_bullet1.target_x = p1.m_x;
            m_bullet1.target_y = p1.m_y;
            if(x > 0)
                this->shoot(0);
            else
                this->shoot(1);
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

void monster::shoot(int i)
{
    if(i == 0)
    {
        m_bullet0.m_free = false;
        m_bullet0.m_x = m_x;
        m_bullet0.m_y = m_y;
        m_bullet0.m_speed = m_bspeed;
        m_bullet0.m_Rect.setRect(m_x,m_y,m_bullet0.m_width,m_bullet0.m_height);
        m_bullet0.aim();
    }
    else
    {
        m_bullet1.m_free = false;
        m_bullet1.m_x = m_x;
        m_bullet1.m_y = m_y;
        m_bullet1.m_speed = m_bspeed;
        m_bullet1.m_Rect.setRect(m_x,m_y,m_bullet1.m_width,m_bullet1.m_height);
        m_bullet1.aim();
    }
}




