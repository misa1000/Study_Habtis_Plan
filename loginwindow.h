#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "User.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    void setUser(User *user)
    {
        this->user = user;
    }
    void sendPostRequest(const QUrl &requestedUrl, const QByteArray &data);

private slots:
    void onPostRequestFinished(QNetworkReply *reply);

private:
    User *user;
    QUrl url;
    QNetworkRequest request;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;

private:
    Ui::LoginWindow *ui;

};
#endif // LOGINWINDOW_H
