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
    m_y += m_speed * sin;
    m_x += m_speed * cos;
    if(m_y<(m_yrange_t+m_height/2) || m_y>(m_yrange_b-m_height/2))
    {
        sin *= -1;
        m_y += m_height/2 * sin;
    }
    if(m_x<(m_xrange_l+m_width/2) || m_x>(m_xrange_r-m_width/2))
    {
        cos *= -1;
        m_x += m_width/2 *cos;
    }
    m_Rect.moveTo(m_x - 0.5 * m_width,m_y - 0.5 * m_height);
    // if(m_y>=(m_yrange_t+m_height/2) && m_y<=(m_yrange_b-m_height/2))
    // {
    //     m_y += m_speed * sin;
    // }
    // else
    // {
    //     // sin *= -1;
    //     if(m_y<(m_yrange_t+m_height/2))
    //     {

    //         m_y=(m_yrange_t+m_height/2);
    //     }
    //     else
    //     {

    //         m_y=(m_yrange_b-m_height/2);
    //     }
    // }

    // if(m_x>=(m_xrange_l+m_width/2) && m_x<=(m_xrange_r-m_width/2))
    // {
    //     m_x += m_speed * cos;
    // }
    // else
    // {
    //     // cos *= -1;
    //     if(m_x<(m_xrange_l+m_width/2))
    //     {

    //         m_x=(m_xrange_l+m_width/2);
    //     }
    //     else
    //     {

    //         m_x=(m_xrange_r-m_width/2);
    //     }
    // }

    m_Rect.moveTo(m_x - 0.5 * m_width,m_y - 0.5 * m_height);
    qDebug()<<m_x<<m_y<<sin<<cos<<x<<y<<d;
}



void monster::attack(position & p1)
{
    // isattacking = true;
    // m_speed *= 0.5;
    // connect(&m_timer, &QTimer::timeout, [&](){
    //     m_timer.stop();
    //     if(d > attackrad)
    //     {
    //         isattacking = false;
    //         m_speed *= 2;
    //         disconnect(&m_timer, &QTimer::timeout, nullptr, nullptr);

    //         return;
    //     }
    //     if(p1.shield>0)
    //     {
    //         if(p1.shield >= power)
    //             p1.shield -= power;
    //         else
    //         {
    //             p1.shield = 0;
    //             p1.blood -=(power - p1.shield);
    //         }
    //     }
    //     else
    //     {
    //         p1.blood -= power;
    //     }
    //     isattacking = false;
    //     m_speed *= 2;
    //     emit harm();
    //     disconnect(&m_timer, &QTimer::timeout, nullptr, nullptr);

    // });
    // m_timer.start(attackrate);
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




