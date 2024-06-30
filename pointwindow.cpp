#include "pointwindow.h"
#include "ui_pointwindow.h"

PointWindow::PointWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PointWindow)
{
    ui->setupUi(this);
}

PointWindow::~PointWindow()
{
    delete ui;
}
