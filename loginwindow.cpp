#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <qpainter.h>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{

    ui->setupUi(this);
    background.load(":/image/resource/loginwindow.png");
    setFixedSize(1200,800);
    ui->game_start_btn->setFixedSize(200,100);
    ui->game_start_btn->move(400,600);
    ui->game_start_btn->setStyleSheet(R"(
    QPushButton {
        background-image: url(:/image/resource/newgamebtn.png);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
    }
    )");
    connect(ui->game_start_btn,&QPushButton::clicked,[=](){
        emit gamestart();
    });

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), background);
}
