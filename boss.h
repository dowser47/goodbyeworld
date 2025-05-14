#ifndef BOSS_H
#define BOSS_H
#include "monster.h"
#include "QRandomGenerator"

class boss: public monster
{
public:
    boss();
    int which_bullet = 0;
    int m_space = 150;
    int wb_attack1_m = 0;
    int m_radius = 150;
    int bn_attack1_m = 6;
    int bn_attack1_s1 = 10;
    int bn_attack1_s2 = 20;
    int attack1_m_p[6][2];
    int m_currspeed;
    int m_racespeed;
    int m_bulletnum = 100;
    int bn_attack3[2] = {3,5};
    int spread_attack3 = 1;//预警红圈扩散速度
    int warningr_attack3[5];//预警红圈半径

    bullet magazine[100];
    bullet magazine_attack1_m[6];
    bullet magazine_attack1_s1[6][10];
    bullet magazine_attack1_s2[6][10][20];
    bullet magazine_attack2[2];
    bullet magazine_attack3[5];
    position targets_attack3[5];//陨石坠落位置

    QRandomGenerator m_rand;
    bool maga2_on[2];
    // bullet magazine_attack1[8][11][21];//如果数组太大会导致栈溢出
    QTimer m_attacktimer0;//一技能按时触发
    int tinterval_attack0 = 5000;
    QTimer m_attacktimer1;//二技能按时触发
    int tinterval_attack1 = 9000;
    QTimer m_attacktimer12;//s1按时发射s2
    int tinterval_attack12 = 1000;
    QTimer m_attacktimer2;//三技能按时触发
    int tinterval_attack2 = 8000;
    QTimer m_attacktimer20;//三技能按时结束
    int tlength_attack20 = 5000;
    QTimer m_attacktimer3;//四技能按时触发
    int tinterval_attack3 = 7500;
    QTimer m_attacktimer30[5][2];//控制陨石出现、膨胀，预警半径增大
    int tinterval_attack300 = 20;//陨石不动，膨胀
    int tinterval_attack301 = 20;//预警半径增大
    int tinterval_attack302 = 500;//陨石出现
    // QTimer m_attacktimer;
    QPixmap m_attack0_bimage;
    QPixmap m_attack10_bimage;
    QPixmap m_attack11_bimage;
    QPixmap m_attack12_bimage;
    QPixmap m_attack3_bimage;
    void shoot(int i);
    void attack0();
    //射出母弹
    void attack10(position &p);
    //判断子1弹是否到达位置
    void attack11(int m,int s1);
    //同步射s2
    void attack12();
     //召唤护体法球
    void attack20();
    //法球旋转
    void attack21();
    //召唤陨石
    void attack30(position &p);
    //检测陨石位置，判断是否攻击到hero
    void attack31(position &p);

signals:

};

#endif // BOSS_H
