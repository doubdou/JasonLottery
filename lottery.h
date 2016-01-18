#ifndef LOTTERY_H
#define LOTTERY_H

#include <QMainWindow>
#include <QList>
#include <QTimer>

#include "helpdialog.h"
#include "stackedwidget.h"

namespace Ui {
class Lottery;
}

class Lottery : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lottery(QWidget *parent = 0);
    void display(bool flag);
    void getnamelist();
    void on_Btn_start_clicked();
    ~Lottery();

private:
    Ui::Lottery *ui;
    HelpDialog *dlg;
    QList<QString>namelist;
    QList<QString>namelistfull;
    QTimer *timer;
    int frequent;
    StackedWidget *stkwid;


private slots:
    void slotIntSpinbox_slider();
    void slotSlider_IntSpinbox();
};

#endif // LOTTERY_H
