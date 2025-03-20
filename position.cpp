#include "position.h"

position::position(){}
float position::E_distance(position p2){
    float x = (this->m_x-p2.m_x);
    float y = (this->m_y-p2.m_y);
    return sqrt(x*x + y*y);
}
int position::M_distance(position p2){
    int x,y;
    if((this->m_x-p2.m_x)>0)
        x=this->m_x-p2.m_x;
    else
        x=p2.m_x - this->m_x;
    if((this->m_y-p2.m_y)>0)
        y=this->m_y-p2.m_y;
    else
        y=p2.m_y - this->m_y;
    return x+y;
}
// float position::angle(position p2){
//     float x = (p2.m_x-this->m_x);
//     float y = (p2.m_y-this->m_y);
//     if(x==0)
//     {
//         if(y<0)
//             return -100;
//         else
//             return 100;
//     }
//     return y/x;
// }
