#ifndef LOTTERY_H
#define LOTTERY_H

#include <QMainWindow>

namespace Ui {
class Lottery;
}

class Lottery : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lottery(QWidget *parent = 0);
    ~Lottery();

private:
    Ui::Lottery *ui;
};

#endif // LOTTERY_H
