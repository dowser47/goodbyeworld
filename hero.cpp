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
            if(m_y>(m_yrange_t+h_height/2))
                m_y-=m_speed*0.707;

            if(m_x>m_xrange_l+h_width/2)
                m_x-=m_speed*0.707;
        }

        else if(m_isright == 1)
        {
            if(m_y>m_yrange_t+h_height/2)
                m_y-=m_speed*0.707;

            if(m_x<m_xrange_r-h_width/2)
                m_x+=m_speed*0.707;
        }

        else
        {
            if(m_y>(m_yrange_t+h_width/2))
                m_y-=m_speed;

        }
    }
    else if (m_isdown == 1)
    {
        if(m_isleft == 1)
        {
            if(m_y<m_yrange_b-h_height/2)
                m_y+=m_speed*0.707;

            if(m_x>m_xrange_l+h_height/2)
                m_x-=m_speed*0.707;
        }

        else if(m_isright == 1)
        {
            if(m_y<m_yrange_b-h_height/2)
                m_y+=m_speed*0.707;

            if(m_x<m_xrange_r-h_width/2)
                m_x+=m_speed*0.707;
        }

        else
        {
            if(m_y<m_yrange_b-h_height/2)
                m_y+=m_speed;

        }
    }
    else if (m_isleft == 1)
    {
        if(m_isup == 1)
        {
            if(m_y>(m_yrange_t+h_width/2))
                m_y-=m_speed*0.707;

            if(m_x>m_xrange_l+h_height/2)
                m_x-=m_speed*0.707;
        }

        else if(m_isdown == 1)
        {
            if(m_y<m_yrange_b-h_height/2)
                m_y+=m_speed*0.707;

            if(m_x>m_xrange_l+h_height/2)
                m_x-=m_speed*0.707;
        }

        else
        {
            if(m_x>m_xrange_l+h_height/2)
                m_x-=m_speed;

        }
    }
    else if (m_isright == 1)
    {
        if(m_isup == 1)
        {
            if(m_y>(m_yrange_t+h_width/2))
                m_y-=m_speed*0.707;

            if(m_x<m_xrange_r-h_width/2)
                m_x+=m_speed*0.707;
        }

        else if(m_isdown == 1)
        {
            if(m_y<m_yrange_b-h_height/2)
                m_y+=m_speed*0.707;

            if(m_x<m_xrange_r-h_width/2)
                m_x+=m_speed*0.707;
        }

        else
        {
            if(m_x<m_xrange_r-h_width/2)
                m_x+=m_speed;

        }
    }
}

void hero::shoot(int i)
{

        magazine[i].m_free = false;
        magazine[i].m_x0 = m_x;
        magazine[i].m_y0 = m_y;
        magazine[i].m_x = m_x;
        magazine[i].m_y = m_y;
        magazine[i].m_speed = h_bspeed;
        magazine[i].m_Rect.setRect(m_x,m_y,magazine[i].m_width,magazine[i].m_height);
        magazine[i].aim();
}

void hero::recover0()
{
    if(m_recover.isActive())
        disconnect(&m_recover,&QTimer::timeout,0,0);
    connect(&m_recover,&QTimer::timeout,[=](){
        disconnect(&m_recover,&QTimer::timeout,0,0);
        recover1();
    });
    m_recover.start(m_beganrecover);

    qDebug()<<shield<<' '<<blood;
}

void hero::recover1()
{
    connect(&m_recover,&QTimer::timeout,[=](){
        if(shield < fullshield)
            shield++;
        else
            disconnect(&m_recover,&QTimer::timeout,0,0);
        qDebug()<<shield<<' '<<blood;
    });
    m_recover.start(m_recoverrate);

}

