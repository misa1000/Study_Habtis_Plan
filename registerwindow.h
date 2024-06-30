#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <User.h>

#include <QMainWindow>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();
    void sendPostRequest(const QUrl &requestedUrl, const QByteArray &data);

private slots:
    void onPostRequestFinished(QNetworkReply *reply);

private:
    QUrl url;
    QNetworkRequest request;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
