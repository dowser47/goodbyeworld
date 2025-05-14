#include "mainwindow.h"
#include "loginwindow.h"
#include "resultscreen.h"
#include <QApplication>
#include <QResource>
#include <QObject>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow lw;
    ResultScreen rs;
    MainWindow mw;
    lw.show();
    QObject::connect(&lw,&LoginWindow::gamestart,[&](){
        mw.creatworld();
        mw.show();
        lw.hide();
    });
    QObject::connect(&mw,&MainWindow::gameover,[&](){
        rs.show();
        mw.hide();
    });
    QObject::connect(&mw,&MainWindow::gamewin,[&](){
        rs.show();
        mw.hide();
    });
    QObject::connect(&rs,&ResultScreen::gohome,[&](){
        rs.hide();
        lw.show();
        mw.hide();
    });
    QObject::connect(&rs,&ResultScreen::playagain,[&](){
        rs.hide();
        mw.hide();
        emit lw.gamestart();
    });
    return a.exec();
}
