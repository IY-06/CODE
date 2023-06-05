#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QPainter>
#include <QDesktopWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置图标
    this->setWindowIcon(QIcon("://img/1.ioc"));

    //创建人的对象
    this->m_Person = new person;

    //将人对象显示到窗口中
    this->m_Person->setParent(this);

    //启动定时器
    this->m_Person->running();

    //监听人切图的信号
    connect(this->m_Person,&person::changePix,[=](){
        update();//手动调用绘图事件

    });

    //监听人移动拖拽的信号
    connect(this->m_Person,&person::moving,[=](QPoint point){
        this->move(point);

        m_Auto_pos = point;//鼠标移动的时候，更新当前窗口的位置
    });

    //创建自动移动定时器对象
    this->Auto_timer = new QTimer(this);

    //启动定时器
    this->Auto_timer->start(50);

    //获取屏幕
    QDesktopWidget * desk = QApplication::desktop();
    //监听定时器
    connect(this->Auto_timer,&QTimer::timeout,[=](){
        //鼠标没有按下的时候，才能向前移动
        if (this->m_Person->mouseDown != true){
        this->m_Auto_pos.setX(this->m_Auto_pos.x()+10);
        }

        if (this->m_Auto_pos.x() > desk->width()){//如果更新后的位置大于桌面宽度
            this->m_Auto_pos.setX(-this->m_Person->width());//则将类对象的位置设置(x坐标）为负值的类对象图片的宽度
        }
        //窗口同步移动
        this->move(this->m_Auto_pos);
    });

    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    //设置透明窗体 120号素性
    this->setAttribute(Qt::WA_TranslucentBackground);

    //设置窗口顶层
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    //设置起始Y位置
    this->m_Auto_pos.setY(desk->height()*1.057 - this->m_Person->height());
}
//重写绘图事件
void Widget::paintEvent(QPaintEvent *){
    QPainter painter(this);


    painter.drawPixmap(0,0,this->m_Person->m_Perosn_Pix);
}
Widget::~Widget()
{
    delete ui;
}
