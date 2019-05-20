#include "client.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QPixmap>

Client::Client(QWidget *parent) :
    QWidget(parent)
{
    //背景音乐
    m_music = new MusicThread;
    m_music->start();
    //四个模块
    m_playTogether = new PlayTogether;
    m_playWithComputer = new PlayWithComputer;
    m_playOnline = new PlayOnline;
    m_deploy = new Deploy;

    connect(m_deploy,&Deploy::valueChanged,this,[this](int value){
        this->m_music->doVolumeChanged(value);
    });
    setBackground();
    openOrCloseFunction();
    showAnimation();
}

Client::~Client()
{
    delete m_music;
    delete m_playTogether;
    delete m_playWithComputer;
    delete m_playOnline;
}

void Client::setBackground()
{
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

    //设置按钮位置大小样式
    btnPeopleTogether= new QPushButton(this);
    btnPeopleTogether->setGeometry(460,90,240,90);
    btnPeopleTogether->setStyleSheet("QPushButton{border-image:url(:/images/PeoPleTogether.png)}");

    btnPeopleAndComputer = new QPushButton(this);
    btnPeopleAndComputer->setGeometry(460,200,240,90);
    btnPeopleAndComputer->setStyleSheet("QPushButton{border-image:url(:/images/PeopleAndComputer.png)}");

    btnOnline = new QPushButton(this);
    btnOnline->setGeometry(460,310,240,90);
    btnOnline->setStyleSheet("QPushButton{border-image:url(:/images/Online.png)}");

    btnDeploy = new QPushButton(this);
    btnDeploy->setGeometry(460,420,240,90);
    btnDeploy->setStyleSheet("QPushButton{border-image:url(:/images/Deploy.png)}");

    //按钮单击音效
    effect=new QSoundEffect(this);
    effect->setSource(QUrl::fromLocalFile(":/sound/clickOne.wav"));
    effect->setVolume(0.3);
}

void Client::showAnimation()
{
    QPropertyAnimation *animation1=new QPropertyAnimation(btnPeopleTogether,"geometry");
    animation1->setDuration(2000);
    animation1->setStartValue(QRect(460,0,240,90));
    animation1->setEndValue(QRect(460,90,240,90));
    animation1->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation *animation2=new QPropertyAnimation(btnPeopleAndComputer,"geometry");
    animation2->setDuration(2000);
    animation2->setStartValue(QRect(0,200,240,90));
    animation2->setEndValue(QRect(460,200,240,90));
    animation2->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation *animation3=new QPropertyAnimation(btnOnline,"geometry");
    animation3->setDuration(2000);
    animation3->setStartValue(QRect(1200,310,240,90));
    animation3->setEndValue(QRect(460,310,240,90));
    animation3->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation *animation4=new QPropertyAnimation(btnDeploy,"geometry");
    animation4->setDuration(2000);
    animation4->setStartValue(QRect(460,740,240,90));
    animation4->setEndValue(QRect(460,420,240,90));
    animation4->setEasingCurve(QEasingCurve::OutBounce);



    //并行动画组
    group = new QParallelAnimationGroup(this);
    group->addAnimation(animation1);
    group->addAnimation(animation2);
    group->addAnimation(animation3);
    group->addAnimation(animation4);
    group->start();
}

void Client::openOrCloseFunction()
{

    //开启功能模板
    connect(btnPeopleTogether,&QPushButton::clicked,this,[this](){
        effect->play();
        this->hide();
        m_playTogether ->show();
    });
    connect(btnPeopleAndComputer,&QPushButton::clicked,this,[this](){
        effect->play();
        this->hide();
        m_playWithComputer ->show();
    });
    connect(btnOnline,&QPushButton::clicked,this,[this](){
        effect->play();
        this->hide();
        m_playOnline->startServer();
        m_playOnline ->show();
    });
    connect(btnDeploy,&QPushButton::clicked,this,[this](){
        effect->play();
        this->hide();
        m_deploy ->show();
    });

    //关闭功能模板
    connect(m_playTogether,&PlayTogether::closed,this,[this](){
        this->show();
        showAnimation();
    });
    connect(m_playWithComputer,&PlayWithComputer::closed,this,[this](){
        this->show();
        showAnimation();
    });
    connect(m_playOnline,&PlayOnline::closed,this,[this](){
        this->show();
        showAnimation();
    });

    connect(m_deploy,&Deploy::closed,this,[this](){
      this->show();
    });
}

void Client::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,1200,740),QPixmap(":/images/background.png"));
}
