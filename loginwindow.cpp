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
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[\u4e00-\u9fa5]{1,6}")));
    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]{9}")));

    connect(ui->pushButton,&QPushButton::clicked, [=](){
        QString value1 = ui->lineEdit->text();
        QString value2 = ui->lineEdit_2->text();
        QString url = ROOT"user/login";
        QJsonObject json;
        json["username"] = value1;
        json["password"] = value2;
        QJsonDocument jsonDoc(json);
        QByteArray data = jsonDoc.toJson();
        sendPostRequest(QUrl(url), data);
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
        QMessageBox::information(this, "信息", "登录成功！", QMessageBox::Yes, QMessageBox::Yes);
        MainWindow * mainwindow = new MainWindow();
        mainwindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "警告", "登录失败，请重新检查用户名和密码是否正确！", QMessageBox::Yes, QMessageBox::Yes);
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

