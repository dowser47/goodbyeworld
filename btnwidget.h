#ifndef BTNWIDGET_H
#define BTNWIDGET_H

#include <QWidget>

namespace Ui {
class BtnWidget;
}

class BtnWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BtnWidget(QWidget *parent = nullptr);
    ~BtnWidget();

private:
    Ui::BtnWidget *ui;
};

#endif // BTNWIDGET_H
