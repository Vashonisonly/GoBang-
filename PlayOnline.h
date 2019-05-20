#ifndef PLAYONLINE_H
#define PLAYONLINE_H

#include "myClientServer.h"
#include <QWidget>
#include <QTableWidget>

namespace Ui {
class Online;
}
class  QSoundEffect;
class PlayOnline : public QWidget
{
    Q_OBJECT
public:
    explicit PlayOnline(QWidget *parent = nullptr);
    ~PlayOnline();
    bool startServer();

protected:
    void paintEvent(QPaintEvent *event);          //绘制界面
    void mouseReleaseEvent(QMouseEvent *event);   //鼠标按下事件

signals:
    void closed();
    void chessDownEvent(int chess_x, int chess_y);

public slots:
    void returnBtnClicked();
    void regretBtnClicked();
    void giveUpBtnClicked();
private:
    void setBackground();
    //游戏规则设计
    int rule(int chess_x,int chess_y);
    void judge();

    //处理指令
    //cmd代表指令，args代表参数
    void processCommand(QByteArray &cmd, QByteArray &args);
private:
    Ui::Online* ui;

    QTableWidget* clientTable;
    MyClientServer* m_clientServer;
    //音效
    QSoundEffect* m_chessDownEffect, * m_clickOneEffect,* m_winEffect,* m_loseEffect;
    //链表，用于悔棋
    QList<QPair<int,int>> opponentList;
    QList<QPair<int,int>> myList;

    int chess[19][19]={};
    int chess_x=0, chess_y=0;
    int m_color;
    bool begin_flag=false,win_flag=false;
};

#endif // PLAYONLINE_H
