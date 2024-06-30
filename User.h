#ifndef USER_H
#define USER_H

#define ROOT "http://127.0.0.1:8080/"

#include <QString>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

class User {

public:
    User(QString username, QString password, QString token)
    {
        this->username = username;
        this->password = password;
        this->token = token;
    }

public:
    QString getUsername()
    {
        return this->username;
    }
    QString getPassword()
    {
        return this->password;
    }
    QString getToken()
    {
        return this->token;
    }

private:
    QString username, password;
    QString token;
};

#endif // USER_H
