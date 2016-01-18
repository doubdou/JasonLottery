#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    setFixedSize(320,240);
    setWindowIcon(QIcon(":/icons/icon"));
    setWindowTitle("关于");
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->btn_ok, &QPushButton::clicked, [=]()
    {
        close();
    });

    connect(ui->btn_cancel, &QPushButton::clicked, [=]()
    {
        close();
    });

    /*
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setWindowIcon(QIcon(":/icons/icon"));
    dlg->setWindowTitle("关于本软件");
    */
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
