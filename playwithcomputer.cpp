#include "playwithcomputer.h"
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

PlayWithComputer::PlayWithComputer(QWidget *parent) : QWidget(parent)
{
    setBackground();
    connect(m_returnBtn, &QPushButton::clicked,this,&PlayWithComputer::returnBtnClicked);
    connect(m_regretBtn, &QPushButton::clicked,this,&PlayWithComputer::regretBtnClicked);
    connect(m_beginBtn,&QPushButton::clicked,this,&PlayWithComputer::beginBtnClicked);
}

void PlayWithComputer::setBackground()
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

    //先手者按钮组
    m_groupBox_PlayerFirst = new QGroupBox(this);
    m_groupBox_PlayerFirst->setGeometry(QRect(830, 0, 211, 161));
    m_groupBox_PlayerFirst->setStyleSheet("QGroupBox {border:0px;}");
    m_groupBox_PlayerFirst->setFlat(true);
    m_playerRadioBtn = new QRadioButton(m_groupBox_PlayerFirst);
    m_playerRadioBtn->setGeometry(QRect(40, 20, 141, 51));
    m_playerRadioBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/PlayerFirst.png);"));
    m_playerRadioBtn->setChecked(true);
    connect(m_playerRadioBtn,&QPushButton::clicked,this,[this](){m_clickOneEffect->play();});
    m_computerRadioBtn = new QRadioButton(m_groupBox_PlayerFirst);
    m_computerRadioBtn->setGeometry(QRect(40, 80, 141, 51));
    m_computerRadioBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/ComputerFirst.png);"));
    connect(m_computerRadioBtn,&QPushButton::clicked,this,[this](){m_clickOneEffect->play();});
    //先手颜色按钮组
    m_groupBox_ColorFirst = new QGroupBox(this);
    m_groupBox_ColorFirst->setGeometry(QRect(830, 140, 211, 161));
    m_groupBox_ColorFirst->setStyleSheet(QString::fromUtf8("border-width:0px;"));
    m_groupBox_ColorFirst->setStyleSheet("QGroupBox {border:0px;}");
    m_groupBox_ColorFirst->setFlat(true);
    m_blackRadioBtn = new QRadioButton(m_groupBox_ColorFirst);
    m_blackRadioBtn->setGeometry(QRect(40, 30, 141, 51));
    m_blackRadioBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/BlackFirst.png);"));
    m_blackRadioBtn->setChecked(true);
    connect(m_blackRadioBtn,&QPushButton::clicked,this,[this](){m_clickOneEffect->play();});
    m_whiteRadioBtn = new QRadioButton(m_groupBox_ColorFirst);
    m_whiteRadioBtn->setGeometry(QRect(40, 90, 141, 51));
    m_whiteRadioBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/WhiteFirst.png);"));
    connect(m_whiteRadioBtn,&QPushButton::clicked,this,[this](){m_clickOneEffect->play();});

    //返回主菜单按钮
    m_returnBtn = new QPushButton(this);
    m_returnBtn->setGeometry(QRect(860, 300, 161, 71));
    m_returnBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/Return.png);"));
    m_beginBtn = new QPushButton(this);
    m_beginBtn->setGeometry(QRect(420, 600, 121, 121));
    m_beginBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/BeginGame.png);"));

    //悔棋按钮
    m_regretBtn = new QPushButton(this);
    m_regretBtn->setGeometry(QRect(580, 650, 101, 45));
    m_regretBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/Regret.png);"));

    //音效设置
    m_chessDownEffect =new QSoundEffect(this);
    m_chessDownEffect->setSource(QUrl::fromLocalFile(":/sound/chessone(1).wav"));

    m_winEffect = new QSoundEffect(this);
    m_winEffect->setSource(QUrl::fromLocalFile(":/sound/win.wav"));

    m_loseEffect = new QSoundEffect(this);
    m_loseEffect->setSource(QUrl::fromLocalFile(":/sound/lose.wav"));

    m_clickOneEffect=new QSoundEffect(this);
    m_clickOneEffect->setSource(QUrl::fromLocalFile(":/sound/clickOne.wav"));
}

int PlayWithComputer::rule(int chess_x, int chess_y)
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

void PlayWithComputer::judge()
{
    int ret =0;
    //弹出胜负结果会话框
    if((m_computerRadioBtn->isChecked()&&
        ((m_blackRadioBtn->isChecked()&&color_flag==2)||(m_whiteRadioBtn->isChecked()&&color_flag==1)))
            ||
            (m_playerRadioBtn->isChecked()&&
             ((m_blackRadioBtn->isChecked()&&color_flag==1)||(m_whiteRadioBtn->isChecked()&&color_flag==2))))
    {
        m_clickOneEffect->play();
        ret=QMessageBox::information(this,tr("胜负已分！"),tr("恭喜人机获胜！\n菜鸡，再来一局？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    }
    else
    {
        m_clickOneEffect->play();
        ret=QMessageBox::information(this,tr("胜负已分！"),tr("你居然赢了！\n要不要再来一局？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    }

    //根据玩家判断做出选项
    if(ret==QMessageBox::Yes)
    {
        beginBtnClicked();
    }
    else if(ret==QMessageBox::No)
    {
        returnBtnClicked();
    }
}

void PlayWithComputer::actionByAi()
{
    int temp=0,maxsource=0;maxsource_x=0,maxsource_y=0;
    for(int i=0;i!=19;++i)
        for(int j=0;j!=19;++j)
        {
            if(chess[i][j]==0)
            {
                temp=value(i,j);
                if(temp>=maxsource)
                {
                    maxsource_x=i;
                    maxsource_y=j;
                    maxsource=temp;
                }
            }
        }
    chess[maxsource_x][maxsource_y]=color_flag;
    color_flag = 3 - color_flag;
    this->rule(maxsource_x,maxsource_y);
    renji_flag=0;
    computerList.append(qMakePair(maxsource_x,maxsource_y));
    update();
}

int PlayWithComputer::value(int i, int j)
{
    int rotate=1,Value=0,source1,source2,score1,score2,X1,X2,Y1,Y2,Z1,Z2,temp;

    /*排除临界的32种棋型，因为会不断检查是够决出胜负，所以图上最多的为四子连珠，分敌我两种情况，于是：
     *            己冲，己活
     *      |自己->己空冲，己空活
     * 棋型->
     *      |对手->对冲，对活
     *             对空冲，对空活
     * 又因为每种棋型又分1-4个子的四种情况,所以共有32种棋型
     * */
    int V[2][4][4]={{{40,700,6000,20000},{6,10,600,20000},{20,670,5400,0},{6,10,500,0}},
                    {{30,300,2500,15000},{2,8,300,9000},{26,160,0,0},{4,20,300,0}}};
    //rotate代表角度，代表了八个方向;以向右为1，则逆时针分别有2，3，4，5，6，7，8
    while(rotate!=5)
    {
        source1=chessType(rotate,i,j); rotate+=4;
        source2=chessType(rotate,i,j); rotate-=3;       //分别代表两个相反方向的棋型


        if(source1>source2)                             //调整使source1<source2
        {
            temp=source1;source1=source2;source2=temp;
        }

        score1=source1; score2=source2;
        Z1=score1%10;score1/=10;Y1=score1%10;score1/=10;X1=score1%10;
        Z2=score2%10;score2/=10;Y2=score2%10;score2/=10;X2=score2%10;

        //对边界空，边界冲，临界三种情况分别赋值
        if(source1==-1)
        {
            if(source2<0) {Value+=0;continue;}
            else Value+=V[X2][Y2][Z2]+5; continue;
        }
        if(source1==-2)
        {
            if(source2<0) {Value+=0;continue;}
            else Value+=V[X2][Y2][Z2]/2; continue;
        }
        if(source1==-3)
        {
            if(source2<0) {Value+=0;continue;}
            else Value+=V[X2][Y2][Z2]/3; continue;
        }
        //己活己活，己活己冲，对活对活，对活对冲四种情况赋值
        if(((source1>=0&&source1<=3)&&((source2>=0&&source2<=3)||(source2>=10&&source2<=13)))
                ||((source1>=100&&source1<=103)&&((source2>=100&&source2<=103)||(source2>=110&&source2<=113))))
        {
            if(Z1+Z2>=2) {Value+=V[X2][Y2][3];continue;}
            else {Value+=V[X2][Y2][Z1+Z2+1]; continue;}
        }
        //己冲己冲 对冲对冲情况赋值  因为两边被封死，如果落子能凑出5个子，那应该给与极大的权值，不然凑不齐5子，权值为0
        if(((source1>=10&&source1<=13)&&(source2>=10&&source2<=13))||((source1>=110&&source1<=113)&&(source2>=110&&source2<=113)))
        {
            if(Z1+Z2>=2) {Value+=10000; continue;}
            else Value+=0;continue;
        }
        //己活对活，己活对冲，己冲对活，己冲对冲
        if(((source1>=0&&source1<=3)&&((source2>=100&&source2<=103)||(source2>=110&&source2<=113)))
                ||((source1>=10&&source1<=13)&&((source2>=100&&source2<=103)||(source2>=110&&source2<=113))))
        {
            if(Z1==3||Z2==3) { Value+=10000; continue; }
            else { Value+=V[X2][Y2][Z2]+V[X1][Y1][Z1]/4; continue; }
        }
        else Value+=V[X1][Y1][Z1]+V[X2][Y2][Z2];
        continue;
    }
    return Value;
}

int PlayWithComputer::chessType(int rotate, int i, int j)
{
    if(m_blackRadioBtn->isChecked()){
        int t,count=0;
        moveByOne(rotate,&i,&j);
        if((i<0||i>18)||(j<0||j>18))return -2;
        switch (chess[i][j]) {
        case 2:
        {
            while (chess[i][j]==2) {
                ++count;moveByOne(rotate,&i,&j);
                if((i<0||i>18)||(j<0||j>18))
                {
                    t=count+9;
                    return t;
                }
            }
            if(chess[i][j]==0) {t=count-1;}
            else t=count+9;
        }break;
        case 1:
        {
            while(chess[i][j]==1){
                ++count;moveByOne(rotate,&i,&j);
                if((i<0||i>18)||(j<0||j>18))
                {
                    t=count+109;
                    return t;
                }
            }
            if(chess[i][j]==0) {t=count+99;}
            else t=count+109;
        }break;
        case 0:
        {
            moveByOne(rotate,&i,&j);
            if((i<0||i>18)||(j<0||j>18))return -3;
            switch (chess[i][j]) {
            case 2:
            {
                while (chess[i][j]==2) {
                    ++count;moveByOne(rotate,&i,&j);
                    if((i<0||i>18)||(j<0||j>18))
                    {
                        t=count+29;
                        return t;
                    }
                }
                if(chess[i][j]==0) {t=count+19;}
                else t=count+29;
            }break;
            case 1:
            {
                while(chess[i][j]==1){
                    ++count;moveByOne(rotate,&i,&j);
                    if((i<0||i>18)||(j<0||j>18))
                    {
                        t=count+129;
                        return t;
                    }
                }
                if(chess[i][j]==0) {t=count+119;}
                else t=count+129;
            }break;
            case 0:{
                t=-1;
            }break;
            }
        }break;
        }
        return t;
    }
    else if(m_whiteRadioBtn ->isChecked())
    {
        int t,count=0;
        moveByOne(rotate,&i,&j);
        if((i<0||i>18)||(j<0||j>18))return -2;
        switch (chess[i][j]) {
        case 1:
        {
            while (chess[i][j]==1) {
                ++count;moveByOne(rotate,&i,&j);
                if((i<0||i>18)||(j<0||j>18))
                {
                    t=count+9;
                    return t;
                }
            }
            if(chess[i][j]==0) {t=count-1;}
            else t=count+9;
        }break;
        case 2:
        {
            while(chess[i][j]==2){
                ++count;moveByOne(rotate,&i,&j);
                if((i<0||i>18)||(j<0||j>18))
                {
                    t=count+109;
                    return t;
                }
            }
            if(chess[i][j]==0) {t=count+99;}
            else t=count+109;
        }break;
        case 0:
        {
            moveByOne(rotate,&i,&j);
            if((i<0||i>18)||(j<0||j>18))return -3;
            switch (chess[i][j]) {
            case 1:
            {
                while (chess[i][j]==1) {
                    ++count;moveByOne(rotate,&i,&j);
                    if((i<0||i>18)||(j<0||j>18))
                    {
                        t=count+29;
                        return t;
                    }
                }
                if(chess[i][j]==0) {t=count+19;}
                else t=count+29;
            }break;
            case 2:
            {
                while(chess[i][j]==2){
                    ++count;moveByOne(rotate,&i,&j);
                    if((i<0||i>18)||(j<0||j>18))
                    {
                        t=count+129;
                        return t;
                    }
                }
                if(chess[i][j]==0) {t=count+119;}
                else t=count+129;
            }break;
            case 0:{
                t=-1;
            }break;
            }
        }break;
        }
        return t;
    }
}

void PlayWithComputer::moveByOne(int rotate, int *i, int *j)
{
    switch (rotate) {
    case 1:{++*i;}break;
    case 2:{++*i;--*j;}break;
    case 3:{--*j;}break;
    case 4:{--*i;--*j;}break;
    case 5:{--*i;}break;
    case 6:{--*i;++*j;}break;
    case 7:{++*j;}break;
    case 8:{++*i;++*j;}break;
    }
}

void PlayWithComputer::beginBtnClicked()
{
    m_clickOneEffect->play();

    //1代表黑棋，2代表白棋
    if(m_blackRadioBtn->isChecked()) color_flag=1;
    else if(m_whiteRadioBtn->isChecked())color_flag=2;

    memset(chess,0,sizeof(chess));
    if(m_computerRadioBtn->isChecked())
    {
        maxsource_x=maxsource_y=9;
        m_clickOneEffect->play();
        chess[9][9]=color_flag;
        color_flag=3-color_flag;
    }
    update();
    begin_flag=1;
    win_flag=0;
    m_beginBtn->setStyleSheet("QPushButton{border-image: url(:/images/AgainBegin.png);}");
}

void PlayWithComputer::returnBtnClicked()
{
    m_clickOneEffect->play();
    emit closed();
    this->hide();
    memset(chess,0,sizeof(chess));
    m_beginBtn->setStyleSheet("QPushButton{border-image: url(:/images/BeginGame.png);}");
    begin_flag=0;
    update();
}

void PlayWithComputer::regretBtnClicked()
{
    m_clickOneEffect->play();
    if((!computerList.isEmpty())&&(!personList.isEmpty())){
        QPair<int,int> computerTempPair=computerList.last();
        QPair<int,int> personTempPair=personList.last();
        computerList.removeLast();
        personList.removeLast();
        chess[computerTempPair.first][computerTempPair.second]=0;
        chess[personTempPair.first][personTempPair.second]=0;
        maxsource_x=computerList.last().first;maxsource_y=computerList.last().second;
    }else{
        QMessageBox::warning(this,tr("丧心病狂"),tr("没棋子啦！"),QMessageBox::Ok);
    }
    update();
}

void PlayWithComputer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //画背景
    painter.drawPixmap(QRect(0,0,1200,740),QPixmap(":/images/qipan.png"));

    //画棋子
    int redPointflag=0;//用于红点提示
    for(int i=0;i!=19;++i)
        for(int j=0;j!=19;++j)
        {
            if(chess[i][j]==0) ++redPointflag;
            if(chess[i][j]==1)
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/BBlack.png"));
            if(chess[i][j]==2)
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/BWhite.png"));
        }
    if(redPointflag!=19*19){
        painter.setBrush(Qt::red);
        painter.drawEllipse(QRect(maxsource_x*30+212,maxsource_y*30+42,8,8));
    }
}

void PlayWithComputer::mouseReleaseEvent(QMouseEvent *event)
{
    if(begin_flag==0) return;   //游戏未开始，或者轮到人机下棋，此时直接返回

    int x=event->x(),y=event->y();
    if(x<210||x>770||y<40||y>600) return;         //鼠标瞎按越界可以吗？不可以！

    chess_x=(x-216+14)/30;chess_y=(y-46+14)/30; //近似算法，得到二维数组坐标（x坐标加半径除以间距）

    if(chess[chess_x][chess_y]!=0) return;     //至关重要，如果点击地方有棋子，那么直接返回不操作

    //根据颜色给棋盘赋值，随之切换
    chess[chess_x][chess_y]=color_flag;
    color_flag=3-color_flag;

    m_chessDownEffect->play();
    if(rule(chess_x,chess_y)) return;                //进行规则审查，判断是否分出了胜负

    personList.append(qMakePair(chess_x,chess_y));

    if(!renji_flag)
    {
        renji_flag =1;
        this->actionByAi();
    }
    update();
}
