#include "hero.h"

hero::hero(QWidget *parent)
    : QWidget{parent}
{

}

void hero::movement()
{
    if (m_isup == 1)
    {
        if(m_isleft == 1)
        {
            if(m_tot == false)
                m_y-=m_speed*0.707;

            if(m_tol == false)
                m_x-=m_speed*0.707;
        }

        else if(m_isright == 1)
        {
            if(m_tot == false)
                m_y-=m_speed*0.707;

            if(m_tor == false)
                m_x+=m_speed*0.707;
        }

        else
        {
            if(m_tot == false)
                m_y-=m_speed;

        }
    }
    else if (m_isdown == 1)
    {
        if(m_isleft == 1)
        {
            if(m_tob == false)
                m_y+=m_speed*0.707;

            if(m_tol == false)
                m_x-=m_speed*0.707;
        }

        else if(m_isright == 1)
        {
            if(m_tob == false)
                m_y+=m_speed*0.707;

            if(m_tor == false)
                m_x+=m_speed*0.707;
        }

        else
        {
            if(m_tob == false)
                m_y+=m_speed;

        }
    }
    else if (m_isleft == 1)
    {
        if(m_isup == 1)
        {
            if(m_tot == false)
                m_y-=m_speed*0.707;

            if(m_tol == false)
                m_x-=m_speed*0.707;
        }

        else if(m_isdown == 1)
        {
            if(m_tob == false)
                m_y+=m_speed*0.707;

            if(m_tol == false)
                m_x-=m_speed*0.707;
        }

        else
        {
            if(m_tol == false)
                m_x-=m_speed;

        }
    }
    else if (m_isright == 1)
    {
        if(m_isup == 1)
        {
            if(m_tot == false)
                m_y-=m_speed*0.707;

            if(m_tor == false)
                m_x+=m_speed*0.707;
        }

        else if(m_isdown == 1)
        {
            if(m_tob == false)
                m_y+=m_speed*0.707;

            if(m_tor == false)
                m_x+=m_speed*0.707;
        }

        else
        {
            if(m_tor == false)
                m_x+=m_speed;

        }
    }
}

void hero::shoot(int i)
{

        magazine[i].m_free = false;
        magazine[i].m_x = m_x;
        magazine[i].m_y = m_y;
        magazine[i].m_speed = h_bspeed;
        magazine[i].m_Rect.setRect(m_x,m_y,magazine[i].m_width,magazine[i].m_height);
        magazine[i].aim();
}

void hero::recover0()
{
    m_Rect.setWidth(0);
    m_Rect.setHeight(0);
    connect(&m_protect,&QTimer::timeout,[=](){
        m_Rect.setWidth(h_width);
        m_Rect.setHeight(h_height);
        disconnect(&m_protect,&QTimer::timeout,0,0);
    });
    m_protect.start(m_protlen);
    if(m_recover.isActive())
        disconnect(&m_recover,&QTimer::timeout,0,0);
    connect(&m_recover,&QTimer::timeout,[=](){
        disconnect(&m_recover,&QTimer::timeout,0,0);
        recover1();
    });
    m_recover.start(m_beganrecover);

    // qDebug()<<shield<<' '<<blood;
}

void hero::recover1()
{
    connect(&m_recover,&QTimer::timeout,[=](){
        if(shield < fullshield)
            shield++;
        else
            disconnect(&m_recover,&QTimer::timeout,0,0);
    });
    m_recover.start(m_recoverrate);

}

void hero::rangecheck()
{
    if(m_x>=(m_xrange_r-h_width/2))
    {
        m_tor = true;
        m_tol = false;
    }
    else if(m_x<=(m_xrange_l+h_width/2))
    {
        m_tor = false;
        m_tol = true;
    }
    else
    {
        m_tor = false;
        m_tol = false;
    }
    if(m_y<=(m_yrange_t+h_width/2))
    {
        m_tot = true;
        m_tob = false;
    }
    else if(m_y>=(m_yrange_b-h_width/2))
    {
        m_tot = false;
        m_tob = true;
    }
    else
    {
        m_tot = false;
        m_tob = false;
    }

}

void hero::skill()
{
    m_skillon = true;
    disconnect(&m_skill,&QTimer::timeout,0,0);
    m_firespeed *= 0.5;
    if(m_timer.isActive())
        m_timer.start(m_firespeed);
    connect(&m_skill,&QTimer::timeout,[=](){
        m_skillon = false;
        m_firespeed /= 0.5;
        if(m_timer.isActive())
            m_timer.start(m_firespeed);
        disconnect(&m_skill,&QTimer::timeout,0,0);
        m_skill.start(m_skillrate);
        m_skillready = false;
        connect(&m_skill,&QTimer::timeout,[&](){
            if(m_skillready == false)
                m_skillready = true;
        });
    });
    m_skill.start(m_skillstop);   
}

