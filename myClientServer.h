#ifndef STATICFUNCTION_H
#define STATICFUNCTION_H

#include <QApplication>
class  QTcpSocket;

class MyClientServer:public QObject
{
    Q_OBJECT
public:
    MyClientServer(QObject* parent = 0);
    ~MyClientServer();
    //昵称r
    QByteArray m_name="";

public:
    //服务端向客户端发送的指令集合
    //游戏内容
    const QByteArray CmdGameBegin = "GAME_BEGIN";  //请求建立房间
    const QByteArray CmdGameJion = "GAME_JION";  //请求加入游戏
    const QByteArray CmdGameCreat = "GAME_CREAT";  //请求建立房间
    const QByteArray CmdPosDown = "POSITION";  //发送对方落子位置信息
    const QByteArray CmdForPeace = "FORPEACE"; //对方求和指令
    const QByteArray CmdForPeaceReturn = "FORPEACE_RETURN"; //对方求和指令,是
    const QByteArray CmdForRegret = "FORREGRET";  //对方请求悔棋指令
    const QByteArray CmdForRegretReturn = "FORREGRET_RETURN"; //对方反馈的请求悔棋，是
    const QByteArray CmdGiveUp = "GIVE_UP";  //发送认输指令
    const QByteArray CmdSendMsg = "SEND_MESSAGE";  //发送对话消息
    const QByteArray CmdGameOver = "GAMEOVER";  //游戏结束指令
    const QByteArray CmdTimeOut = "TIMEOUT";  //落子超时指令
    const QByteArray CmdGameQuit = "GAME_QUIT";  //游戏退出指令
    const QByteArray CmdLogin = "LOGIN";  //登入指令

    //控制内容
     const QByteArray CmdGameInfo= "GAME_INFO";  //服务端下发游戏大厅指令
    const QByteArray CmdGameInfoAdd = "GAME_INFO_ADD";  //服务端下发游戏大厅指令,添加客户
    const QByteArray CmdGameInfoRemove = "GAME_INFO_REMOVE";  //服务端下发游戏大厅指令，移除客户
    const QByteArray CmdServerClose = "SERVER_CLOSE";  //服务端停止服务指令

    //特殊指令
    const QByteArray CmdEnd = "\r\n";  //结束符
    const QByteArray CmdSplit = ";";  //间隔符

signals:
    void newData(QByteArray cmd,QByteArray args);

public slots:
    int readData();

    bool initAndConnect();
    bool disConnect();

    bool creatGame(); //创建房间
    bool jionGame();  //加入房间
    bool sendPosition(const int chess_x, const int chess_y);
    //求和指令
    bool sendPeaceCmd();
    bool sendPeaceReturnCmd(bool);
    //悔棋指令
    bool sendRegretCmd();
    bool sendRegretreturnCmd(QByteArray flag);
    //认输指令
    bool sendGiveUpCmd();
    //发送消息
    bool sendMessage(QByteArray* m_msg);
    //发送决出胜负指令
    bool sendGameOverCmd();
private:
    QTcpSocket* m_tcpSocket;
    //地址
    QString m_addr;
};

#endif // STATICFUNCTION_H
