#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <qevent.h>
#include <QIcon>
#include <QPixmap>
#include <QImage>
#include <QCursor>
#include <QGraphicsItemGroup>
//#include <QRandomGenerator>

#define BulletNum 50
#define MonsterNum 10

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    m_x_size = 1200;
    m_y_size = 800;
    this->setFixedSize(m_x_size,m_y_size);
    setWindowTitle("energy");
    setWindowIcon(QIcon(":/image/resource/bullet0.png"));
    sethero();
    setmonster();
    timer.start(20);
    sigimage0.load(":/image/resource/sight0.png");
    sigimage1.load(":/image/resource/sight1.png");
    sigimage0 = sigimage0.scaled(30,30);
    sigimage1 = sigimage1.scaled(30,30);
    sigcursor0 = QCursor(sigimage0);
    sigcursor1 = QCursor(sigimage1);
    setCursor(sigcursor0);
    map.load(":/image/resource/ground1.png");
    blood.load(":/image/resource/blood0.png");
    shield.load(":/image/resource/shield0.png");
    font.setBold(1);
    font.setPointSize(30);

    // pen.setColor(Qt::red);
    // pen.color();
    setMouseTracking(true);

    connect(&timer,&QTimer::timeout,[=](){

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
    m_hero.m_weapon.m_pos.setX(m_hero.m_x);
    m_hero.m_weapon.m_pos.setY(m_hero.m_y);
    m_hero.m_Rect.setRect(m_hero.m_x,m_hero.m_y,m_hero.h_width,m_hero.h_height);
    m_hero.m_image.load(":/image/resource/person1.png");
    m_hero.m_weapon.m_image.load(":/image/resource/weapon1.png");
    m_hero.m_weapon.m_image0.load(":/image/resource/weapon1.png");
    m_hero.m_weapon.m_image = m_hero.m_weapon.m_image.transformed(m_hero.m_weapon.m_transform0);
    m_hero.m_weapon.m_x = 600;
    m_hero.m_weapon.m_y = 400;
    m_hero.m_image = m_hero.m_image.scaled(m_hero.h_width,m_hero.h_height);
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
        m_monsters[i].m_image.load(":/image/resource/enemy0.png");
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
    QPainter painter0(this);
    QPen pen(QColor(255,0,0));
    painter.setFont(font);

    painter.drawPixmap(0,0,m_x_size,m_y_size,map);
    painter.drawPixmap(m_x_size-300,0,100,100,blood);
    painter.drawPixmap(m_x_size-300,100,100,100,shield);
    painter.setPen(pen);
    painter.drawText(m_x_size-300,0,100,100,Qt::AlignCenter,QString::number(m_hero.blood)+'/'+QString::number(m_hero.fullblood));
    painter.drawText(m_x_size-300,100,100,100,Qt::AlignCenter,QString::number(m_hero.shield)+'/'+QString::number(m_hero.fullshield));
    // painter.drawText()
    painter.drawImage(m_hero.m_x-(m_hero.h_height/2),m_hero.m_y-(m_hero.h_width/2),m_hero.m_image);
    //painter.drawPixmap(m_hero.m_x-(m_hero.h_height/2),m_hero.m_y-(m_hero.h_width/2),m_hero.m_weapon.m_image);
    //painter.drawPixmap(m_hero.m_weapon.m_pos,m_hero.m_weapon.m_image,m_hero.m_weapon.m_Rect);

    for(int i=0;i<m_monsnum;i++)
    {
        if(m_monsters[i].m_free == 0)
            painter.drawPixmap(m_monsters[i].m_x-(m_monster.m_height/2),m_monsters[i].m_y-(m_monster.m_width/2),m_monster.m_height,m_monster.m_width
                               ,m_monsters[i].m_image);
    }
    for(int i = 0; i < BulletNum; i++)
    {
        if(m_hero.magazine[i].m_free == 0)
            painter.drawPixmap(m_hero.magazine[i].m_x-5,m_hero.magazine[i].m_y-5,15,15,m_hero.magazine[i].m_image);
    }

    painter0.translate(m_hero.m_x,m_hero.m_y);
    painter0.rotate(m_hero.m_weapon.m_angle);
    if(m_hero.m_weapon.m_orient == 1)
    {
        // painter0.drawRect(-0.5 * m_hero.m_weapon.m_width,-0.5 * m_hero.m_weapon.m_height,m_hero.m_weapon.m_width,m_hero.m_weapon.m_height);
        painter0.drawPixmap(-0.5 * m_hero.m_weapon.m_width,-0.5 * m_hero.m_weapon.m_height,m_hero.m_weapon.m_width,m_hero.m_weapon.m_height,m_hero.m_weapon.m_image);
    }
    else
    {
        // painter0.drawRect(-0.5 * m_hero.m_weapon.m_width,-0.5 * m_hero.m_weapon.m_height,m_hero.m_weapon.m_width,m_hero.m_weapon.m_height);
        painter0.drawPixmap(-0.5 * m_hero.m_weapon.m_width,-0.5 * m_hero.m_weapon.m_height,m_hero.m_weapon.m_width,m_hero.m_weapon.m_height,m_hero.m_weapon.m_image0);
    }
}
void MainWindow::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_W)
        m_hero.m_isup = 1;
    if (e->key() == Qt::Key_A)
    {
        m_hero.m_isleft = 1;
        if(m_hero.orientation == 0)
        {
            m_hero.orientation = 1;
            m_hero.m_image.mirror(1,0);
        }
    }
    if (e->key() == Qt::Key_S)
        m_hero.m_isdown = 1;
    if (e->key() == Qt::Key_D)
    {
        m_hero.m_isright = 1;
        if(m_hero.orientation)
        {
            m_hero.orientation = 0;
            m_hero.m_image.mirror(1,0);
        }
    }


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
    setCursor(sigcursor1);
    if(e->button() == Qt::LeftButton)
    {
        m_hero.magazine[m_hero.m_whichbullet].target_x = mpos.x();
        m_hero.magazine[m_hero.m_whichbullet].target_y = mpos.y();
        m_hero.shoot(m_hero.m_whichbullet);
        // qDebug()<<m_hero.m_whichbullet;
        m_hero.m_whichbullet++;
        if(m_hero.m_whichbullet == BulletNum)
            m_hero.m_whichbullet = 0;
        m_hero.m_timer.start(m_hero.m_firespeed);
        connect(&m_hero.m_timer,&QTimer::timeout,[=](){
            m_hero.magazine[m_hero.m_whichbullet].target_x = mpos.x();
            m_hero.magazine[m_hero.m_whichbullet].target_y = mpos.y();
            m_hero.shoot(m_hero.m_whichbullet);
            // qDebug()<<m_hero.m_whichbullet;
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
    setCursor(sigcursor0);
    if(e->button() == Qt::LeftButton)
    {
        m_hero.m_timer.stop();
        disconnect(&m_hero.m_timer,&QTimer::timeout,0,0);
    }

}



void MainWindow::setscene()
{
    if(m_hero.blood <= 0)
    {
        emit this->gameover();
        qDebug()<<"You Have Lost";
        timer.stop();        
        return;
    }
    else if(m_alivenum == 0)
    {
        emit this->gameover();
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
    m_hero.m_weapon.rotate(mpos);//更改
    m_hero.m_weapon.m_pos.setX(m_hero.m_x);
    m_hero.m_weapon.m_pos.setY(m_hero.m_y);
    // m_hero.m_weapon.m_Rect.setPos(m_hero.m_weapon.m_pos);
    // m_hero.m_weapon.m_pixmapitem.setPos(m_hero.m_weapon.m_pos);

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
            m_alivenum--;
        }

    }
}

void MainWindow::attackcheck()
{
    for(int i = 0; i < m_monsnum; i++)
    {
        if(m_monsters[i].m_free)
            continue;
        if(m_monsters[i].isattacking)
            continue;
        if(m_monsters[i].d < m_monsters[i].attackrad)
        {

            m_monsters[i].attack(m_hero);                        
        }
    }
}





