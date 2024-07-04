#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "autowindow.h"
#include "StudyPlan.h"

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
    QString url = ROOT"/studyPlan/getAll";
    sendGetRequest(QUrl(url));
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

void MainWindow::sendGetRequest(const QUrl &requestedUrl)
{
    url = requestedUrl;
    manager = new QNetworkAccessManager(this);
    request.setUrl(url);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setRawHeader("token", user->getToken().toLocal8Bit());
    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, [=](){
        onGetRequestFinished(reply);
    });
}

void MainWindow::onGetRequestFinished(QNetworkReply *reply){
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json = jsonDoc.object();
    QJsonArray data = json["data"].toArray();
    QList<StudyPlan> studyPlans;
    for (QJsonValue it : data) {
        StudyPlan studyPlan(
            it["id"].toInt(), it["username"].toString(), it["deadline"].toString(),
            it["topic"].toString(), it["priority"].toInt(), it["content"].toString(),
            it["create_time"].toString(), it["update_time"].toString(),
            it["reminder_time"].toString(), it["finish_time"].toString(),
            it["status"].toInt()
        );
        studyPlans.append(studyPlan);
    }
    this->getUser()->setStudyPlans(studyPlans);
}

void MainWindow::updatePage2()
{
    QToolBox *tb1 = ui->tbUnready;
    for (int i = 0; i < tb1->count(); i++) {
        tb1->removeItem(i);
    }
    QToolBox *tb2 = ui->tbReady;
    for (int i = 0; i < tb1->count(); i++) {
        tb2->removeItem(i);
    }
    QList<StudyPlan> studyPlans = this->getUser()->getStudyPlans();
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

            vboxLayout->addWidget(widget1);
            vboxLayout->addWidget(lab2);
            vboxLayout->addWidget(textBrowser);

            widget->setLayout(vboxLayout);
            QToolBox *tb2 = ui->tbReady;
            tb2->addItem(widget, topic);
        }
    }
}

void MainWindow::editPlan(int id)
{
    QList<StudyPlan> studyPlans = this->getUser()->getStudyPlans();
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

    int currentIndex = box->currentIndex();
    box->itemText(currentIndex) = target->getTopic();
    QWidget * page = box->widget(currentIndex);
    QRadioButton * radiobtn = page->findChild<QRadioButton *>();
    QList<QLineEdit *> list = autoWindow->findAllLineEdits(page);
    list.at(0)->setText(target->getTopic());
    list.at(1)->setText(QString(target->getPriority()));
    list.at(2)->setText(target->getDeadLine());
    if (target->getReminderTime() != NULL)
        radiobtn->setChecked(true);
        list.at(3)->setText(target->getReminderTime());
    QTextEdit * textedit = page->findChild<QTextEdit *>();
    textedit->setText(target->getContent());
    QPushButton *btnnew = autoWindow->findChild<QPushButton *>("btnnew");
    btnnew->setVisible(false);

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


