#include "btnwidget.h"
#include "ui_btnwidget.h"

BtnWidget::BtnWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BtnWidget)
{
    ui->setupUi(this);
}

BtnWidget::~BtnWidget()
{
    delete ui;
}
