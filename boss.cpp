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
}

void boss::attack0()
{
    float j = 0;
    for(int i = 0; i < 6; i++)
    {
        for(int k = 0; k <3; k++)
        {
            magazine[which_bullet].sin = std::sin(j);
            magazine[which_bullet].cos = std::cos(j);
            this->shoot(which_bullet++);
            if(which_bullet == m_bulletnum)
                which_bullet = 0;
            j += 0.1744;
        }
        j += 0.5233;
    }
}


void boss::attack10(position &p)
{
    //若m和s1不在弹夹中，则回归弹夹
    for(int i = 0; i < bn_attack1_s1; i++)
    {
        magazine_attack1_s1[wb_attack1_m][i].m_free = true;
    }
    //发射m，记录此时m位置
    magazine_attack1_m[wb_attack1_m].m_free = false;
    magazine_attack1_m[wb_attack1_m].m_x = m_x;
    magazine_attack1_m[wb_attack1_m].m_y = m_y;
    attack1_m_p[wb_attack1_m][0]=m_x;
    attack1_m_p[wb_attack1_m][1]=m_y;
    magazine_attack1_m[wb_attack1_m].m_speed = m_bspeed;
    magazine_attack1_m[wb_attack1_m].m_Rect.setRect(m_x,m_y,
        magazine_attack1_m[wb_attack1_m].m_width,magazine_attack1_m[wb_attack1_m].m_height);
    magazine_attack1_m[wb_attack1_m].target_x = p.m_x;
    magazine_attack1_m[wb_attack1_m].target_y = p.m_y;
    magazine_attack1_m[wb_attack1_m].aim();
    //设置wb_attack1_m的s2的速度、方向
    for(int i = 0; i < bn_attack1_s1; i++)
    {
        for(int j = 0; j < bn_attack1_s2; j++)
        {
            magazine_attack1_s2[wb_attack1_m][i][j].m_speed = m_bspeed;
            magazine_attack1_s2[wb_attack1_m][i][j].m_Rect.setRect(m_x,m_y,
                magazine_attack1_s2[wb_attack1_m][0][0].m_width,magazine_attack1_s2[wb_attack1_m][0][0].m_height);
            magazine_attack1_s2[wb_attack1_m][i][j].sin = magazine_attack1_m[wb_attack1_m].cos;
            magazine_attack1_s2[wb_attack1_m][i][j++].cos = -magazine_attack1_m[wb_attack1_m].sin;
            magazine_attack1_s2[wb_attack1_m][i][j].m_speed = m_bspeed;
            magazine_attack1_s2[wb_attack1_m][i][j].m_Rect.setRect(m_x,m_y,
                magazine_attack1_s2[wb_attack1_m][0][0].m_width,magazine_attack1_s2[wb_attack1_m][0][0].m_height);
            magazine_attack1_s2[wb_attack1_m][i][j].sin = -magazine_attack1_m[wb_attack1_m].cos;
            magazine_attack1_s2[wb_attack1_m][i][j].cos = magazine_attack1_m[wb_attack1_m].sin;
        }
    }
    wb_attack1_m++;
    if(wb_attack1_m == bn_attack1_m)
        wb_attack1_m = 0;
    for(int i = 0; i < bn_attack1_s1; i++)
    {
        magazine_attack1_s1[wb_attack1_m][i].m_free = true;
    }
    //发射m，记录此时m位置
    magazine_attack1_m[wb_attack1_m].m_free = false;
    magazine_attack1_m[wb_attack1_m].m_x = m_x;
    magazine_attack1_m[wb_attack1_m].m_y = m_y;
    attack1_m_p[wb_attack1_m][0]=m_x;
    attack1_m_p[wb_attack1_m][1]=m_y;
    magazine_attack1_m[wb_attack1_m].m_speed = m_bspeed;
    magazine_attack1_m[wb_attack1_m].m_Rect.setRect(m_x,m_y,
        magazine_attack1_m[wb_attack1_m].m_width,magazine_attack1_m[wb_attack1_m].m_height);
    magazine_attack1_m[wb_attack1_m].target_x = p.m_x;
    magazine_attack1_m[wb_attack1_m].target_y = p.m_y;
    magazine_attack1_m[wb_attack1_m].aim();
    magazine_attack1_m[wb_attack1_m].sin *= -1;
    magazine_attack1_m[wb_attack1_m].cos *= -1;
    //设置wb_attack1_m的s2的速度、方向
    for(int i = 0; i < bn_attack1_s1; i++)
    {
        for(int j = 0; j < bn_attack1_s2; j++)
        {
            magazine_attack1_s2[wb_attack1_m][i][j].m_speed = m_bspeed;
            magazine_attack1_s2[wb_attack1_m][i][j].m_Rect.setRect(m_x,m_y,
                magazine_attack1_s2[wb_attack1_m][0][0].m_width,magazine_attack1_s2[wb_attack1_m][0][0].m_height);
            magazine_attack1_s2[wb_attack1_m][i][j].sin = magazine_attack1_m[wb_attack1_m].cos;
            magazine_attack1_s2[wb_attack1_m][i][j++].cos = -magazine_attack1_m[wb_attack1_m].sin;
            magazine_attack1_s2[wb_attack1_m][i][j].m_speed = m_bspeed;
            magazine_attack1_s2[wb_attack1_m][i][j].m_Rect.setRect(m_x,m_y,
                magazine_attack1_s2[wb_attack1_m][0][0].m_width,magazine_attack1_s2[wb_attack1_m][0][0].m_height);
            magazine_attack1_s2[wb_attack1_m][i][j].sin = -magazine_attack1_m[wb_attack1_m].cos;
            magazine_attack1_s2[wb_attack1_m][i][j].cos = magazine_attack1_m[wb_attack1_m].sin;
        }
    }
    wb_attack1_m++;
    if(wb_attack1_m == bn_attack1_m)
        wb_attack1_m = 0;
}

void boss::attack11(int m, int s1)
{
    if(sqrt((magazine_attack1_m[m].m_x - attack1_m_p[m][0]) * (magazine_attack1_m[m].m_x -attack1_m_p[m][0]) +
             (magazine_attack1_m[m].m_y -attack1_m_p[m][1]) * (magazine_attack1_m[m].m_y -attack1_m_p[m][1])) <=
            (m_space*s1 + m_bspeed/2) &&
        sqrt((magazine_attack1_m[m].m_x -attack1_m_p[m][0]) * (magazine_attack1_m[m].m_x -attack1_m_p[m][0]) +
             (magazine_attack1_m[m].m_y -attack1_m_p[m][1]) * (magazine_attack1_m[m].m_y -attack1_m_p[m][1])) >=
            (m_space*s1 - m_bspeed/2) )
    {
        magazine_attack1_s1[m][s1].m_free = false;
        magazine_attack1_s1[m][s1].m_x = magazine_attack1_m[m].m_x;
        magazine_attack1_s1[m][s1].m_y = magazine_attack1_m[m].m_y;
        for(int k = 0; k < bn_attack1_s2; k++)
        {
            magazine_attack1_s2[m][s1][k].m_x = magazine_attack1_s1[m][s1].m_x;
            magazine_attack1_s2[m][s1][k].m_y = magazine_attack1_s1[m][s1].m_y;
        }
    }
}

void boss::attack12()
{
    for(int i = 0; i < bn_attack1_m; i++)
    {
        // qDebug()<<i<<magazine_attack1_m[i].cos<<magazine_attack1_m[i].sin<<"one";
        for(int j = 0; j < bn_attack1_s1; j++)
        {
            if(!magazine_attack1_s1[i][j].m_free)
            {
                // qDebug()<<magazine_attack1_s2[i][j][0].cos<<magazine_attack1_s2[i][j][0].sin<<"two";
                // qDebug()<<magazine_attack1_s2[i][j][1].cos<<magazine_attack1_s2[i][j][1].sin<<"three";
                for(int k = 0; k < bn_attack1_s2; k++)
                {
                    if(magazine_attack1_s2[i][j][k].m_free)
                    {
                        // qDebug()<<i<<j<<k;
                        magazine_attack1_s2[i][j][k++].m_free = false;
                        if(k == bn_attack1_s2)
                            k = 0;
                        // qDebug()<<i<<j<<k;
                        magazine_attack1_s2[i][j][k].m_free = false;
                        // qDebug()<<magazine_attack1_s2[i][j][k].m_free;
                        break;
                    }
                }
            }
        }
    }
}

void boss::attack20()
{
    magazine_attack2[0].m_free = false;
    magazine_attack2[1].m_free = false;
    maga2_on[0] = true;
    maga2_on[1] = true;
    connect(&m_attacktimer20,&QTimer::timeout,[&](){
        magazine_attack2[0].m_free = true;
        magazine_attack2[1].m_free = true;
        disconnect(&m_attacktimer20,&QTimer::timeout,0,0);
        m_attacktimer20.stop();
    });
    m_attacktimer20.start(tlength_attack20);
}

void boss::attack21()
{
    magazine_attack2[0].m_x = m_radius*std::cos(M_PI * m_attacktimer20.remainingTime()/1000);
    magazine_attack2[0].m_y = m_radius*std::sin(M_PI * m_attacktimer20.remainingTime()/1000);
    magazine_attack2[1].m_x = -magazine_attack2[0].m_x;
    magazine_attack2[1].m_y = -magazine_attack2[0].m_y;
}

void boss::attack30(position &p)
{

    if(blood>=fullblood/2)
    {
        for(int i = 0; i < bn_attack3[0]; i++)
        {           
            warningr_attack3[i] = 10;
            magazine_attack3[i].m_height = 10;
            magazine_attack3[i].m_width = 10;
            //陨石出现
            connect(&m_attacktimer30[i][0],&QTimer::timeout,[=](){
                magazine_attack3[i].target_x = p.m_x + m_rand.bounded(-150,150);
                magazine_attack3[i].target_y = p.m_y + m_rand.bounded(-150,150);
                targets_attack3[i].m_x = magazine_attack3[i].target_x;
                targets_attack3[i].m_y = magazine_attack3[i].target_y;
                magazine_attack3[i].m_x = magazine_attack3[i].target_x - 300;
                magazine_attack3[i].m_y = magazine_attack3[i].target_y - 400;
                magazine_attack3[i].aim();
                //预警红圈膨胀
                connect(&m_attacktimer30[i][1],&QTimer::timeout,[=](){
                    warningr_attack3[i] += spread_attack3;
                });
                m_attacktimer30[i][1].start(tinterval_attack301);
                magazine_attack3[i].m_free = false;
                disconnect(&m_attacktimer30[i][0],&QTimer::timeout,0,0);
                //陨石膨胀
                connect(&m_attacktimer30[i][0],&QTimer::timeout,[=](){
                    magazine_attack3[i].m_width += 5;
                    magazine_attack3[i].m_height += 5;
                    if(magazine_attack3[i].m_width >= magazine_attack3[i].m_Rect.width())
                    {
                        magazine_attack3[i].m_speed = m_bspeed;
                        disconnect(&m_attacktimer30[i][0],&QTimer::timeout,0,0);
                    }
                });
                m_attacktimer30[i][0].start(tinterval_attack300);
            });
            m_attacktimer30[i][0].start(tinterval_attack302 * i);
        }

    }
    else
    {
        for(int i = 0; i < bn_attack3[1]; i++)
        {
            warningr_attack3[i] = 10;
            magazine_attack3[i].m_height = 10;
            magazine_attack3[i].m_width = 10;
            //陨石出现
            connect(&m_attacktimer30[i][0],&QTimer::timeout,[=](){
                magazine_attack3[i].target_x = p.m_x + m_rand.bounded(-150,150);
                magazine_attack3[i].target_y = p.m_y + m_rand.bounded(-150,150);
                targets_attack3[i].m_x = magazine_attack3[i].target_x;
                targets_attack3[i].m_y = magazine_attack3[i].target_y;
                magazine_attack3[i].m_x = magazine_attack3[i].target_x - 300;
                magazine_attack3[i].m_y = magazine_attack3[i].target_y - 400;
                magazine_attack3[i].aim();
                //预警红圈膨胀
                connect(&m_attacktimer30[i][1],&QTimer::timeout,[=](){
                    warningr_attack3[i] += spread_attack3;
                });
                m_attacktimer30[i][1].start(tinterval_attack301);
                magazine_attack3[i].m_free = false;
                disconnect(&m_attacktimer30[i][0],&QTimer::timeout,0,0);
                //陨石膨胀
                connect(&m_attacktimer30[i][0],&QTimer::timeout,[=](){
                    magazine_attack3[i].m_width += 5;
                    magazine_attack3[i].m_height += 5;
                    if(magazine_attack3[i].m_width >= magazine_attack3[i].m_Rect.width())
                    {
                        magazine_attack3[i].m_speed = m_bspeed;
                        disconnect(&m_attacktimer30[i][0],&QTimer::timeout,0,0);
                    }
                });
                m_attacktimer30[i][0].start(tinterval_attack300);
            });
            m_attacktimer30[i][0].start(tinterval_attack302 * i);
        }
    }
}

void boss::attack31(position &p)
{
    for(int i = 0; i < bn_attack3[1]; i++)
    {
        if(!magazine_attack3[i].m_free)
        {
            if(sqrt((magazine_attack3[i].m_x - targets_attack3[i].m_x) *
                    (magazine_attack3[i].m_x - targets_attack3[i].m_x) +
                    (magazine_attack3[i].m_y - targets_attack3[i].m_y) *
                    (magazine_attack3[i].m_y - targets_attack3[i].m_y)) > magazine_attack3[i].m_speed)
                magazine_attack3[i].fly();
            else
            {
                disconnect(&m_attacktimer30[i][1],&QTimer::timeout,0,0);
                magazine_attack3[i].m_speed = 0;
                magazine_attack3[i].m_free = true;
                if(sqrt((magazine_attack3[i].m_x - p.m_x) *
                        (magazine_attack3[i].m_x - p.m_x) +
                        (magazine_attack3[i].m_y - p.m_y) *
                        (magazine_attack3[i].m_y - p.m_y) < warningr_attack3[i]))
                {
                    if(p.shield>0)
                    {
                        if(p.shield >= power)
                            p.shield -= power;
                        else
                        {
                            p.shield = 0;
                            p.blood -=(power - p.shield);
                        }
                    }
                    else
                    {
                        p.blood -= power;
                    }

                }
            }
        }
    }
}
