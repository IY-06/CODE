#include "person.h"

person::person(QWidget *parent) : QWidget(parent)
{
    //加载人所有图片资源
    for( int i = 0; i <= this->max; i++){
        QString str = QString("://13/image (%1).png").arg(i);
        this->m_Perosn_Pix.load(str);
    }
    //设置人尺寸
    this->setFixedSize(this->m_Perosn_Pix.width(),this->m_Perosn_Pix.height());

    //创建定时器对象
    this->timer = new QTimer(this);

    //监听定时器的信号
    connect(timer,&QTimer::timeout,[=](){
        QString str = QString("://13/image (%1).png").arg(this->min++);
        this->m_Perosn_Pix.load(str);
        if (this->min > this->max){
            this->min = 1;
        }

        //抛出信号
        emit changePix();
    });

    //菜单创建
    this->m_Menu = new QMenu;

    //连接菜单中退出选项的信号槽
    connect(this->m_Menu->addAction("退出"),&QAction::triggered,[=](){
        exit(0);
    });
}
//鼠标按下事件
void person::mousePressEvent(QMouseEvent * e){
    //((QWidget *)this->parent())->frameGeometry().topLeft() 获取当前主窗口的左上角坐标
    this->m_Pos = e->globalPos() - ((QWidget *)this->parent())->frameGeometry().topLeft();

    //鼠标按下的状态为真
    this->mouseDown = true;

    //如果是鼠标的右键 弹出菜单
    if (e->button() == Qt::RightButton){
        //弹出菜单
        this->m_Menu->popup(QCursor::pos());//弹出鼠标当前位置
    }
    //如果菜单 通过别的方式消失的 类对象应该继续向前飞
    connect(this->m_Menu,&QMenu::aboutToHide,[=](){
        this->mouseDown = false;//条件给改为假，就可以继续移动
    });
}

//鼠标移动事件
void person::mouseMoveEvent(QMouseEvent * e){

    //在移动过程中 反向获取 窗口最终移动的位置 eimt(发出)
    emit moving(e->globalPos() - this->m_Pos);
}
//鼠标释放事件
void person::mouseReleaseEvent(QMouseEvent *){
    //鼠标释放的时候状态为假
    this->mouseDown = false;

}
//执行动画
void person::running(){
    //启动定时器
    this->timer->start(70);
}
