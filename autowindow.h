#ifndef AUTOWINDOW_H
#define AUTOWINDOW_H

#include "User.h"

#include <QMainWindow>
#include <QList>
#include <QLineEdit>

namespace Ui {
class AutoWindow;
}

class AutoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AutoWindow(QWidget *parent = nullptr);
    ~AutoWindow();
    QList<QLineEdit*> findAllLineEdits(QWidget *parent);

public:
    void setUser(User user)
    {
        this->user = user;
    }
    User getUser()
    {
        return this->user;
    }
    void setId(int id)
    {
        this->id = id;
    }
    void setMode(int mode)
    {
        this->mode = mode;
    }
    void renew();
    void sendPostRequest(const QUrl &requestedUrl, const QByteArray &data);
    void sendGetRequest(const QUrl &requestedUrl);

private slots:
    void onPostRequestFinished(QNetworkReply *reply);
    void onGetRequestFinished(QNetworkReply *reply);

private:
    int mode = 0;
    int id = 0;
    User user;
    QUrl url;
    QNetworkRequest request;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;

private:
    Ui::AutoWindow *ui;
};

#endif // AUTOWINDOW_H
