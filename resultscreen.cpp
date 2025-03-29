#include "resultscreen.h"
#include "ui_resultscreen.h"
#include <qevent.h>

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
