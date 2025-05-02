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
#define BulletNum1 10
#define MonsterNum 10

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    m_x_size = 1200;
    m_y_size = 800;
    this->setFixedSize(m_x_size,m_y_size);
    // this->move(150,100);
    setWindowTitle("energy");
    setWindowIcon(QIcon(":/image/resource/bullet0.png"));

    door.load(":/image/resource/door0.png");
    sigimage0.load(":/image/resource/sight0.png");
    sigimage1.load(":/image/resource/sight1.png");
    sigimage0 = sigimage0.scaled(30,30);
    sigimage1 = sigimage1.scaled(30,30);
    sigcursor0 = QCursor(sigimage0);
    sigcursor1 = QCursor(sigimage1);
    setCursor(sigcursor0);
    map.load(":/image/resource/ground1.png");
    // m_mapx = -400;
    // m_mapy = -300;
    m_mapwidth = 2000;
    m_mapheight = 1600;
    blood.load(":/image/resource/blood0.png");
    shield.load(":/image/resource/shield0.png");
    font.setBold(1);
    font.setPointSize(30);
    pen.setColor(Qt::white);
    // pen.color();
    setMouseTracking(true);
    connect(&timer,&QTimer::timeout,[=](){

        setscene();
        update();
    });
    // creatworld();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creatworld(int cf)
{
    if(cf == 0)
    {
        m_monsnum = 0;
        m_monsnum1 = 0;
        m_bossnum = 0;        
        this->sethero();
    }
    else if(cf == 1)
    {
        m_monsnum = 0;
        m_monsnum1 = 1;
        m_bossnum = 0;
    }
    else
    {
        m_monsnum = 0;
        m_monsnum1 = 0;
        m_bossnum = 1;
    }
     pnum = 0;
    for(int i = 0; i<BulletNum; i++)
    {
        positions[pnum++] = &m_hero.magazine[i];
    }
    for(int i = 0; i<m_monsnum; i++)
    {
        positions[pnum++] = &m_monsters[i];
        positions[pnum++] = &m_monsters[i].m_bullet0;
        positions[pnum++] = &m_monsters[i].m_bullet1;
    }
    for(int i = 0; i<m_monsnum1; i++)
    {
        positions[pnum++] = &m_monsters1[i];
        for(int j = 0; j<BulletNum1; j++)
        {
            positions[pnum++] = &m_monsters1[i].magazine[j];
        }
    }
    for(int i = 0; i<m_bossnum; i++)
    {
        positions[pnum++] = &m_boss;
        positions[pnum++] = &m_boss.m_body;
        for(int j = 0; j<m_boss.m_bulletnum; j++)
        {
            positions[pnum++] = &m_boss.magazine[j];
        }
    }
    m_alivenum = m_monsnum + m_monsnum1 + m_bossnum;
    m_mapx = -400;
    m_mapy = -300;

    this->setmonster();
    this->timer.start(20);

}

void MainWindow::sethero()
{
    QTransform transform;
    transform.scale(-1,1);
    m_hero.m_xrange_r=m_x_size * 0.8;
    m_hero.m_yrange_b=m_y_size * 0.8;
    m_hero.m_xrange_l=m_x_size * 0.2;
    m_hero.m_yrange_t=m_y_size * 0.2;
    m_hero.m_x=600;
    m_hero.m_y=400;
    m_hero.m_weapon.m_pos.setX(m_hero.m_x);
    m_hero.m_weapon.m_pos.setY(m_hero.m_y);
    m_hero.m_Rect.setRect(m_hero.m_x-m_hero.h_width*0.3,m_hero.m_y-m_hero.h_height*0.1,m_hero.h_width*0.4,m_hero.h_height*0.8);
    m_hero.m_image.load(":/image/resource/person1.png");
    m_hero.m_image1 = m_hero.m_image.transformed(transform);
    m_hero.m_weapon.m_image.load(":/image/resource/weapon1.png");
    m_hero.m_weapon.m_image0.load(":/image/resource/weapon1.png");
    m_hero.m_image = m_hero.m_image.scaled(m_hero.h_width,m_hero.h_height);
    m_hero.m_image1 = m_hero.m_image1.scaled(m_hero.h_width,m_hero.h_height);
    for(int i = 0; i < BulletNum; i++)
        m_hero.magazine[i].m_image.load(":/image/resource/bullet0.png");
    m_hero.m_weapon.m_image = m_hero.m_weapon.m_image.transformed(m_hero.m_weapon.m_transform0);
    m_hero.m_weapon.m_x = 600;
    m_hero.m_weapon.m_y = 400;   
    m_hero.m_speed=5;

    m_hero.shield = 500;
    m_hero.fullshield = 5;
    m_hero.blood = 5;
    m_hero.fullblood = 5;
    m_hero.m_skill.setSingleShot(true);
    m_hero.m_skill.start(m_hero.m_skillrate);
    m_hero.m_skillready = false;
    connect(&m_hero.m_skill,&QTimer::timeout,[&](){
        if(m_hero.m_skillready == false)
            m_hero.m_skillready = true;
    });
}

void MainWindow::setmonster()
{

    // m_monster.m_Rect.setRect(m_monster.m_x,m_monster.m_y,m_monster.m_width,m_monster.m_height);
    // m_monster.m_speed=3;
    QTransform transform;
    transform.scale(-1,1);
    for(int i=0; i < m_monsnum; i++)
    {
        m_monsters[i].m_free = false;
        m_monsters[i].m_x = m_rand.bounded(m_mapx, m_mapwidth);
        m_monsters[i].m_y = m_rand.bounded(m_mapy, m_mapheight);
        m_monsters[i].m_xrange_r=m_mapwidth;
        m_monsters[i].m_yrange_b=m_mapheight;

        m_monsters[i].m_Rect.setRect(m_monsters[i].m_x,m_monsters[i].m_y,m_monsters[i].m_width,m_monsters[i].m_height);
        m_monsters[i].m_speed=3;
        m_monsters[i].blood = 100;
        m_monsters[i].fullblood = 100;
        m_monsters[i].m_image.load(":/image/resource/enemy0.png");
        m_monsters[i].m_image0.load(":/image/resource/enemy0.png");
        m_monsters[i].m_image0 = m_monsters[i].m_image0.transformed(transform);
        m_monsters[i].m_bullet0.m_image.load(":/image/resource/bullet2.png");
        m_monsters[i].m_bullet1.m_image.load(":/image/resource/bullet2.png");
        m_monsters[i].m_bullet1.m_image = m_monsters[i].m_bullet1.m_image.transformed(transform);
        m_monsters[i].m_bullet0.m_width = 60;
        m_monsters[i].m_bullet0.m_height = 60;
        m_monsters[i].m_bullet1.m_width = 60;
        m_monsters[i].m_bullet1.m_height = 60;
        //m_monsters[i].m_timer.setSingleShot(true);
        //视线外随机移动
        m_monsters[i].m_timer.start(2000);
        connect(&m_monsters[i].m_timer,&QTimer::timeout,[=](){m_monsters[i].istracking = false;});
        connect(&m_monsters[i],&monster::harm,&m_hero,&hero::recover0);

    }
    for(int i=0; i < m_monsnum1; i++)
    {
        m_monsters1[i].m_free = false;
        m_monsters1[i].m_x = m_rand.bounded(m_mapx, m_mapwidth);
        m_monsters1[i].m_y = m_rand.bounded(m_mapy, m_mapheight);
        m_monsters1[i].m_xrange_r=m_mapwidth;
        m_monsters1[i].m_yrange_b=m_mapheight;
        qDebug()<<m_monsters1[i].m_x<<m_monsters1[i].m_y;
        m_monsters1[i].m_Rect.setRect(m_monsters1[i].m_x,m_monsters1[i].m_y,m_monsters1[i].m_width,m_monsters1[i].m_height);
        m_monsters1[i].m_speed=3;
        m_monsters1[i].blood = 100;
        m_monsters1[i].fullblood = 100;
        m_monsters1[i].attackrad = 800;
        m_monsters1[i].attackrate = 500;
        m_monsters1[i].m_image.load(":/image/resource/enemy2.png");
        m_monsters1[i].m_image0.load(":/image/resource/enemy2.png");
        m_monsters1[i].m_image0 = m_monsters1[i].m_image0.transformed(transform);
        for(int j = 0; j < BulletNum1; j++)
            m_monsters1[i].magazine[j].m_image.load(":/image/resource/bullet1.png");
        //m_monsters[i].m_timer.setSingleShot(true);
        //视线外随机移动
        m_monsters1[i].m_timer.start(2000);
        connect(&m_monsters1[i].m_timer,&QTimer::timeout,[=](){m_monsters1[i].istracking = false;});
        connect(&m_monsters1[i],&monster1::harm,&m_hero,&hero::recover0);
    }
    for(int i=0; i < m_bossnum; i++)
    {
        m_boss.m_free = false;
        m_boss.m_x = m_mapx + m_mapwidth/2;
        m_boss.m_y = m_mapy + m_mapheight/2;
        m_boss.m_xrange_r=m_mapwidth;
        m_boss.m_yrange_b=m_mapheight;

        m_boss.m_Rect.setRect(m_boss.m_x,m_boss.m_y,m_boss.m_width,m_boss.m_height);
        m_boss.m_currspeed = 6;
        m_boss.m_racespeed = 10;
        m_boss.m_speed = m_boss.m_currspeed;
        m_boss.blood = 100;
        m_boss.fullblood = 100;
        m_boss.m_image.load(":/image/resource/enemy0.png");
        m_boss.m_image0.load(":/image/resource/enemy0.png");
        m_boss.m_image0 = m_boss.m_image0.transformed(transform);

        m_boss.m_body.m_width = m_boss.m_width;
        m_boss.m_body.m_height = m_boss.m_height;
        for(int j = 0; j < m_boss.m_bulletnum; j++)
            m_boss.magazine[j].m_image.load(":/image/resource/bullet1.png");

        //视线外随机移动
        m_boss.m_timer.start(3000);
        connect(&m_boss.m_timer,&QTimer::timeout,[=](){m_boss.istracking = false;});
        connect(&m_boss,&monster::harm,&m_hero,&hero::recover0);
        m_boss.m_attacktimer0.start(3000);
        connect(&m_boss.m_attacktimer0,&QTimer::timeout,[=](){m_boss.attack0();});
        m_boss.m_attacktimer1.start(10000);
        connect(&m_boss.m_attacktimer1,&QTimer::timeout,[=](){m_boss.attack1(m_hero);});
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawPixmap(m_mapx,m_mapy,m_mapwidth,m_mapheight,map);
    //本层胜利后出现传送门
    if(currflourwin)
    {
        painter.drawPixmap(m_mapx+m_mapwidth*0.5-150,m_mapy-200,300,300,door);
        // QPen pen0(Qt::red);
        // pen0.setStyle(Qt::DashLine);
        // pen0.setWidth(3);
        // painter.setPen(pen0);
        painter.drawLine(m_hero.m_x,m_hero.m_y,m_mapx+m_mapwidth*0.5,m_mapy);
    }
    //血量、护盾、技能倒计时
    painter.drawPixmap(m_x_size-300,0,100,100,blood);
    painter.drawPixmap(m_x_size-300,100,100,100,shield); 
    painter.drawText(m_x_size-200,0,100,100,Qt::AlignCenter,QString::number(m_hero.blood)+'/'+QString::number(m_hero.fullblood));
    painter.drawText(m_x_size-200,100,100,100,Qt::AlignCenter,QString::number(m_hero.shield)+'/'+QString::number(m_hero.fullshield));
    painter.drawText(m_x_size-200,200,100,100,Qt::AlignCenter,QString::number(m_hero.m_skill.remainingTime()/1000));
    //画出hero
    if(m_hero.orientation)
        painter.drawImage(m_hero.m_x-(m_hero.h_height/2),m_hero.m_y-(m_hero.h_width/2),m_hero.m_image);
    else
        painter.drawImage(m_hero.m_x-(m_hero.h_height/2),m_hero.m_y-(m_hero.h_width/2),m_hero.m_image1);

    //画出monster
    for(int i=0;i<m_monsnum;i++)
    {
        if(m_monsters[i].m_free == false)
        {
            if(m_monsters[i].x <= 0)
                painter.drawPixmap(m_monsters[i].m_x-(m_monster.m_height/2),m_monsters[i].m_y-(m_monster.m_width/2),m_monster.m_height,m_monster.m_width
                                   ,m_monsters[i].m_image);
            else
                painter.drawPixmap(m_monsters[i].m_x-(m_monster.m_height/2),m_monsters[i].m_y-(m_monster.m_width/2),m_monster.m_height,m_monster.m_width
                                   ,m_monsters[i].m_image0);
        }
    }
    //画出monster1
    for(int i=0;i<m_monsnum1;i++)
    {
        if(m_monsters1[i].m_free == 0)
        {
            if(m_monsters1[i].x <= 0)
                painter.drawPixmap(m_monsters1[i].m_x-(m_monster.m_height/2),m_monsters1[i].m_y-(m_monster.m_width/2),m_monster.m_height,m_monster.m_width
                                   ,m_monsters1[i].m_image);
            else
                painter.drawPixmap(m_monsters1[i].m_x-(m_monster.m_height/2),m_monsters1[i].m_y-(m_monster.m_width/2),m_monster.m_height,m_monster.m_width
                                   ,m_monsters1[i].m_image0);
        }
    }
    //画出boss
    if(m_boss.m_free == false)
    {
        // qDebug()<<0;
        if(m_boss.x <= 0)
        {
            painter.drawPixmap(m_boss.m_x-(m_boss.m_height/2),m_boss.m_y-(m_boss.m_width/2),m_boss.m_height,m_boss.m_width
                               ,m_boss.m_image);
            // qDebug()<<1;
        }
        else
        {
            painter.drawPixmap(m_boss.m_x-(m_boss.m_height/2),m_boss.m_y-(m_boss.m_width/2),m_boss.m_height,m_boss.m_width
                               ,m_boss.m_image0);
            // qDebug()<<2;
        }
    }
    //画出hero的子弹
    for(int i = 0; i < BulletNum; i++)
    {
        if(m_hero.magazine[i].m_free == 0)
            painter.drawPixmap(m_hero.magazine[i].m_x-m_hero.magazine[i].m_width/2,m_hero.magazine[i].m_y-m_hero.magazine[i].m_height/2
                               ,m_hero.magazine[i].m_width,m_hero.magazine[i].m_height,m_hero.magazine[i].m_image);
    }

    //画出monster的子弹
    for(int i = 0;i < m_monsnum; i++)
    {
        if(m_monsters[i].m_bullet0.m_free == 0)
            painter.drawPixmap(m_monsters[i].m_bullet0.m_x-m_monsters[i].m_bullet0.m_width*0.5,m_monsters[i].m_bullet0.m_y-m_monsters[i].m_bullet0.m_height*0.5,
                               m_monsters[i].m_bullet0.m_width,m_monsters[i].m_bullet0.m_height,m_monsters[i].m_bullet0.m_image);
        if(m_monsters[i].m_bullet1.m_free == 0)
            painter.drawPixmap(m_monsters[i].m_bullet1.m_x-m_monsters[i].m_bullet1.m_width*0.5,m_monsters[i].m_bullet1.m_y-m_monsters[i].m_bullet1.m_height*0.5,
                               m_monsters[i].m_bullet0.m_width,m_monsters[i].m_bullet0.m_height,m_monsters[i].m_bullet1.m_image);
    }
    //画出monster1的子弹
    for(int i = 0; i < m_monsnum1; i++)
    {
        // if(m_monsters1[i].m_free)
        //     continue;
        for(int j = 0; j < BulletNum1; j++)
        {
            if(m_monsters1[i].magazine[j].m_free == 0)
                painter.drawPixmap(m_monsters1[i].magazine[j].m_x-m_monsters1[i].magazine[j].m_width/2,
                                   m_monsters1[i].magazine[j].m_y-m_monsters1[i].magazine[j].m_height/2,
                                   m_monsters1[i].magazine[j].m_width,m_monsters1[i].magazine[j].m_height,m_monsters1[i].magazine[j].m_image);
        }
    }
    //画出boss的子弹
    for(int i = 0;i < m_boss.m_bulletnum; i++)
    {
        if(m_boss.magazine[i].m_free == 0)
            painter.drawPixmap(m_boss.magazine[i].m_x-m_boss.magazine[i].m_width/2,
                               m_boss.magazine[i].m_y-m_boss.magazine[i].m_height/2,
                               m_boss.magazine[i].m_width,m_boss.magazine[i].m_height,m_boss.magazine[i].m_image);
    }
    //画出hero的武器，武器会随着鼠标旋转
    painter.save();
    painter.translate(m_hero.m_x,m_hero.m_y);
    painter.rotate(m_hero.m_weapon.m_angle);
    if(m_hero.m_weapon.m_orient == 1)
    {
        // painter0.drawRect(-0.5 * m_hero.m_weapon.m_width,-0.5 * m_hero.m_weapon.m_height,m_hero.m_weapon.m_width,m_hero.m_weapon.m_height);
        painter.drawPixmap(-0.5 * m_hero.m_weapon.m_width,-0.5 * m_hero.m_weapon.m_height,m_hero.m_weapon.m_width,m_hero.m_weapon.m_height,m_hero.m_weapon.m_image);
    }
    else
    {
        // painter0.drawRect(-0.5 * m_hero.m_weapon.m_width,-0.5 * m_hero.m_weapon.m_height,m_hero.m_weapon.m_width,m_hero.m_weapon.m_height);
        painter.drawPixmap(-0.5 * m_hero.m_weapon.m_width,-0.5 * m_hero.m_weapon.m_height,m_hero.m_weapon.m_width,m_hero.m_weapon.m_height,m_hero.m_weapon.m_image0);
    }
    painter.restore();
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
            // m_hero.m_image.mirror(1,0);
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
            // m_hero.m_image.mirror(1,0);
        }
    }
    if(m_hero.m_skillready)
    {
        if(e->key() == Qt::Key_V)
            m_hero.skill();
    }
    if (currflourwin)
    {
        if((m_hero.m_x>=(m_mapx+m_mapwidth*0.5-150))&&(m_hero.m_x<=(m_mapx+m_mapwidth*0.5+150))&&(m_hero.m_y<=(m_mapy+100)))
        {
            if(e->key() == Qt::Key_Space)
            {
                this->timer.stop();
                currflourwin = 0;
                m_alivenum = m_monsnum;
                this->creatworld(currflour);

            }
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
        //技能释放和结束时射速无法立即转变
        connect(&m_hero.m_timer,&QTimer::timeout,[=](){
            m_hero.magazine[m_hero.m_whichbullet].target_x = mpos.x();
            m_hero.magazine[m_hero.m_whichbullet].target_y = mpos.y();
            m_hero.shoot(m_hero.m_whichbullet);
            // qDebug()<<m_hero.m_whichbullet;
            m_hero.m_whichbullet++;
            if(m_hero.m_whichbullet == BulletNum)
                m_hero.m_whichbullet = 0;
            return;
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
    if(currflourwin == 0)
    {
        if(m_hero.blood <= 0)
        {
            emit this->gameover();
            timer.stop();
            m_hero.m_timer.stop();
            return;
        }
        else if(m_alivenum == 0)
        {
            if(currflour<fullflour)
            {
                //本层胜利
                currflourwin = true;
                currflour++;
                return;
            }
            else
            {
                currflour = 0;
                emit this->gameover();
                timer.stop();
                m_hero.m_timer.stop();
                return;
            }
        }
    }
    //改变怪物移动范围
    for(int i = 0; i < m_monsnum; i++)
    {
        if(m_monsters[i].m_free)
            continue;
        else
        {
            m_monsters[i].m_xrange_l = m_mapx;
            m_monsters[i].m_xrange_r = m_mapx + m_mapwidth;
            m_monsters[i].m_yrange_t = m_mapy;
            m_monsters[i].m_yrange_b = m_mapy + m_mapheight;
        }
    }
    for(int i = 0; i < m_monsnum1; i++)
    {
        if(m_monsters1[i].m_free)
            continue;
        else
        {
            m_monsters1[i].m_xrange_l = m_mapx;
            m_monsters1[i].m_xrange_r = m_mapx + m_mapwidth;
            m_monsters1[i].m_yrange_t = m_mapy;
            m_monsters1[i].m_yrange_b = m_mapy + m_mapheight;
        }
    }
    if(m_boss.m_free == 0)
    {
        m_boss.m_xrange_l = m_mapx;
        m_boss.m_xrange_r = m_mapx + m_mapwidth;
        m_boss.m_yrange_t = m_mapy;
        m_boss.m_yrange_b = m_mapy + m_mapheight;
    }
    //怪物移动
    for(int i=0;i<m_monsnum;i++)
    {
        if(m_monsters[i].m_free == 0)
        {
            //视线外随机移动
            m_monsters[i].x = m_hero.m_x - m_monsters[i].m_x;
            m_monsters[i].y = m_hero.m_y - m_monsters[i].m_y;
            m_monsters[i].d = sqrt(m_monsters[i].x * m_monsters[i].x + m_monsters[i].y * m_monsters[i].y);

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
            // m_monsters[i].track0(m_hero);
            m_monsters[i].track1();
        }
    }

    for(int i = 0; i < m_monsnum1; i++)
    {
        if(m_monsters1[i].m_free == 0)
        {
            //视线外随机移动有大问题
            // m_monsters[i].x = m_hero.m_x - m_monsters[i].m_x;
            // m_monsters[i].y = m_hero.m_y - m_monsters[i].m_y;
            // m_monsters[i].d = sqrt(m_monsters[i].x * m_monsters[i].x + m_monsters[i].y * m_monsters[i].y);

            // if(m_monsters[i].d < m_monsters[i].sightrange)
            // {
            //     m_monsters[i].sin = m_monsters[i].y/m_monsters[i].d;
            //     m_monsters[i].cos = m_monsters[i].x/m_monsters[i].d;
            //     qDebug()<<0;
            // }
            // else
            // {
            //     if(m_monsters[i].istracking == false)
            //     {
            //         temp_orient = m_rand.bounded(0, 8);
            //         m_monsters[i].cos = orient[1][temp_orient];
            //         m_monsters[i].sin = orient[0][temp_orient];
            //         m_monsters[i].istracking = true;
            //         qDebug()<<1;
            //     }

            // }
            m_monsters1[i].track0(m_hero);
            if(m_monsters1[i].d < m_monsters1[i].runawayrange)
            {
                m_monsters1[i].sin *= -1;
                m_monsters1[i].cos *= -1;
            }
            m_monsters1[i].track1();

        }
    }
    if(m_boss.istracking == false && m_boss.isattacking == false)
    {
        temp_orient = m_rand.bounded(0, 8);
        m_boss.cos = orient[1][temp_orient];
        m_boss.sin = orient[0][temp_orient];
        m_boss.istracking = true;
    }
    if(m_boss.m_free == false)
        m_boss.track1();

    collisionproof();

    m_hero.rangecheck();
    m_hero.movement();
    m_hero.m_Rect.moveTo(m_hero.m_x-0.2*m_hero.h_width,m_hero.m_y-0.4*m_hero.h_height);
    if(m_hero.m_tot || m_hero.m_tob || m_hero.m_tol || m_hero.m_tor)
        othersmove();
    m_hero.m_weapon.rotate(mpos);//更改
    m_hero.m_weapon.m_pos.setX(m_hero.m_x);
    m_hero.m_weapon.m_pos.setY(m_hero.m_y);
    // 子弹若在地图中则飞行，飞出边界时回到弹夹
    for(int i = 0; i < BulletNum; i++)
    {
        if(m_hero.magazine[i].m_free == 0)
        {
            if(m_hero.magazine[i].m_x < m_mapx || m_hero.magazine[i].m_x > (m_mapx + m_mapwidth)
                || m_hero.magazine[i].m_y < m_mapy || m_hero.magazine[i].m_y >  (m_mapy + m_mapheight))
                m_hero.magazine[i].m_free = 1;
            else
                m_hero.magazine[i].fly();
        }
    }

    for(int i = 0; i < m_monsnum1; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(m_monsters1[i].magazine[j].m_free == 0)
            {
                if(m_monsters1[i].magazine[j].m_x < m_mapx || m_monsters1[i].magazine[j].m_x >  (m_mapx + m_mapwidth)
                    || m_monsters1[i].magazine[j].m_y < m_mapy || m_monsters1[i].magazine[j].m_y >  (m_mapy + m_mapheight))
                    m_monsters1[i].magazine[j].m_free = 1;
                else
                    m_monsters1[i].magazine[j].fly();
            }
        }
    }
    for(int i = 0; i < m_monsnum; i++)
    {
        if(m_monsters[i].m_bullet0.m_free == 0)
        {
            if(((m_monsters[i].m_bullet0.m_x - m_monsters[i].m_x)*(m_monsters[i].m_bullet0.m_x - m_monsters[i].m_x) +
                (m_monsters[i].m_bullet0.m_y - m_monsters[i].m_y)*(m_monsters[i].m_bullet0.m_y - m_monsters[i].m_y)) >
                (m_monsters[i].attackrad * m_monsters[i].attackrad))
                m_monsters[i].m_bullet0.m_free = 1;
            else
                m_monsters[i].m_bullet0.fly();
        }
        else if(m_monsters[i].m_bullet1.m_free == 0)
        {
            if(((m_monsters[i].m_bullet1.m_x - m_monsters[i].m_x)*(m_monsters[i].m_bullet1.m_x - m_monsters[i].m_x) +
                 (m_monsters[i].m_bullet1.m_y - m_monsters[i].m_y)*(m_monsters[i].m_bullet1.m_y - m_monsters[i].m_y)) >
                (m_monsters1[i].attackrad * m_monsters[i].attackrad))
                m_monsters[i].m_bullet1.m_free = 1;
            else
                m_monsters[i].m_bullet1.fly();
        }
    }
    if(m_boss.m_body.m_free == 0)
    {
        if(m_boss.m_body.m_x < m_mapx || m_boss.m_body.m_x >  (m_mapx + m_mapwidth)
            || m_boss.m_body.m_y < m_mapy || m_boss.m_body.m_y >  (m_mapy + m_mapheight))
        {
            m_boss.m_body.m_free = 1;
            //m_boss.emit stop();
            m_boss.m_speed = m_boss.m_currspeed;
            m_boss.m_attacktimer0.start(3000);
            connect(&m_boss.m_timer,&QTimer::timeout,[=](){m_boss.istracking = false;});
            m_boss.m_timer.start(2000);
            // qDebug()<<test++;
        }
        else
            m_boss.m_body.fly();
    }
    for(int i = 0; i < m_boss.m_bulletnum; i++)
    {
        if(m_boss.magazine[i].m_free == 0)
        {
            if(m_boss.magazine[i].m_x < m_mapx || m_boss.magazine[i].m_x >  (m_mapx + m_mapwidth)
                || m_boss.magazine[i].m_y < m_mapy || m_boss.magazine[i].m_y >  (m_mapy + m_mapheight))
                m_boss.magazine[i].m_free = 1;
            else
                m_boss.magazine[i].fly();
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
        for(int j = 0; j < m_monsnum1; j++)
        {
            if(m_monsters[i].m_free || m_monsters1[j].m_free)
                continue;
            if(m_monsters[i].m_Rect.intersects(m_monsters1[j].m_Rect))
            {
                if(m_monsters[i].d>m_monsters1[j].d)
                {
                    m_monsters[i].track0(m_monsters1[j]);
                    m_monsters[i].cos *= -1;
                    m_monsters[i].sin *= -1;
                    m_monsters[i].track1();
                }
                else
                {
                    m_monsters1[j].track0(m_monsters[i]);
                    m_monsters1[j].cos *= -1;
                    m_monsters1[j].sin *= -1;
                    m_monsters1[j].track1();
                }
            }
        }
    }
    for(int i = 0; i < m_monsnum1 - 1; i++)
    {
        for(int j = 1; j < m_monsnum1 - i; j++)
        {
            if(m_monsters1[i].m_free || m_monsters1[i+j].m_free)
                continue;
            if(m_monsters1[i].m_Rect.intersects(m_monsters1[i + j].m_Rect))
            {

                if(m_monsters1[i].d>m_monsters1[i+j].d)
                {
                    m_monsters1[i].track0(m_monsters1[i+j]);
                    m_monsters1[i].cos *= -1;
                    m_monsters1[i].sin *= -1;
                    m_monsters1[i].track1();
                }
                else
                {
                    m_monsters1[i+j].track0(m_monsters1[i]);
                    m_monsters1[i+j].cos *= -1;
                    m_monsters1[i+j].sin *= -1;
                    m_monsters1[i+j].track1();
                }
            }
        }
    }
}

void MainWindow::shotcheck()
{
    // hero的子弹是否击中monster、monster1及boss
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
                m_monsters[j].blood-=m_hero.m_power;
                m_hero.magazine[i].m_free = true;
            }
        }
        for(int j = 0; j < m_monsnum1; j++)
        {
            if(m_monsters1[j].m_free)
                continue;
            if(m_hero.magazine[i].m_Rect.intersects(m_monsters1[j].m_Rect))
            {
                m_monsters1[j].blood-=m_hero.m_power;
                m_hero.magazine[i].m_free = true;
            }
        }
        if(m_boss.m_free == false)
        {
            if(m_hero.magazine[i].m_Rect.intersects(m_boss.m_Rect))
            {

                m_boss.blood-=m_hero.m_power;
                m_hero.magazine[i].m_free = true;
            }
        }
    }
    // monster1的子弹是否击中hero
    for(int i = 0; i < m_monsnum1; i++)
    {
        for(int j = 0; j < BulletNum1; j++)
        {

            if(m_monsters1[i].magazine[j].m_free)
                continue;
            if(m_monsters1[i].magazine[j].m_Rect.intersects(m_hero.m_Rect))
            {
                if(m_hero.shield>0)
                {
                    if(m_hero.shield >= m_monsters1[i].power)
                        m_hero.shield -= m_monsters1[i].power;
                    else
                    {
                        m_hero.shield = 0;
                        m_hero.blood -=(m_monsters1[i].power - m_hero.shield);
                    }
                }
                else
                {
                    m_hero.blood -= m_monsters1[i].power;
                }
                m_monsters1[i].magazine[j].m_free = true;
                m_monsters1[i].emit harm();
            }
        }
    }
    // monster0 的子弹是否击中hero
    for(int i = 0; i < m_monsnum; i++)
    {
        if(m_monsters[i].m_bullet0.m_free == 0)
        {
            if(m_monsters[i].m_bullet0.m_Rect.intersects(m_hero.m_Rect))
            {
                if(m_hero.shield>0)
                {
                    if(m_hero.shield >= m_monsters[i].power)
                        m_hero.shield -= m_monsters[i].power;
                    else
                    {
                        m_hero.shield = 0;
                        m_hero.blood -=(m_monsters[i].power - m_hero.shield);
                    }
                }
                else
                {
                    m_hero.blood -= m_monsters[i].power;
                }
                m_monsters[i].m_bullet0.m_free = true;
                m_monsters[i].emit harm();
            }
        }
        else if(m_monsters[i].m_bullet1.m_free == 0)
        {
            if(m_monsters[i].m_bullet1.m_Rect.intersects(m_hero.m_Rect))
            {
                if(m_hero.shield>0)
                {
                    if(m_hero.shield >= m_monsters[i].power)
                        m_hero.shield -= m_monsters[i].power;
                    else
                    {
                        m_hero.shield = 0;
                        m_hero.blood -=(m_monsters[i].power - m_hero.shield);
                    }
                }
                else
                {
                    m_hero.blood -= m_monsters[i].power;
                }
                m_monsters[i].m_bullet1.m_free = true;
                m_monsters[i].emit harm();
            }
        }
    }
    // boss子弹是否击中hero
    if(m_boss.m_free == false)
    {
        // body 是否击中
        if(m_boss.m_body.m_free == false)
        {
            if(m_boss.m_body.m_Rect.intersects(m_hero.m_Rect))
            {
                if(m_hero.shield>0)
                {
                    if(m_hero.shield >= m_boss.power)
                        m_hero.shield -= m_boss.power;
                    else
                    {
                        m_hero.shield = 0;
                        m_hero.blood -=(m_boss.power - m_hero.shield);
                    }
                }
                else
                {
                    m_hero.blood -= m_boss.power;
                }
                m_boss.m_body.m_free = true;
                connect(&m_boss.m_timer,&QTimer::timeout,[=](){m_boss.istracking = false;});
                m_boss.m_timer.start(2000);
                m_boss.m_speed = m_boss.m_currspeed;
                m_boss.emit harm();
            }
        }
        // magazine
        for(int i = 0; i < m_boss.m_bulletnum; i++)
        {
            if(m_boss.magazine[i].m_free == false)
            {
                if(m_boss.magazine[i].m_Rect.intersects(m_hero.m_Rect))
                {
                    if(m_hero.shield>0)
                    {
                        if(m_hero.shield >= m_boss.power)
                            m_hero.shield -= m_boss.power;
                        else
                        {
                            m_hero.shield = 0;
                            m_hero.blood -=(m_boss.power - m_hero.shield);
                        }
                    }
                    else
                    {
                        m_hero.blood -= m_boss.power;
                    }
                    m_boss.magazine[i].m_free = true;
                    m_boss.emit harm();
                }
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
            m_monsters[i].isattacking = false;
            m_monsters[i].blood = m_monsters[i].fullblood;
            m_alivenum--;
        }
    }
    for(int i = 0; i < m_monsnum1; i++)
    {
        if(m_monsters1[i].m_free)
            continue;
        if(m_monsters1[i].blood <= 0)
        {
            m_monsters1[i].m_free = 1;
            m_monsters1[i].isattacking = false;
            m_monsters1[i].blood = m_monsters[i].fullblood;
            m_alivenum--;
        }
    }
    if(m_boss.m_free == false)
    {
        if(m_boss.blood <= 0)
        {
            m_boss.m_free = 1;
            m_boss.isattacking = false;
            m_boss.blood = m_boss.fullblood;
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
    for(int i = 0; i < m_monsnum1; i++)
    {
        if(m_monsters1[i].m_free)
            continue;
        if(m_monsters1[i].isattacking)
            continue;
        if(m_monsters1[i].d < m_monsters1[i].attackrad)
        {           
            m_monsters1[i].attack(m_hero);
        }
    }
}

void MainWindow::othersmove()
{
    if (m_hero.m_isup == 1)
    {
        if(m_hero.m_isleft == 1)
        {
            if(m_hero.m_tot && m_hero.m_y > m_mapy)
            {
                m_mapy += m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y += m_hero.m_speed*0.707;
                }
            }

            if(m_hero.m_tol && m_hero.m_x > m_mapx)
            {
                m_mapx += m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x += m_hero.m_speed*0.707;
                }
            }
        }

        else if(m_hero.m_isright == 1)
        {
            if(m_hero.m_tot && m_hero.m_y > m_mapy)
            {
                m_mapy += m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y += m_hero.m_speed*0.707;
                }
            }

            if(m_hero.m_tor && m_hero.m_x < (m_mapx + m_mapwidth))
            {
                m_mapx -= m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x -= m_hero.m_speed*0.707;
                }
            }
        }

        else
        {
            if(m_hero.m_tot && m_hero.m_y > m_mapy)
            {
                m_mapy += m_hero.m_speed;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y += m_hero.m_speed;
                }
            }

        }
    }
    else if (m_hero.m_isdown == 1)
    {
        if(m_hero.m_isleft == 1)
        {
            if(m_hero.m_tob && m_hero.m_y < (m_mapy + m_mapheight))
            {
                m_mapy -= m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y -= m_hero.m_speed*0.707;
                }
            }

            if(m_hero.m_tol && m_hero.m_x > m_mapx)
            {
                m_mapx += m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x += m_hero.m_speed*0.707;
                }
            }
        }

        else if(m_hero.m_isright == 1)
        {
            if(m_hero.m_tob && m_hero.m_y < (m_mapy + m_mapheight))
            {
                m_mapy -= m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y -= m_hero.m_speed*0.707;
                }
            }

            if(m_hero.m_tor && m_hero.m_x < (m_mapx + m_mapwidth))
            {
                m_mapx -= m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x -= m_hero.m_speed*0.707;
                }
            }
        }

        else
        {
            if(m_hero.m_tob && m_hero.m_y < (m_mapy + m_mapheight))
            {
                m_mapy -= m_hero.m_speed;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y -= m_hero.m_speed*0.707;
                }
            }

        }
    }
    else if (m_hero.m_isleft == 1)
    {
        if(m_hero.m_isup == 1)
        {
            if(m_hero.m_tot && m_hero.m_y > m_mapy)
            {
                m_mapy += m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y += m_hero.m_speed*0.707;
                }
            }

            if(m_hero.m_tol && m_hero.m_x > m_mapx)
            {
                m_mapx += m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x += m_hero.m_speed*0.707;
                }

            }
        }

        else if(m_hero.m_isdown == 1)
        {
            if(m_hero.m_tob && m_hero.m_y < (m_mapy + m_mapheight))
            {
                m_mapy -= m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y -= m_hero.m_speed*0.707;
                }
            }

            if(m_hero.m_tol && m_hero.m_x > m_mapx)
            {
                m_mapx += m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x += m_hero.m_speed*0.707;
                }
            }
        }

        else
        {
            if(m_hero.m_tol && m_hero.m_x > m_mapx)
            {
                m_mapx += m_hero.m_speed;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x += m_hero.m_speed*0.707;
                }
            }

        }
    }
    else if (m_hero.m_isright == 1)
    {
        if(m_hero.m_isup == 1)
        {
            if(m_hero.m_tot && m_hero.m_y > m_mapy)
            {
                m_mapy += m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y += m_hero.m_speed*0.707;
                }
            }

            if(m_hero.m_tor && m_hero.m_x < (m_mapx + m_mapwidth))
            {
                m_mapx -= m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x += m_hero.m_speed*0.707;
                }
            }
        }

        else if(m_hero.m_isdown == 1)
        {
            if(m_hero.m_tob && m_hero.m_y < (m_mapy + m_mapheight))
            {
                m_mapy -= m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_y -= m_hero.m_speed*0.707;
                }
            }

            if(m_hero.m_tor && m_hero.m_x < (m_mapx + m_mapwidth))
            {
                m_mapx -= m_hero.m_speed*0.707;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x -= m_hero.m_speed*0.707;
                }
            }
        }

        else
        {
            if(m_hero.m_tor && m_hero.m_x < (m_mapx + m_mapwidth))
            {
                m_mapx -= m_hero.m_speed;
                for(int i = 0; i<pnum; i++)
                {
                    positions[i]->m_x -= m_hero.m_speed*0.707;
                }

            }
        }
    }

}
