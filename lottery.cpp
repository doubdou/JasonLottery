#include "lottery.h"
#include "ui_lottery.h"

Lottery::Lottery(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lottery)
{
    ui->setupUi(this);
}

Lottery::~Lottery()
{
    delete ui;
}
