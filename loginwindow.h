#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    QPixmap background;
    void paintEvent(QPaintEvent *event);
signals:
    void gamestart();


private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
