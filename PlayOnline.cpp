#include "playonline.h"
#include "ui_online.h"
#include <QList>
#include <QInputDialog>
#include <QDir>
#include <QDebug>
#include <QPainter>
#include <QSoundEffect>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDesktopWidget>

PlayOnline::PlayOnline(QWidget *parent) : QWidget(parent),ui(new Ui::Online)
{ 
    setBackground();
    connect(ui->returnBtn,&QPushButton::clicked,this,&PlayOnline::returnBtnClicked);
    connect(ui->regretBtn,&QPushButton::clicked,this,&PlayOnline::regretBtnClicked);
    connect(ui->giveUpBtn,&QPushButton::clicked,this,&PlayOnline::giveUpBtnClicked);
}

PlayOnline::~PlayOnline()
{
    delete ui;
}

bool PlayOnline::startServer()
{
    if(!m_clientServer){
        m_clientServer = new MyClientServer(this);
        if(m_clientServer->m_name==""){
            bool ok;
            QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("User name:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty()){
                m_clientServer->m_name = text.toLocal8Bit();
            }
        }
        connect(m_clientServer,&MyClientServer::newData,this,
                [this](QByteArray cmd,QByteArray args){
            processCommand(cmd,args);
        });
        connect(ui->creatRoom,&QPushButton::clicked,m_clientServer,&MyClientServer::creatGame);
        connect(ui->joinRoom,&QPushButton::clicked,m_clientServer,&MyClientServer::jionGame);
        connect(ui->regretBtn,&QPushButton::clicked,m_clientServer,&MyClientServer::sendRegretCmd);
        connect(ui->forPeaceBtn, &QPushButton::clicked,m_clientServer,&MyClientServer::sendPeaceCmd);
        connect(ui->giveUpBtn,&QPushButton::clicked,m_clientServer,&MyClientServer::sendGiveUpCmd);
        connect(this,&PlayOnline::chessDownEvent,this,[this](int chess_x,int chess_y){
            m_clientServer->sendPosition(chess_x,chess_y);
        });
        connect(ui->sendBtn,&QPushButton::clicked,this,[this](){
            QByteArray msg = ui->lineEdit->text().toLocal8Bit();
            m_clientServer->sendMessage(&msg);
        });
    }
    else  return true;
}

void PlayOnline::paintEvent(QPaintEvent *event)
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
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/黑棋.png"));
            if(chess[i][j]==2)
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/白棋.png"));
        }
}

void PlayOnline::mouseReleaseEvent(QMouseEvent *event)
{
    if(begin_flag==0) return;   //游戏未开始，此时直接返回

    int x=event->x(),y=event->y();
    if(x<210||x>770||y<40||y>600) return;         //鼠标瞎按越界可以吗？不可以！

    chess_x=(x-216+14)/30;chess_y=(y-46+14)/30; //近似算法，得到二维数组坐标（x坐标加半径除以间距）

    if(chess[chess_x][chess_y]!=0) return;     //至关重要，如果点击地方有棋子，那么直接返回不操作

    //根据颜色给棋盘赋值，随之切换
    chess[chess_x][chess_y]=m_color;

    m_chessDownEffect->play();
    this->rule(chess_x,chess_y);                //进行规则审查，判断是否分出了胜负
    update();
}

void PlayOnline::returnBtnClicked()
{
    m_clickOneEffect->play();
    emit closed();
    this->hide();
    memset(chess,0,sizeof(chess));
   // m_beginBtn->setStyleSheet("QPushButton{border-image: url(:/images/BeginGame.png);}");
    begin_flag=0;
    update();
}

void PlayOnline::regretBtnClicked()
{
    m_clientServer->sendRegretCmd();
}

void PlayOnline::giveUpBtnClicked()
{
    m_clientServer->sendGiveUpCmd();
}

void PlayOnline::setBackground()
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

    qDebug()<<"set bacckground";
    //客户菜单
    clientTable=new QTableWidget(this);
    clientTable->setGeometry(800,190,246,192);
    clientTable->setColumnCount(3);
    clientTable->setHorizontalHeaderItem(0,new QTableWidgetItem("房主"));
    clientTable->setColumnWidth(0,65);
    clientTable->setHorizontalHeaderItem(1,new QTableWidgetItem(tr("客人")));
    clientTable->setColumnWidth(1,64);
    clientTable->setHorizontalHeaderItem(2,new QTableWidgetItem("状态"));
    clientTable->setColumnWidth(2,115);
    clientTable->setStyleSheet(QString::fromUtf8("border-image: url(:/images/gameInfo.jpg);"));

    //设置选中格式为每次一整行
    clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置每次只能选出一个对象
    clientTable->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置不能修改
    clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

int PlayOnline::rule(int chess_x, int chess_y)
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
    emit chessDownEvent(chess_x,chess_y);
    return false;
}

void PlayOnline::judge()
{
    
}

void PlayOnline::processCommand(QByteArray &cmd, QByteArray &args)
{
    //确保字符串为大写并且两端为空
    cmd=cmd.toUpper().trimmed();
    QList<QByteArray> m_args = args.split(m_clientServer->CmdSplit[0]);
    //QHash<QByteArray, QByteArray> hashArgs=parseArgs(args)

    //接收到对方落子指令
    if(cmd == m_clientServer->CmdPosDown){
        chess[m_args[0].toInt()][m_args[1].toInt()] = 3-m_color;
    }

    //接收到游戏开始信息
    else  if(cmd == m_clientServer->CmdGameBegin){
        if(m_args[1] == "CHESSDOWN_TIME"){
            m_color = 1;
            begin_flag =1;
        }
        else if(m_args[1] == "WAIT_TIME"){
            m_color =2;
            begin_flag =1;
        }
        else  {
            qDebug()<< " begin error";
        }
    }

    //接收到大厅玩家增加指令
    else if(cmd == m_clientServer->CmdGameInfoAdd){
        int rowCount = clientTable->rowCount();
        clientTable->setRowCount(rowCount+1);
        //        ui->tableWidget->item(rowCount,0)->text() = m_args[0];
        //        ui->tableWidget->item(rowCount,1)->text() = m_args[1];
        //        ui->tableWidget->item(rowCount,2)->text() = m_args[2];
        QTableWidgetItem *itemId=new QTableWidgetItem(m_args[0].data());
        clientTable->setItem(rowCount,0,itemId);

        QTableWidgetItem *itemName=new QTableWidgetItem(m_args[1].data());
        clientTable->setItem(rowCount,1,itemName);

        QTableWidgetItem *itemIp=new QTableWidgetItem(m_args[2].data());
        clientTable->setItem(rowCount,2,itemIp);
    }

    //接收到大厅玩家退出指令
    else if(cmd == m_clientServer->CmdGameInfoRemove){
        int rowCount=clientTable->rowCount();
        for(int i=0;i!=rowCount;++i)
        {
            if(clientTable->item(i,0)->text()==m_args[0]){
                //删除
                clientTable->removeRow(i);
                break;
            }
            else if(clientTable->item(i,2)->text() == m_args[0]){
                //更改
            }
        }
    }

    //接收到大厅当前玩家信息指令
    else if(cmd == m_clientServer->CmdGameInfo){
        int rowCount = (m_args.size())/2;
        qDebug()<<"GameInfo:"<<args<<"rowCount: "<<rowCount;

        for(int i=0;i!=rowCount;++i){
            clientTable->setRowCount(i+1);

            QTableWidgetItem *itemHost=new QTableWidgetItem(m_args[2*i].data());
            itemHost->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            clientTable->setItem(i,0,itemHost);

            QTableWidgetItem *itemGuest=new QTableWidgetItem(m_args[2*i+1].data());
            itemGuest->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            clientTable->setItem(i,1,itemGuest);

            if(m_args[2*i+1].data() != QByteArray("-") ){
                QTableWidgetItem *itemState=new QTableWidgetItem(QString(tr("战斗中")));
                itemState->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                clientTable->setItem(i,2,itemState);
            }
            else{
                QTableWidgetItem *itemState=new QTableWidgetItem(QString(tr("等待玩家")));
                itemState->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                clientTable->setItem(i,2,itemState);
            }
//            ui->tableWidget->item(2*i,0)->text() = m_args[2*i];
//            ui->tableWidget->item(2*i,1)->text() = m_args[2*i+1];
//            update();
            //ui->tableWidget->item(3*i,2)->text() = m_args[3*i+2];
        }
        qDebug()<<"rowCount over";
        update();
    }

    //接收到对方发来消息指令
    else if(cmd == m_clientServer->CmdSendMsg){
        for(int i=0;i!=m_args.size();++i){
            ui->textBrowser->append(m_args[i]);
        }

    }

    //接收到对方认输指令
    else if(cmd == m_clientServer->CmdGiveUp){
        int ret = QMessageBox::information(this,"Win!","对方投降！你赢啦!\n再来一把？");
        //
    }

    //接收到对方求和指令
    else  if(cmd == m_clientServer->CmdForPeace){
        int ret = QMessageBox::information(this,"和棋","对方请求与你和棋\n是否同意？");
        if(ret==QMessageBox::Yes){
            m_clientServer->sendPeaceReturnCmd(1);
        }
        else  {
            m_clientServer->sendPeaceReturnCmd(0);
        }
    }

    //接收到对方请求悔棋指令
    else if(cmd == m_clientServer->CmdForRegret){
        int ret = QMessageBox::information(this,"悔棋","对方请求你悔棋\n是否同意？");
        if(ret==QMessageBox::Yes){
            m_clientServer->sendRegretreturnCmd(QByteArray("1"));
        }
    }

    //接收到对方回应自己求和请求指令
    else if(cmd == m_clientServer->CmdForPeaceReturn){
        if(m_args[0].toInt()==1){
            //
        }
        else if(m_args[0].toInt() ==0){
            //
        }
        else {
            qDebug()<<"for peace error:";
        }
    }

    //接收到对方回应自己悔棋请求指令
    else if(cmd == m_clientServer->CmdForRegretReturn){
        if(m_args[0]=="1"){
            //
        }
        else if(m_args[0].toInt() ==0){
            //
        }
        else {
            qDebug()<<"regret error:";
        }
    }

    //接收到对方超时指令
    else if(cmd == m_clientServer->CmdTimeOut){

    }

    //服务器停止服务指令
    else if(cmd == m_clientServer->CmdServerClose){

    }
    update();
}
