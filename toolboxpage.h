#ifndef TOOLBOXPAGE_H
#define TOOLBOXPAGE_H

#include <QMainWindow>
#include <QWidget>
#include <QWidget>
#include <QPushButton>

class ToolboxPage : public QWidget
{
    Q_OBJECT
public:
    explicit ToolboxPage(QWidget *parent = nullptr);
//    MyWidget(QWidget * parent)  : QWidget(parent){
//        // 创建一个子控件（例如，一个按钮）
//        QPushButton *button = new QPushButton("Click me!", this);

//        // 设置子控件的位置（可选，如果你不使用布局管理器）
//        // button->move(50, 50); // 这里只是一个示例位置

//        // 如果你想使用布局管理器，可以这样做：
//        // QVBoxLayout *layout = new QVBoxLayout(this);
//        // layout->addWidget(button);
//        // setLayout(layout);
//    }

signals:

};

#endif // TOOLBOXPAGE_H



