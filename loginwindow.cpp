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
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
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
        QMessageBox::information(this, "信息", "登录成功！", QMessageBox::Yes, QMessageBox::Yes);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject json = jsonDoc.object();
        User user(json["username"].toString(), json["token"].toString());
        MainWindow * mainwindow = new MainWindow();
        mainwindow->setUser(&user);
        mainwindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "警告", "登录失败，请重新检查用户名和密码是否正确！", QMessageBox::Yes, QMessageBox::Yes);
    }
    reply->deleteLater();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

