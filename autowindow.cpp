#include "autowindow.h"
#include "ui_autowindow.h"
#include "mainwindow.h"

#include <QLabel>
#include <QWidget>
#include <QDebug>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QRadioButton>
#include <QTimer>

AutoWindow::AutoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AutoWindow)
{
    ui->setupUi(this);
    ui->frame->hide();
    connect(ui->btnnew,&QPushButton::clicked,[=](){
        ui->frame->show();
    });
    connect(ui->btnsure,&QPushButton::clicked,[=](){
        QWidget * widget = new QWidget();
        QVBoxLayout * vboxlayout = new QVBoxLayout();

        QLabel * lab1 = new QLabel("优先级");
        QLineEdit * linewidget1 = new QLineEdit();
        QWidget * widget1 = new QWidget();
        QHBoxLayout * hboxlayout1 = new QHBoxLayout();
        hboxlayout1->addWidget(lab1);hboxlayout1->addWidget(linewidget1);
        widget1->setLayout(hboxlayout1);

        QLabel * lab2 = new QLabel("完成时间");
        QLineEdit * linewidget2 = new QLineEdit();
        QWidget * widget2 = new QWidget();
        QHBoxLayout * hboxlayout2 = new QHBoxLayout();
        hboxlayout2->addWidget(lab2);hboxlayout2->addWidget(linewidget2);
        widget2->setLayout(hboxlayout2);

        QLabel * lab3 = new QLabel("主题");

        vboxlayout->addWidget(widget1);
        vboxlayout->addWidget(widget2);
        vboxlayout->addWidget(lab3);
        QTextEdit * textwidget = new QTextEdit();
        vboxlayout->addWidget(textwidget);

        widget->setLayout(vboxlayout);

        //添加一个新的item到QToolBox中
        QString value1 = ui->lineEdit->text();
        qDebug() << value1.toUtf8().data();
        ui->toolBox->addItem(widget,value1);
        ui->frame->hide();
        ui->lineEdit->clear();
    });

    connect(ui->btnclose,&QPushButton::clicked,[=](){
        ui->frame->hide();
    });
    connect(ui->btnsave,&QPushButton::clicked,[=](){
        QToolBox * toolBox = ui->toolBox;/* 获取你的 QToolBox 指针 */
        int currentIndex = toolBox->currentIndex();
        // 检查是否有选中的选项卡
        if (currentIndex != -1) {
            QWidget * currentWidget = toolBox->widget(currentIndex);
            // 现在你可以对 currentWidget 进行操作了
            QList<QLineEdit *> list = findAllLineEdits(currentWidget);

            QLineEdit * text1 = list.at(0);
            QString valuea = text1->text();
            qDebug() << valuea.toUtf8().data();

            QLineEdit * text2 = list.at(1);
            QString valueb = text2->text();
            qDebug() << valueb.toUtf8().data();

            QTextEdit * text = currentWidget->findChild<QTextEdit *>();
            QString value1 = text->toPlainText();
            qDebug() << value1.toUtf8().data();

        } else {
            // 没有选中的选项卡，处理这种情况（如果需要）
        }

    });
    connect(ui->btndel,&QPushButton::clicked,[=](){
        QToolBox * toolBox = ui->toolBox;/* 获取你的 QToolBox 指针 */
        int currentIndex = toolBox->currentIndex();
        // 检查索引是否有效，并且确保 QToolBox 中确实有足够多的页面
        if (currentIndex >= 0 && currentIndex < toolBox->count()) {
            // 获取要删除的页面（这一步是可选的，因为我们直接使用索引来删除）
            //QWidget * pageToRemove = toolBox->widget(currentIndex);
            // 删除页面
            toolBox->removeItem(currentIndex);
        }
            else {
            // 没有选中的选项卡，处理这种情况（如果需要）
            qDebug()<<"无效代码！！！";
        }
    });

    connect(ui->btnReturn, &QPushButton::clicked, [=](){
        MainWindow * mainwindow = new MainWindow();
        mainwindow->show();
        this->close();
    });

    connect(ui->btnsss,&QPushButton::clicked,[=](){
        QRadioButton * isclock = ui->radioButton;
        QRadioButton * isfinish = ui->radioButton_2;
        qDebug()<<isclock->isChecked();
        qDebug()<<isfinish->isChecked();
    });

}

AutoWindow::~AutoWindow()
{
    delete ui;
}

QList<QLineEdit*> AutoWindow :: findAllLineEdits(QWidget *parent) {
    QList<QLineEdit*> lineEdits;

    // 遍历所有子控件
    for (int i = 0; i < parent->children().count(); ++i) {
        QObject* obj = parent->children().at(i); // 假设这是你从某个地方得到的QObject指针
        QWidget* child = qobject_cast<QWidget*>(obj);

        // 检查子控件是否是 QLineEdit
        if (QLineEdit *lineEdit = qobject_cast<QLineEdit*>(child)) {
            lineEdits.append(lineEdit);
        }

        // 如果子控件本身也是一个容器（如QWidget），则递归查找
        if (QWidget *widget = qobject_cast<QWidget*>(child)) {
            lineEdits += findAllLineEdits(widget);
        }
    }

    return lineEdits;
}
