#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <qevent.h>
//#include <QRandomGenerator>

#define BulletNum 50

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_x_size = 1200;
    m_y_size = 800;
    this->setFixedSize(m_x_size,m_y_size);
    sethero();
    setmonster();
    timer.start(20);
    //timer0.start(2000);

    setMouseTracking(true);


    connect(&timer,&QTimer::timeout,[=](){

        //for(int i=0 ;i<m_monsnum;i++)

        //qDebug()<<m_monsters[0].sin<<' '<<m_monsters[0].cos<<' '<<m_monsters[0].istracking;
        ui->label0->setText(QString("shield: %1\nblood: %2").arg(m_hero.shield).arg(m_hero.blood));
        setscene();
        update();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sethero()
{

    m_hero.m_x=600;
    m_hero.m_y=400;
    m_hero.m_Rect.setRect(m_hero.m_x,m_hero.m_y,m_hero.h_width,m_hero.h_height);
    m_hero.m_speed=5;
    m_hero.m_xrange_r=m_x_size;
    m_hero.m_yrange_b=m_y_size;
    m_hero.shield = 5;
    m_hero.fullshield = 5;
    m_hero.blood = 5;
    m_hero.fullblood = 5;
}

void MainWindow::setmonster()
{

    m_monster.m_Rect.setRect(m_monster.m_x,m_monster.m_y,m_monster.m_width,m_monster.m_height);
    m_monster.m_speed=3;

    for(int i=0; i < m_monsnum; i++)
    {
        m_monsters[i].m_x = m_rand.bounded(0, m_x_size);
        m_monsters[i].m_y = m_rand.bounded(0, m_y_size);

        m_monsters[i].m_Rect.setRect(m_monster.m_x,m_monster.m_y,m_monster.m_width,m_monster.m_height);
        m_monsters[i].m_speed=3;
        m_monsters[i].m_xrange_r=m_x_size;
        m_monsters[i].m_yrange_b=m_y_size;

        m_monsters[i].blood = 100;
        m_monsters[i].fullblood = 100;

        //m_monsters[i].m_timer.setSingleShot(true);
        //视线外随机移动
        m_monsters[i].m_timer.start(2000);
        connect(&m_monsters[i].m_timer,&QTimer::timeout,[=](){m_monsters[i].istracking = false;});
        connect(&m_monsters[i],&monster::harm,&m_hero,&hero::recover0);
    }


}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(m_hero.m_x-(m_hero.h_height/2),m_hero.m_y-(m_hero.h_width/2),m_hero.h_height,m_hero.h_width);
    for(int i=0;i<m_monsnum;i++)
    {
        if(m_monsters[i].m_free == 0)
            painter.drawRect(m_monsters[i].m_x-(m_monster.m_height/2),m_monsters[i].m_y-(m_monster.m_width/2),m_monster.m_height,m_monster.m_width);
    }
    painter.drawEllipse(sig.m_x-10,sig.m_y-10,20,20);
    for(int i = 0; i < BulletNum; i++)
    {
        if(m_hero.magazine[i].m_free == 0)
            painter.drawEllipse(m_hero.magazine[i].m_x-5,m_hero.magazine[i].m_y-5,10,10);
    }

}
void MainWindow::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_W)
        m_hero.m_isup = 1;
    if (e->key() == Qt::Key_A)
        m_hero.m_isleft = 1;
    if (e->key() == Qt::Key_S)
        m_hero.m_isdown = 1;
    if (e->key() == Qt::Key_D)
        m_hero.m_isright = 1;


    else QWidget::keyPressEvent(e);

}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_W)
        m_hero.m_isup = 0;
    if (e->key() == Qt::Key_A)
        m_hero.m_isleft = 0;
    if (e->key() == Qt::Key_S)
        m_hero.m_isdown = 0;
    if (e->key() == Qt::Key_D)
        m_hero.m_isright = 0;
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{

    mpos = e->pos();
    sig.m_x=mpos.x();
    sig.m_y=mpos.y();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{


    //QPoint mpos = e->pos();
    if(e->button() == Qt::LeftButton)
    {

        m_hero.m_timer.start(m_hero.m_firespeed);
        connect(&m_hero.m_timer,&QTimer::timeout,[=](){
            m_hero.magazine[m_hero.m_whichbullet].target_x = mpos.x();
            m_hero.magazine[m_hero.m_whichbullet].target_y = mpos.y();
            m_hero.shoot(m_hero.m_whichbullet);
            m_hero.m_whichbullet++;
            if(m_hero.m_whichbullet == BulletNum)
                m_hero.m_whichbullet = 0;

            return;
            // for(int i = 0; i < BulletNum ; i++)
            // {
            //     if(m_hero.magazine[i].m_free)
            //     {
            //         m_hero.magazine[i].target_x = mpos.x();
            //         m_hero.magazine[i].target_y = mpos.y();
            //         m_hero.shoot(i);
            //     }
            //     break;
            // }
        });

    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        m_hero.m_timer.stop();
}



void MainWindow::setscene()
{
    if(m_hero.blood <= 0)
    {
        qDebug()<<"You Have Lost";
        timer.stop();
        return;
    }
    for(int i=0;i<m_monsnum;i++)
    {
        if(m_monsters[i].m_free == 0)
        {
            //视线外随机移动
            m_monsters[i].x = m_hero.m_x - m_monsters[i].m_x;
            m_monsters[i].y = m_hero.m_y - m_monsters[i].m_y;
            m_monsters[i].d = sqrt(m_monsters[i].x * m_monsters[i].x + m_monsters[i].y * m_monsters[i].y);
            //m_monsters[i].track0(m_hero);
            if(m_monsters[i].d < m_monsters[i].sightrange)
            {
                m_monsters[i].sin = m_monsters[i].y/m_monsters[i].d;
                m_monsters[i].cos = m_monsters[i].x/m_monsters[i].d;
            }
            else
            {
                if(m_monsters[i].istracking == false)
                {
                    temp_orient = m_rand.bounded(0, 8);
                    m_monsters[i].cos = orient[1][temp_orient];
                    m_monsters[i].sin = orient[0][temp_orient];
                    m_monsters[i].istracking = true;
                }
            }
            m_monsters[i].track1();
        }
    }

    collisionproof();

    m_hero.movement();

    for(int i = 0; i < BulletNum; i++)
    {
        if(m_hero.magazine[i].m_free == 0)
        {
            if(m_hero.magazine[i].m_x<0 || m_hero.magazine[i].m_x >  m_x_size
                || m_hero.magazine[i].m_y < 0 || m_hero.magazine[i].m_y >  m_y_size)
                m_hero.magazine[i].m_free = 1;
            else
                m_hero.magazine[i].fly();
        }
    }

    attackcheck();
    shotcheck();
    deathcheck();
}

void MainWindow::collisionproof()
{
    for(int i = 0; i < m_monsnum - 1; i++)
    {
        for(int j = 1; j < m_monsnum - i; j++)
        {
            if(m_monsters[i].m_free || m_monsters[i+j].m_free)
                continue;
            if(m_monsters[i].m_Rect.intersects(m_monsters[i + j].m_Rect))
            {

                if(m_monsters[i].d>m_monsters[i+j].d)
                {
                    m_monsters[i].track0(m_monsters[i+j]);
                    m_monsters[i].cos *= -1;
                    m_monsters[i].sin *= -1;
                    m_monsters[i].track1();

                }
                else
                {
                    m_monsters[i+j].track0(m_monsters[i]);
                    m_monsters[i+j].cos *= -1;
                    m_monsters[i+j].sin *= -1;
                    m_monsters[i+j].track1();

                }
            }
        }
    }
}

void MainWindow::shotcheck()
{
    for(int i = 0; i < BulletNum; i++)
    {
        if(m_hero.magazine[i].m_free)
            continue;
        for(int j = 0; j < m_monsnum; j++)
        {
            if(m_monsters[j].m_free)
                continue;
            if(m_hero.magazine[i].m_Rect.intersects(m_monsters[j].m_Rect))
            {
                m_monsters[j].blood-=10;
                m_hero.magazine[i].m_free = true;
            }
        }
    }
}

void MainWindow::deathcheck()
{
    for(int i = 0; i < m_monsnum; i++)
    {
        if(m_monsters[i].m_free)
            continue;
        if(m_monsters[i].blood <= 0)
        {
            m_monsters[i].m_free = 1;
            m_monsters[i].blood = m_monsters[i].fullblood;
        }

    }
}

void MainWindow::attackcheck()
{
    for(int i = 0; i < m_monsnum; i++)
    {

        if(m_monsters[i].isattacking)
            continue;
        if(m_monsters[i].d < m_monsters[i].attackrad)
        {

            m_monsters[i].attack(m_hero);                        
        }
    }
}





