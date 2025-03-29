#include "mainwindow.h"
#include "loginwindow.h"
#include "resultscreen.h"
#include <QApplication>
#include <QResource>
#include <QObject>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QResource::registerResource("./energy.rcc");
    LoginWindow lw;
    ResultScreen rs;
    MainWindow* mw = NULL;
    lw.show();
    QObject::connect(&lw,&LoginWindow::gamestart,[&](){
        mw = new MainWindow;
        lw.hide();
        mw->show();
        QObject::connect(mw,&MainWindow::gameover,[&](){
            rs.show();
        });
        QObject::connect(&rs,&ResultScreen::gohome,[&](){
            QObject::disconnect(&rs,&ResultScreen::playagain,0,0);
            QObject::disconnect(&rs,&ResultScreen::gohome,0,0);
            QObject::disconnect(mw,&MainWindow::gameover,0,0);
            rs.hide();
            lw.show();
            mw->deleteLater();
            mw = NULL;
        });
        QObject::connect(&rs,&ResultScreen::playagain,[&](){
            QObject::disconnect(&rs,&ResultScreen::playagain,0,0);
            QObject::disconnect(&rs,&ResultScreen::gohome,0,0);
            QObject::disconnect(mw,&MainWindow::gameover,0,0);
            rs.hide();
            delete mw;
            emit lw.gamestart();
            // mw = new MainWindow;
        });
    });

    // MainWindow w;
    // w.show();
    return a.exec();
}
