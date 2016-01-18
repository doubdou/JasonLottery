#include "lottery.h"
#include "ui_lottery.h"

#include <QAction>
#include <QWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTime>
#include <QTimer>

#include <stdlib.h>

Lottery::Lottery(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lottery)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/icon"));

    ui->btn_start->setEnabled(false);
    ui->btn_start->setStyleSheet("font-size:30px");

    /*初始化标题*/
    ui->label_title->setText("迅达电梯无锡分公司 年会抽奖");
    ui->label_title->setStyleSheet("font-size:22px;color:red");
    ui->label_title->setAlignment(Qt::AlignHCenter);
    //ui->label_title->setFont(&(75));

    /*文件路径设置为不可编辑*/
    //ui->lineEdit_filepath->setEnabled(false);

    //ui->label_ScrollArea->setPixmap(QPixmap(":/images/who"));
    ui->label_ScrollArea->setAlignment(Qt::AlignCenter);
    ui->label_ScrollArea->setStyleSheet("font-size:100px;color:red");

    /*初始化”退出“按钮*/
    connect(ui->btn_exit, &QPushButton::clicked, [=]()
    {
        close();
    });

    /*初始化”重置“按钮*/
    connect(ui->btn_reset, &QPushButton::clicked, [=]()
    {
        namelist = namelistfull;

        /*修改统计人数的label*/
        QString  s11;
        int winnernum = namelistfull.size() - namelist.size();
        s11 = QString::number(winnernum,10);
        ui->label_winnernum2->setText(s11); //已中奖人数

        QString s_22;
        s_22 = QString::number(namelist.size(), 10);
        ui->label_leftnum_2->setText(s_22);  //剩余参与人数
    });

    /*初始化 帮助->关于 */
    connect(ui->action_about, &QAction::triggered, [=]()
    {
       dlg = new HelpDialog;
       dlg->show();
    });

    /*初始化spinbox 和 slider控件*/
    ui->spinBox->setMinimum(1);
    ui->Slider->setMinimum(1);
    ui->spinBox->setMaximum(100);
    ui->Slider->setMaximum(100);
    ui->spinBox->setValue(50); //设置默认值
    ui->Slider->setValue(50); //设置默认值
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(slotIntSpinbox_slider()));
    connect(ui->Slider, SIGNAL(valueChanged(int)), this, SLOT(slotSlider_IntSpinbox()));

    getnamelist();





    /*设置定时器*/
    timer = new QTimer();
    frequent = 50; //设置默认值
    timer->setInterval((101 - frequent) * 2);
    qsrand(QTime::currentTime().msec());
    connect(timer, &QTimer::timeout, [=]()
    {
        static int num = 0;
        int i = num % namelist.size();
        ui->label_ScrollArea->setText(namelist.at(i));
        num++;
        update();
    });

    connect(ui->btn_start, &QPushButton::clicked, [=]()
    {
        on_Btn_start_clicked();
    });

    connect(ui->btn_reset, &QPushButton::clicked, [=]()
    {
        namelist.clear();
        namelist = namelistfull;
        ui->btn_start->setEnabled(true);
    });

}

Lottery::~Lottery()
{
    delete timer;
    delete ui;
}

void Lottery::getnamelist()
{
    connect(ui->action_selectFile, &QAction::triggered, [=]()
    {
        QString path = QFileDialog::getOpenFileName(this, "选择抽奖名单", ".","*.txt");
        if (path.isEmpty())
        {
            return;
        }
        QFile file;
        file.setFileName(path);
        if (!file.open(QFile::ReadOnly))
        {
            return;
        }
        ui->lineEdit_filepath->setText(path);
        namelist.clear();

        QTextStream stream(&file);
        QString line;
        while(!stream.atEnd())
        {
            line = stream.readLine();
            if (!line.isEmpty())
            {
                namelist.append(line);
            }
        }
        namelistfull = namelist;
        file.close();
        ui->btn_start->setEnabled(true);

        /*初始化人数统计的label*/
        QString  s1;
        s1 = QString::number(namelistfull.size(),10);
        ui->label_sum2->setText(s1); //总人数

        QString  s2;
        int winnernum = namelistfull.size() - namelist.size();
        s2 = QString::number(winnernum,10);
        ui->label_winnernum2->setText(s2); //已中奖人数

        QString s3;
        s3 = QString::number(namelist.size(), 10);
        ui->label_leftnum_2->setText(s3);  //剩余参与人数
    });
}

void Lottery::display(bool flag)
{
    int size = namelist.size();
    int winner = (qrand()%size);
    ui->label_ScrollArea->setText(namelist.at(winner));
    if (flag == true)
    {
        namelist.removeAt(winner);
    }
}

void Lottery::slotSlider_IntSpinbox()
{
    ui->spinBox->setValue(ui->Slider->value());
    frequent = ui->Slider->value();
    timer->setInterval((101 - frequent) * 2);
}

void Lottery::slotIntSpinbox_slider()
{
    ui->Slider->setValue(ui->spinBox->value());
    frequent = ui->spinBox->value();
    timer->setInterval((101 - frequent) * 2);
}

void Lottery::on_Btn_start_clicked()
{
    if (namelist.size() == 1)
    {
        QMessageBox::information(this, "提示", "剩余1人参与抽奖，结束！");

        ui->btn_start->setEnabled(false);
        ui->label_ScrollArea->clear();
        return;
    }

    if (ui->btn_start->text() == "开始")
    {
        ui->btn_start->setText("停止");
        timer->start(); //启动定时器， 翻滚名字
    }
    else if (ui->btn_start->text() == "停止")
    {
        ui->btn_start->setText("开始");
        timer->stop();
        display(true);  //停止定时器  显示中奖者名字

        /*修改统计人数的label*/
        QString  s_winnernum;
        int winnernum = namelistfull.size() - namelist.size();
        s_winnernum = QString::number(winnernum,10);
        ui->label_winnernum2->setText(s_winnernum); //已中奖人数

        QString s_leftnum;
        s_leftnum = QString::number(namelist.size(), 10);
        ui->label_leftnum_2->setText(s_leftnum);  //剩余参与人数


        //ui->label_winnernum2->setText(); //已中奖人数
        //ui->label_leftnum_2->setText();  //剩余参与人数
    }
}









