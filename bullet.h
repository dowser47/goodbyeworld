#ifndef BULLET_H
#define BULLET_H
#include <QWidget>
#include "position.h"

class bullet : public QWidget, public position
{
    Q_OBJECT
public:
    explicit bullet(QWidget *parent = nullptr);

    bool m_free = 1;
    int target_x;
    int target_y;
    int m_height = 20;
    int m_width = 20;
    float x;
    float y;
    float d;
    float sin;
    float cos;
    QPixmap m_image;
    void aim();//计算弹道
    void fly();//让子弹飞
};

#endif // BULLET_H
