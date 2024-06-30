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
    void setUser(User *user)
    {
        this->user = user;
    }

private:
    User *user;
    QUrl url;
    QNetworkRequest request;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;

private:
    Ui::AutoWindow *ui;
};

#endif // AUTOWINDOW_H
