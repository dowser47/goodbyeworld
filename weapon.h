#ifndef WEAPON_H
#define WEAPON_H

#include <QWidget>
#include <QTransform>

class weapon : public QWidget
{
    Q_OBJECT
public:
    explicit weapon(QWidget *parent = nullptr);
    QPixmap m_image;
    QPixmap m_image0;
    QPointF m_pos;
    QTransform m_transform0;
    bool m_orient = 0;
    int m_height = 80;
    int m_width = 80;
    QLineF m_line;
    qreal m_angle;
    qreal m_x;
    qreal m_y;
    void rotate(QPointF &p);
signals:
};

#endif // WEAPON_H
