#include "weapon.h"

weapon::weapon(QWidget *parent)
    : QWidget{parent}
{
    m_transform0.scale(1,-1);
}

void weapon::rotate(QPointF &p)
{
    m_line.setLine(m_pos.rx(),m_pos.ry(),p.rx(),p.ry());
    m_angle = -m_line.angle();

    // m_Rect.setRotation(m_angle);
    if(m_pos.rx()>p.rx())
        m_orient = 1;
    else
        m_orient = 0;
}
