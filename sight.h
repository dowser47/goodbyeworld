#ifndef SIGHT_H
#define SIGHT_H

#include <QWidget>
#include <QMouseEvent>

class sight : public QWidget
{
    Q_OBJECT
public:
    explicit sight(QWidget *parent = nullptr);
    int m_x;
    int m_y;

    //void mouseMoveEvent(QMouseEvent* e) ;
signals:
    void fire();
};

#endif // SIGHT_H
