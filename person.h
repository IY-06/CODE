#ifndef PERSON_H
#define PERSON_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>
#include <QMenu>

class person : public QWidget
{
    Q_OBJECT
public:
    explicit person(QWidget *parent = nullptr);

    //人显示图片
    QPixmap m_Perosn_Pix;

    //最小值下标
    int min = 0;

    //最大值下标
    int max = 17;

    //定时器
    QTimer * timer;

    //执行动画
    void running();

    //记录分量坐标
    QPoint m_Pos;

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *);

    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *);

    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *);

    //记录鼠标按下的状态
    bool mouseDown = false;

    //创建菜单
    QMenu * m_Menu;


signals:

    //自定义信号，代表正在切换图片的信号
    void changePix();

    //自定义信号 拖拽后 主场景应该移动的位置
    void moving(QPoint point);


};

#endif // PERSON_H
