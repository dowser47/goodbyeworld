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
    //QResource::registerResource("./energy.rcc");
    LoginWindow lw;
    ResultScreen rs;
    // MainWindow* mw = NULL;
    MainWindow mw;
    lw.show();
    // QObject::connect(&lw,&LoginWindow::gamestart,[&](){
    //     mw = new MainWindow;
    //     lw.hide();
    //     mw->show();
    //     QObject::connect(mw,&MainWindow::gameover,[&](){
    //         rs.show();
    //     });
    //     QObject::connect(&rs,&ResultScreen::gohome,[&](){
    //         QObject::disconnect(&rs,&ResultScreen::playagain,0,0);
    //         QObject::disconnect(&rs,&ResultScreen::gohome,0,0);
    //         QObject::disconnect(mw,&MainWindow::gameover,0,0);
    //         rs.hide();
    //         lw.show();
    //         mw->deleteLater();
    //         mw = NULL;
    //     });
    //     QObject::connect(&rs,&ResultScreen::playagain,[&](){
    //         QObject::disconnect(&rs,&ResultScreen::playagain,0,0);
    //         QObject::disconnect(&rs,&ResultScreen::gohome,0,0);
    //         QObject::disconnect(mw,&MainWindow::gameover,0,0);
    //         rs.hide();
    //         delete mw;
    //         emit lw.gamestart();
    //         // mw = new MainWindow;
    //     });
    // });
    QObject::connect(&lw,&LoginWindow::gamestart,[&](){
        mw.creatworld();
        mw.show();
        lw.hide();
    });
    QObject::connect(&mw,&MainWindow::gameover,[&](){
        rs.show();
        mw.hide();
    });
    // QObject::connect(&mw,&MainWindow::gamecontinue,[&](){


    // });
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
