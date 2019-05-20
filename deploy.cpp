#include "deploy.h"
#include "ui_deploy.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

Deploy::Deploy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deploy)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider,&QSlider::valueChanged,this,[this](int value){
         qDebug()<<"value 1 is: "<<value;
        emit valueChanged(value);
    });
    connect(ui->returnBtn,&QPushButton::clicked,this,&Deploy::returnBtnClicked);
}

Deploy::~Deploy()
{
    delete ui;
}

void Deploy::setBackGround()
{
    this->hide();
    ui->setupUi(this);
    // 设置窗口大小
    const int w = 1200,  h = 740;
    // 将窗口至中，你必须在widget.h里#include <QDesktopWidget>
    // 以后我就不再多说了，没有include的类就自己在.h文件里include
    const int x = (QApplication::desktop()->width() - w)/2;
    const int y = (QApplication::desktop()->height() - h)/2;
    this->setGeometry(x, y, w, h);
    //不允许最大化最小化
    this->setMaximumSize(QSize(w, h));
    this->setMinimumSize(QSize(w, h));
}

void Deploy::returnBtnClicked()
{
    this->hide();

    emit closed();
}
