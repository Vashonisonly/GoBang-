#include "myClientServer.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QTextCodec>
#include <QMessageBox>

MyClientServer::MyClientServer(QObject *parent):QObject (parent)
{

    initAndConnect();
}

MyClientServer::~MyClientServer()
{

}

int MyClientServer::readData()
{
    //读取出数据包
    QByteArray buffer=m_tcpSocket->readAll();
    QTextCodec *tc = QTextCodec::codecForName("UTF-8");
    QString tmpQStr = tc->toUnicode(buffer);
    qDebug()<<"recive new Data: "<<tmpQStr;

    int endIndex;
    while((endIndex = buffer.indexOf(CmdEnd))>-1){
        //提取一行指令
        QByteArray data = buffer.mid(0,endIndex);
        buffer.remove(0,endIndex+CmdEnd.length());
        //提取指令和参数
        QByteArray cmd,args;
        int argIndex = data.indexOf(CmdSplit);
        if(argIndex==-1){
            cmd = data;
        }else{
            cmd = data.mid(0,argIndex);
            args = data.mid(argIndex+CmdSplit.length(),data.length());
        }
        emit newData(cmd,args);
    }
}

bool MyClientServer::initAndConnect()
{
    qDebug()<<"2222!!!!!!!!!!!!!!!!";
    m_tcpSocket = new QTcpSocket;
    m_tcpSocket->connectToHost(QString("47.101.200.189"),6666);

    //连接成功
    connect(m_tcpSocket,&QTcpSocket::connected,this,[this](){
        if(m_tcpSocket){
            qDebug()<<"scusess connect!";
            m_addr = m_tcpSocket->peerAddress().toString();
//            QByteArray data;
//            data.append(CmdLogin+CmdSplit+m_name+CmdEnd);
//            qint64 ret = m_tcpSocket->write(data.data(),data.length());
//            qDebug()<<"ret: "<<ret<<" "<<data;
            //新数据到来就进行读取
            connect(m_tcpSocket,&QTcpSocket::readyRead,this,[this](){readData();});
        }
    });

    //    connect(m_tcpSocket,&QTcpSocket::error,this,[this](){
    //        QMessageBox::warning(NULL,"提示：",QString("error: %1").arg(errno));
    //    });
}

bool MyClientServer::disConnect()
{

}

bool MyClientServer::creatGame()
{
    if(!m_tcpSocket){
        qDebug()<<"未成功连接";
        return -1;
    }
    QByteArray data;
    data.append(CmdGameCreat+CmdSplit);
            data.append(m_name+CmdSplit);
    data.append(m_addr.toLocal8Bit()+CmdEnd);
    m_tcpSocket->write(data.data(),data.length());
    qDebug()<<data;
}

bool MyClientServer::jionGame()
{

}

bool MyClientServer::sendPosition(const int chess_x, const int chess_y)
{
    m_tcpSocket->write(CmdPosDown+CmdSplit+QByteArray::number(chess_x)+CmdSplit+QByteArray::number(chess_y)+CmdEnd);
}

bool MyClientServer::sendPeaceCmd()
{
    m_tcpSocket->write(CmdForPeace+CmdSplit+CmdEnd);
}

bool MyClientServer::sendPeaceReturnCmd(bool yesOrNo)
{

    if( yesOrNo == 1){
        m_tcpSocket->write(CmdForPeaceReturn+CmdSplit+"1"+CmdEnd);
    }
    else  {
        m_tcpSocket->write(CmdForPeaceReturn+CmdSplit+"0"+CmdEnd);
    }
}

bool MyClientServer::sendRegretCmd()
{
    m_tcpSocket->write(CmdForRegret+CmdEnd);
}

bool MyClientServer::sendRegretreturnCmd(QByteArray flag)
{
    m_tcpSocket->write(CmdForRegretReturn+CmdSplit+flag+CmdEnd);
}

bool MyClientServer::sendGiveUpCmd()
{
    m_tcpSocket->write(CmdGiveUp+CmdSplit+CmdEnd);
}

bool MyClientServer::sendMessage(QByteArray *m_msg)
{
    QByteArray data;
    data.append(CmdSendMsg+CmdSplit+*m_msg+CmdEnd);
    qint64 ret = m_tcpSocket->write(data.data(),data.length());
    qDebug()<<QString("send Msg size: %1").arg(ret);
}

bool MyClientServer::sendGameOverCmd()
{

}
