#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "autowindow.h"

#include <QDebug>
#include <QDate>
#include <QCalendarWidget>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->toolBox->setCurrentIndex(0);
    //栈控件使用
    //设置默认定位  主页
    ui->stackedWidget->setCurrentIndex(0);
    //主页按钮
    connect(ui->btnmain, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex (0);
    });
    //任务按钮
    connect (ui->btntaxt, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    //打卡按钮
    connect (ui->btngoal, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    //个人按钮
    connect (ui->btnperson, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(3);
    });
    // 登录按钮
    connect(ui->btnoutlogin,&QPushButton::clicked,[=](){
        LoginWindow * loginwindow = new LoginWindow();
        loginwindow->setWindowModality(Qt::ApplicationModal);
        loginwindow->show();
        this->close();
    });
    // 用户自定义按钮
    connect(ui->btnauto,&QPushButton::clicked,[=](){
        AutoWindow * autowindow = new AutoWindow();
        autowindow->setWindowModality(Qt::ApplicationModal);
        autowindow->show();
        this->close();
    });
    // 设置日历的最小和最大日期
    ui->calendarWidget->setMinimumDate(QDate(2005, 1, 1));
    ui->calendarWidget->setMaximumDate(QDate::currentDate().addYears(1));
    connect(ui->calendarWidget,&QCalendarWidget::clicked,this,&MainWindow::activatedChanged);    //点击信号

}

MainWindow::~MainWindow()
{
    delete ui;
}

//双击信号  日期触发
void MainWindow::activatedChanged(const QDate date){
    qDebug()<< "点击信号：" << date;

}


