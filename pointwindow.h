#ifndef POINTWINDOW_H
#define POINTWINDOW_H

#include <QMainWindow>

namespace Ui {
class PointWindow;
}

class PointWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PointWindow(QWidget *parent = nullptr);
    ~PointWindow();

private:
    Ui::PointWindow *ui;
};

#endif // POINTWINDOW_H
