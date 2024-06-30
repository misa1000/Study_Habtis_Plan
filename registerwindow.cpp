#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "loginwindow.h"

#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QPushButton>

RegisterWindow::RegisterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[\u4e00-\u9fa5]{1,6}")));
    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]{9}")));
    ui->lineEdit_3->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]{9}")));

    connect(ui->pushButton,&QPushButton::clicked, [=](){
        QString value1 = ui->lineEdit->text();
        QString value2 = ui->lineEdit_2->text();
        QString value3 = ui->lineEdit_3->text();
        if(value2 == value3){
            QString url = ROOT"user/register";
            QJsonObject json;
            json["username"] = value1;
            json["password"] = value2;
            QJsonDocument jsonDoc(json);
            QByteArray data = jsonDoc.toJson();
            sendPostRequest(QUrl(url), data);
        }else{
            QMessageBox::warning(this, "警告", "密码不一致，请重新输入！", QMessageBox::Yes, QMessageBox::Yes);
        }
    });

    connect(ui->pushButton_2,&QPushButton::clicked, [=](){
        this->close();
    });

    connect(ui->pushButton_3, &QPushButton::clicked, [=](){
        LoginWindow * loginwindow = new LoginWindow();
        loginwindow->setWindowModality(Qt::ApplicationModal);
        loginwindow->show();
        this->close();
    });

}

void RegisterWindow::sendPostRequest(const QUrl &requestedUrl, const QByteArray &data)
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

void RegisterWindow::onPostRequestFinished(QNetworkReply *reply)
{
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (status_code == 200) {
        QMessageBox::information(this, "信息", "注册成功！", QMessageBox::Yes, QMessageBox::Yes);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject json = jsonDoc.object();
        User user(json["username"].toString(), json["password"].toString(), json["token"].toString());
        LoginWindow * loginwindow = new LoginWindow();
        loginwindow->setUser(&user);
        loginwindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "警告", "注册失败！", QMessageBox::Yes, QMessageBox::Yes);
    }
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}
