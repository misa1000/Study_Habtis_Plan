#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "User.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void activatedChanged(const QDate date);
    void updatePage2();
    void editPlan(int id);

public:
    void setUser(User *user)
    {
        this->user = user;
    }
    User *getUser()
    {
        return this->user;
    }
    void sendGetRequest(const QUrl &requestedUrl);

private slots:
    void onGetRequestFinished(QNetworkReply *reply);

private:
    User *user;
    QUrl url;
    QNetworkRequest request;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
