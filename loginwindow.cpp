#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->game_start_btn,&QPushButton::clicked,[=](){
        emit gamestart();
    });
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
