#include "mainwindow.h"
#include "loginwindow.h"
#include "registerwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow l;
    l.show();
    return a.exec();
}
