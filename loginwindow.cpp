#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "QLineEdit"
#include "registerwindow.h"
#include "mainwindow.h"

#include <QRegularExpressionValidator>
#include <QDebug>
#include <QPushButton>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[\u4e00-\u9fa5_a-zA-Z0-9_]{3,10}")));
    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]{4,9}")));

    connect(ui->pushButton,&QPushButton::clicked, [=](){
        QString value1 = ui->lineEdit->text();
        QString value2 = ui->lineEdit_2->text();
        if ((value1.length() >= 3) && (value1.length() <= 10))
        {
            if ((value2.length() >= 4) && (value2.length() <= 9))
            {
                QString url = ROOT"user/login";
                QJsonObject json;
                json["username"] = value1;
                json["password"] = value2;
                QJsonDocument jsonDoc(json);
                QByteArray data = jsonDoc.toJson();
                sendPostRequest(QUrl(url), data);
            }else{
                QMessageBox::warning(this, "警告", "密码长度应在4~9个字符之间！", QMessageBox::Yes, QMessageBox::Yes);
            }
        }else{
            QMessageBox::warning(this, "警告", "用户名长度应在3~10个字符之间！", QMessageBox::Yes, QMessageBox::Yes);
        }
    });

    connect(ui->pushButton_2,&QPushButton::clicked, [=](){
        this->close();
    });

    connect(ui->pushButton_3,&QPushButton::clicked, [=](){
        RegisterWindow * registerwindow = new RegisterWindow();
        registerwindow->show();
        this->close();
    });
}

void LoginWindow::sendPostRequest(const QUrl &requestedUrl, const QByteArray &data)
{
    url = requestedUrl;
    manager = new QNetworkAccessManager(this);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    reply = manager->post(request, data);
    connect(reply, &QNetworkReply::finished, [=](){
        onPostRequestFinished(reply);
    });
}

void LoginWindow::onPostRequestFinished(QNetworkReply *reply)
{
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (status_code == 200) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject json = jsonDoc.object();
        json = json["data"].toObject();
        if (!json.isEmpty())
        {
            user = User(json["username"].toString(), json["token"].toString());
            QMessageBox::information(this, "信息", "登录成功！", QMessageBox::Yes, QMessageBox::Yes);
            QString url = ROOT"/studyPlan/getAll";
            sendGetRequest(QUrl(url));
        }else {
            QMessageBox::warning(this, "警告", "登录失败，请重新检查用户名和密码是否正确！", QMessageBox::Yes, QMessageBox::Yes);
        }
    }
    reply->deleteLater();
}

void LoginWindow::sendGetRequest(const QUrl &requestedUrl)
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

void LoginWindow::onGetRequestFinished(QNetworkReply *reply){
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (status_code == 200)
    {
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
        user.setStudyPlans(&studyPlans);
        MainWindow * mainwindow = new MainWindow();
        mainwindow->setUser(this->user);
        mainwindow->show();
        this->close();
    }else {
        ;
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

