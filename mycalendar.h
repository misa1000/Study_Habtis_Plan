#ifndef MYCALENDAR_H
#define MYCALENDAR_H

#include <QCalendarWidget>
#include <QPainter>
#include <QObject>

class myCalendar : public QCalendarWidget
{
    Q_OBJECT
public:
    //explicit myCalendar(QObject *parent = nullptr);
    myCalendar(QWidget *parent = nullptr) : QCalendarWidget(parent) {
        // 初始化日历小部件
    }

protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override {
        // 调用基类的paintCell方法来绘制默认的单元格
        QCalendarWidget::paintCell(painter, rect, date);

        // 检查日期是否为星期一
        if (date.dayOfWeek() == Qt::Monday) {
            // 保存当前的画笔状态
            painter->save();

            // 设置画笔颜色为红色
            painter->setPen(Qt::red);

            // 绘制文本（通常这是由基类paintCell完成的，但在这里我们可能需要覆盖它）
            // 注意：这里可能需要一些调整，因为默认的文本位置可能在背景填充之上
            // 你可以通过获取文本的宽度和高度，然后计算正确的位置来绘制文本
            // 但为了简单起见，这里我们假设文本位置不需要调整

            // 例如，你可能想要获取默认的文本内容并绘制它（这可能需要一些额外的代码）

            // 恢复画笔状态
            painter->restore();
        }
    }

signals:

};

#endif // MYCALENDAR_H






// 在你的主窗口或其他地方使用CustomCalendarWidget
// ...
//CustomCalendarWidget *calendar = new CustomCalendarWidget(this);
// 设置日历小部件的属性等
// ...
