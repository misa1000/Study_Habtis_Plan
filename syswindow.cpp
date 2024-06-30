#include "syswindow.h"
#include "ui_syswindow.h"

SysWindow::SysWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SysWindow)
{
    ui->setupUi(this);
}

SysWindow::~SysWindow()
{
    delete ui;
}
