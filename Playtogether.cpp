#include "playtogether.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QGroupBox>
#include <QRadioButton>
#include  <QPushButton>
#include <QApplication>
#include <QSoundEffect>
#include <QMessageBox>
#include <QDesktopWidget>

PlayTogether::PlayTogether(QWidget *parent) : QWidget(parent)
{
    setBackground();
    connect(m_beginBtn, &QPushButton::clicked,this,&PlayTogether::beginBtnClicked);
    connect(m_returnBtn, &QPushButton::clicked,this,&PlayTogether::returnBtnClicked);
}

void PlayTogether::paintEvent(QPaintEvent *event)
{
    //画背景
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,1200,740),QPixmap(":/images/qipan.png"));


    //画棋子
    for(int i=0;i!=19;++i)
        for(int j=0;j!=19;++j)
        {
            if(chess[i][j]==1)
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/BBlack.png"));
            if(chess[i][j]==2)
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/BWhite.png"));
        }

    painter.setBrush(Qt::red);
    painter.drawEllipse(QRect(chess_x*30+212,chess_y*30+42,8,8));
}

void PlayTogether::mouseReleaseEvent(QMouseEvent *event)
{
    if(begin_flag==0) return;   //游戏未开始，此时直接返回

    int x=event->x(),y=event->y();
    if(x<210||x>770||y<40||y>600) return;         //鼠标瞎按越界可以吗？不可以！

    chess_x=(x-216+14)/30;chess_y=(y-46+14)/30; //近似算法，得到二维数组坐标（x坐标加半径除以间距）

    if(chess[chess_x][chess_y]!=0) return;     //至关重要，如果点击地方有棋子，那么直接返回不操作

    //根据颜色给棋盘赋值，随之切换
    chess[chess_x][chess_y]=color_flag;
    color_flag=3 - color_flag;

    m_chessDownEffect->play();
    this->rule(chess_x,chess_y);                //进行规则审查，判断是否分出了胜负
    update();
}

void PlayTogether::beginBtnClicked()
{
    m_clickOneEffect->play();

     //1代表黑棋，2代表白棋
    if(m_blackRadioBtn->isChecked()) color_flag=1;
    else if(m_whiteRadioBtn->isChecked())color_flag=2;

    memset(chess,0,sizeof(chess));
    update();
    begin_flag=1;
    win_flag=0;
    m_beginBtn->setStyleSheet("QPushButton{border-image: url(:/images/AgainBegin.png);}");
}

void PlayTogether::returnBtnClicked()
{
    m_clickOneEffect->play();
    emit closed();
    this->hide();
}

void PlayTogether::setBackground()
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
    this->hide();

    //添加按钮，设置样式表
    m_groupBox = new QGroupBox(this);
    m_groupBox->setObjectName(QString::fromUtf8("groupBox"));
    m_groupBox->setGeometry(QRect(830, 70, 211, 161));
    m_groupBox->setFlat(true);
    m_groupBox->setStyleSheet("QGroupBox{border:0 px}");

    m_blackRadioBtn = new QRadioButton(m_groupBox);
    m_blackRadioBtn->setGeometry(QRect(40, 30, 141, 51));
    m_blackRadioBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/BlackFirst.png);"));

    m_blackRadioBtn->setChecked(true);
    m_whiteRadioBtn = new QRadioButton(m_groupBox);
    m_whiteRadioBtn->setGeometry(QRect(40, 90, 141, 51));
    m_whiteRadioBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/WhiteFirst.png);"));

    m_returnBtn = new QPushButton(this);
    m_returnBtn->setObjectName(QString::fromUtf8("ReturnButton"));
    m_returnBtn->setGeometry(QRect(860, 300, 161, 71));
    m_returnBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/Return.png);"));

    m_beginBtn = new QPushButton(this);
    m_beginBtn->setObjectName(QString::fromUtf8("BeginButton"));
    m_beginBtn->setGeometry(QRect(420, 600, 121, 121));
    m_beginBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/BeginGame.png);"));

    //设置音效
    m_chessDownEffect=new QSoundEffect(this);
    m_chessDownEffect->setSource(QUrl::fromLocalFile(":/sound/chessone(1).wav"));
    m_clickOneEffect=new QSoundEffect(this);
    m_clickOneEffect->setSource(QUrl::fromLocalFile(":/sound/clickOne.wav"));
}

bool PlayTogether::rule(int chess_x, int chess_y)
{
    int length=0;
    int i=chess_x;int j=chess_y;

    //水平方向判断
    while(chess[i][j]==chess[chess_x][chess_y])
    {
        ++length;
        ++i;
    }
    i=chess_x-1;
    while(chess[i][j]==chess[chess_x][chess_y])
    {
        ++length;
        --i;
    }
    if(length>=5) win_flag=1;

    //竖直方向判断
    i=chess_x;length=0;
    while(chess[i][j]==chess[chess_x][chess_y])
    {
        ++length;
        ++j;
    }
    j=chess_y-1;
    while(chess[i][j]==chess[chess_x][chess_y])
    {
        ++length;
        --j;
    }
    if(length>=5) win_flag=1;

    // /方向判断
    j=chess_y;length=0;
    while(chess[i][j]==chess[chess_x][chess_y])
    {
        ++length;
        ++i;--j;
    }
    i=chess_x-1;j=chess_y+1;
    while(chess[i][j]==chess[chess_x][chess_y])
    {
        ++length;
        --i;++j;
    }
    if(length>=5) win_flag=1;

    //\方向判断
    i=chess_x;j=chess_y;length=0;
    while(chess[i][j]==chess[chess_x][chess_y])
    {
        ++length;
        ++i;++j;
    }
    i=chess_x-1;j=chess_y-1;
    while(chess[i][j]==chess[chess_x][chess_y])
    {
        ++length;
        --i;--j;
    }
    if(length>=5) win_flag=1;

    //判断胜利是否
    if(win_flag==1)
    {
        judge();
        return true;
    }
    return false;
}

void PlayTogether::judge()
{
    int ret =0;
    //弹出胜负结果会话框
    if(color_flag==1){
        ret = QMessageBox::information(this,tr("胜负已分！"),tr("恭喜白棋获胜！\n再来一局？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    }
    else{
        ret = QMessageBox::information(this,tr("胜负已分！"),tr("恭喜黑棋获胜！\n再来一局？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    }

    //根据玩家判断做出选项
    if(ret==QMessageBox::Yes)
    {
        update();
        beginBtnClicked();
    }
    else if(ret==QMessageBox::No)
    {
        returnBtnClicked();
    }
}
