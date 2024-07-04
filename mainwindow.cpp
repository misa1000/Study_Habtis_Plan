#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "autowindow.h"
#include "studyplan.h"

#include <QDebug>
#include <QDate>
#include <QCalendarWidget>
#include <QPainter>
#include <QRadioButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->tbUnready->setCurrentIndex(0);
    ui->tbReady->setCurrentIndex(0);
    //栈控件使用
    //设置默认定位  主页
    ui->stackedWidget->setCurrentIndex(0);
    //主页按钮
    connect(ui->btnmain, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex (0);
    });
    //任务按钮
    connect (ui->btntask, &QPushButton::clicked,[=](){
        updatePage2();
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
        autowindow->setUser(this->getUser());
        autowindow->setMode(1);
        autowindow->show();
        this->close();
    });
    // 设置日历的最小和最大日期
    ui->calendarWidget->setMinimumDate(QDate(2005, 1, 1));
    ui->calendarWidget->setMaximumDate(QDate::currentDate().addYears(1));
    connect(ui->calendarWidget,&QCalendarWidget::clicked,this,&MainWindow::activatedChanged);    //点击信号

}

void MainWindow::updatePage2()
{
    QToolBox *tb1 = ui->tbUnready;
    for (int i = 0; i < tb1->count(); i++) {
        tb1->removeItem(i);
    }
    QToolBox *tb2 = ui->tbReady;
    for (int i = 0; i < tb2->count(); i++) {
        tb2->removeItem(i);
    }
    QList<StudyPlan> studyPlans = this->getUser().getStudyPlans();
    for (StudyPlan i : studyPlans) {
        int id = i.getId();
        int status = i.getStatus();
        QString topic = i.getTopic();
        QString content = i.getContent();
        QString deadline = i.getDeadLine();
        if (status == 0) {
            QWidget *widget = new QWidget();
            QVBoxLayout *vboxLayout = new QVBoxLayout();

            QLabel * lab = new QLabel("截止时间");
            QLineEdit * linewidget = new QLineEdit(deadline);
            linewidget->setEnabled(false);
            QWidget * widget1 = new QWidget();
            QHBoxLayout * hboxlayout = new QHBoxLayout();
            hboxlayout->addWidget(lab);hboxlayout->addWidget(linewidget);
            widget1->setLayout(hboxlayout);

            QLabel * lab2 = new QLabel("内容");
            QTextBrowser *textBrowser = new QTextBrowser();
            textBrowser->append(content);

            QPushButton *btn = new QPushButton("编辑任务");

            vboxLayout->addWidget(widget1);
            vboxLayout->addWidget(lab2);
            vboxLayout->addWidget(textBrowser);
            vboxLayout->addWidget(btn);

            widget->setLayout(vboxLayout);
            QToolBox *tb1 = ui->tbUnready;
            tb1->addItem(widget, topic);

            connect(btn, &QPushButton::clicked, [=](){
                editPlan(id);
            });
        }else{
            QString finish_time = i.getFinishTime();
            QDateTime finishTime = QDateTime::fromString(finish_time, "yyyy-MM-dd hh:mm:ss");
            QDateTime nowTime = QDateTime::currentDateTime();
            int days = finishTime.daysTo(nowTime);
            if (days > 7)
                continue;

            QWidget *widget = new QWidget();
            QVBoxLayout *vboxLayout = new QVBoxLayout();

            QLabel * lab = new QLabel("截止时间");
            QLineEdit * linewidget = new QLineEdit(deadline);
            linewidget->setEnabled(false);
            QWidget * widget1 = new QWidget();
            QHBoxLayout * hboxlayout = new QHBoxLayout();
            hboxlayout->addWidget(lab);hboxlayout->addWidget(linewidget);
            widget1->setLayout(hboxlayout);

            QLabel * lab2 = new QLabel("内容");
            QTextBrowser *textBrowser = new QTextBrowser();
            textBrowser->append(content);

            QPushButton *btn = new QPushButton("删除任务");

            vboxLayout->addWidget(widget1);
            vboxLayout->addWidget(lab2);
            vboxLayout->addWidget(textBrowser);
            vboxLayout->addWidget(btn);

            widget->setLayout(vboxLayout);
            QToolBox *tb2 = ui->tbReady;
            tb2->addItem(widget, topic);

            connect(btn, &QPushButton::clicked, [=](){
                QString url = ROOT"studyPlan/delete";
                url += "?id=" + QString::number(id);
                sendGetRequest(QUrl(url));
            });
        }
    }
}

void MainWindow::sendGetRequest(const QUrl &requestedUrl)
{
    url = requestedUrl;
    manager = new QNetworkAccessManager(this);
    request.setUrl(url);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setRawHeader("token", user.getToken().toLocal8Bit());
    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, [=](){
        onGetRequestFinished(reply);
    });
}

void MainWindow::onGetRequestFinished(QNetworkReply *reply)
{
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (status_code == 200) {
        QToolBox *tb = ui->tbReady;
        tb->removeItem(tb->currentIndex());
        QMessageBox::information(this, "提示", "删除成功！", QMessageBox::Yes, QMessageBox::Yes);
    } else {
        QMessageBox::warning(this, "警告", "删除失败！", QMessageBox::Yes, QMessageBox::Yes);
    }
    reply->deleteLater();
}

void MainWindow::editPlan(int id)
{
    QList<StudyPlan> studyPlans = this->getUser().getStudyPlans();
    StudyPlan *target = NULL;
    for (StudyPlan i : studyPlans) {
        if (i.getId() == id) {
            target = &i;
            break;
         }
    }
    if (target == NULL) {
        QMessageBox::warning(this, "警告", "未找到目标任务！", QMessageBox::Yes, QMessageBox::Yes);
    }

    AutoWindow *autoWindow = new AutoWindow();
    autoWindow->setUser(this->getUser());
    autoWindow->setId(id);
    autoWindow->setMode(0);

    QToolBox * box = autoWindow->findChild<QToolBox *>();

    box->removeItem(box->currentIndex());
    QWidget * widget = new QWidget();
    QVBoxLayout * vboxlayout = new QVBoxLayout();

    QLabel * lab0 = new QLabel("主题");
    QLineEdit * linewidget0 = new QLineEdit();
    QWidget * widget0 = new QWidget();
    QHBoxLayout * hboxlayout0 = new QHBoxLayout();
    hboxlayout0->addWidget(lab0);hboxlayout0->addWidget(linewidget0);
    widget0->setLayout(hboxlayout0);

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

    QLabel * lab4 = new QLabel("提醒时间");
    QLineEdit * linewidget3 = new QLineEdit();
    QWidget * widget5 = new QWidget();
    QVBoxLayout * vboxlayout2 = new QVBoxLayout();
    vboxlayout2->addWidget(lab4);vboxlayout2->addWidget(linewidget3);
    widget5->setLayout(vboxlayout2);

    QRadioButton * radio = new QRadioButton("需提醒任务");
    QWidget * widget4 = new QWidget();
    QHBoxLayout * hboxlayout3 = new QHBoxLayout();
    hboxlayout3->addWidget(radio);hboxlayout3->addWidget(widget5);
    widget4->setLayout(hboxlayout3);


    QLabel * lab3 = new QLabel("内容");

    vboxlayout->addWidget(widget0);
    vboxlayout->addWidget(widget1);
    vboxlayout->addWidget(widget2);
    vboxlayout->addWidget(widget4);
    vboxlayout->addWidget(lab3);
    QTextEdit * textwidget = new QTextEdit();
    vboxlayout->addWidget(textwidget);

    widget->setLayout(vboxlayout);
    box->addItem(widget, target->getTopic());
    int currentIndex = box->currentIndex();
    QWidget * page = box->widget(currentIndex);
    QRadioButton * radiobtn = page->findChild<QRadioButton *>();
    QList<QLineEdit *> list = autoWindow->findAllLineEdits(page);
    list.at(0)->setText(target->getTopic());
    list.at(1)->setText(QString::number(target->getPriority()));
    list.at(2)->setText(target->getDeadLine());
    if (target->getReminderTime() != NULL)
    {
        radiobtn->setChecked(true);
        list.at(3)->setText(target->getReminderTime());
    }
    QTextEdit * textedit = page->findChild<QTextEdit *>();
    textedit->setText(target->getContent());
    QPushButton *btnnew = autoWindow->findChild<QPushButton *>("btnnew");
    btnnew->hide();

    autoWindow->show();
    this->close();
}

//双击信号  日期触发
void MainWindow::activatedChanged(const QDate date)
{
    qDebug()<< "点击信号：" << date;
}

MainWindow::~MainWindow()
{
    delete ui;
}


