#ifndef RESULTSCREEN_H
#define RESULTSCREEN_H

#include <QWidget>
#include <QcloseEvent>

namespace Ui {
class ResultScreen;
}

class ResultScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ResultScreen(QWidget *parent = nullptr);
    ~ResultScreen();
    void closeEvent(QCloseEvent *event);

signals:
    void gohome();
    void playagain();

private:
    Ui::ResultScreen *ui;
};

#endif // RESULTSCREEN_H
