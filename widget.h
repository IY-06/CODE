#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //人对象的指针
    person * m_Person;

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //记录自动移动的位置
    QPoint  m_Auto_pos;

    //自动移动定时器
    QTimer * Auto_timer;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
