#include "resultscreen.h"
#include "ui_resultscreen.h"
#include <qevent.h>
#include <qpainter.h>

ResultScreen::ResultScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResultScreen)
{
    ui->setupUi(this);
    connect(ui->go_home_btn,&QPushButton::clicked,[=](){
        this->emit gohome();
    });
    connect(ui->play_agai_btn,&QPushButton::clicked,[=](){
        this->emit playagain();
    });
    background.load(":/image/resource/resultwindow.jpg");
    setFixedSize(1200,800);
    ui->play_agai_btn->setFixedSize(200,100);
    ui->play_agai_btn->move(500,400);
    ui->play_agai_btn->setStyleSheet(R"(
    QPushButton {
        background-image: url(:/image/resource/restartbtn.jpg);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
    }
    )");
    ui->go_home_btn->setFixedSize(200,100);
    ui->go_home_btn->move(500,600);
    ui->go_home_btn->setStyleSheet(R"(
    QPushButton {
        background-image: url(:/image/resource/backhomebtn.jpg);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
    }
    )");
}

ResultScreen::~ResultScreen()
{
    delete ui;
}

void ResultScreen::closeEvent(QCloseEvent *event)
{
    this->emit gohome();
    event->accept();
}

void ResultScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), background);
}
