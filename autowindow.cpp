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
    if (this->mode == 0)
        ui->btnnew->hide();
    connect(ui->btnnew,&QPushButton::clicked,[=](){
        ui->frame->show();
    });
    connect(ui->btnsure,&QPushButton::clicked,[=](){
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
        QWidget * currentWidget = toolBox->widget(currentIndex);
        // 现在你可以对 currentWidget 进行操作了
        QList<QLineEdit *> list = findAllLineEdits(currentWidget);
        QLineEdit * text0 = list.at(0);
        QString topic = text0->text();
        // 检查是否有选中的选项卡
        if ((currentIndex != -1) && (topic != "示例任务")) {

            QLineEdit * text1 = list.at(1);
            QString value = text1->text();
            int priority = value.toInt();

            QLineEdit * text2 = list.at(2);
            QString deadline = text2->text();

            QLineEdit * text3 = list.at(3);
            QString reminderTime = text3->text();

            QTextEdit * text = currentWidget->findChild<QTextEdit *>();
            QString content = text->toPlainText();

            QRadioButton * isneed = currentWidget->findChild<QRadioButton *>();

            QString url = NULL;
            QJsonObject json;
            if (this->mode == 0){
                url = ROOT"studyPlan/update";
                json["id"] = this->id;
            }
            else
                url = ROOT"studyPlan/add";
            json["topic"] = topic;
            json["priority"] = priority;
            json["deadline"] = deadline;
            if (isneed->isChecked())
                json["reminderTime"] = reminderTime;
            json["content"] = content;
            QJsonDocument jsonDoc(json);
            QByteArray data = jsonDoc.toJson();
            sendPostRequest(QUrl(url), data);
        } else {
            QMessageBox::warning(this, "警告", "当前无任务选项！", QMessageBox::Yes, QMessageBox::Yes);
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
            if (this->id != 0) {
                QString url = ROOT"studyPlan/delete";
                QJsonObject json;
                json["id"] = this->id;
                QJsonDocument jsonDoc(json);
                QByteArray data = jsonDoc.toJson();
                sendPostRequest(QUrl(url), data);
            }
            toolBox->removeItem(currentIndex);
        }
            else {
            // 没有选中的选项卡，处理这种情况（如果需要）
            QMessageBox::warning(this, "警告", "当前无任务选项！", QMessageBox::Yes, QMessageBox::Yes);
        }
    });

    connect(ui->btnReturn, &QPushButton::clicked, [=](){
        MainWindow * mainwindow = new MainWindow();
        mainwindow->setUser(this->user);
        mainwindow->show();
        this->close();
    });

    connect(ui->btncheck,&QPushButton::clicked,[=](){
        QMessageBox::StandardButton result = QMessageBox::question(this, "提示", "是否确认完成", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        if(result ==  QMessageBox::Yes){
            if (this->id != 0) {
                QString url = ROOT"studyPlan/update";
                QJsonObject json;
                json["id"] = this->id;
                json["status"] = 1;
                QJsonDocument jsonDoc(json);
                QByteArray data = jsonDoc.toJson();
                sendPostRequest(QUrl(url), data);
                MainWindow * mainwindow = new MainWindow();
                mainwindow->setUser(this->user);
                mainwindow->show();
                this->close();
            }else {
                QMessageBox::warning(this, "警告", "当前任务未保存！", QMessageBox::Yes, QMessageBox::Yes);
            }
        }
    });
}

void AutoWindow::sendPostRequest(const QUrl &requestedUrl, const QByteArray &data)
{
    url = requestedUrl;
    manager = new QNetworkAccessManager(this);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setRawHeader("token", user->getToken().toLocal8Bit());
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    reply = manager->post(request, data);
    connect(reply, &QNetworkReply::finished, [=](){
        onPostRequestFinished(reply);
    });
}

void AutoWindow::onPostRequestFinished(QNetworkReply *reply)
{
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (status_code == 200) {
        QByteArray replyData = reply->readAll();
        if (!replyData.isEmpty()) {
            QJsonDocument jsonDoc = QJsonDocument::fromJson(replyData);
            QJsonObject json = jsonDoc.object();
            this->setId(json["id"].toInt());
            this->setMode(0);
            ui->btnnew->hide();
            QMessageBox::information(this, "信息", "保存成功！", QMessageBox::Yes, QMessageBox::Yes);
        }else{
            QMessageBox::information(this, "信息", "操作成功！", QMessageBox::Yes, QMessageBox::Yes);
        }
    } else {
        QMessageBox::warning(this, "警告", "操作失败！", QMessageBox::Yes, QMessageBox::Yes);
    }
    reply->deleteLater();
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


AutoWindow::~AutoWindow()
{
    delete ui;
}

