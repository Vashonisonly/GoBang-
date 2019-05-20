#ifndef PLAYWITHCOMPUTER_H
#define PLAYWITHCOMPUTER_H

#include <QWidget>

class QGroupBox;
class QRadioButton;
class QPushButton;
class QSoundEffect;

class PlayWithComputer : public QWidget
{
    Q_OBJECT
public:
    explicit PlayWithComputer(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);          //绘制坐标界面
    void mouseReleaseEvent(QMouseEvent *event);   //鼠标按下事件

private:
    void setBackground();
    //游戏规则设计
    int rule(int chess_x,int chess_y);
    void judge();
    //AI动作
    void actionByAi();
    //判断某一点的权值
    int value(int i,int j);
    int chessType(int rotate,int i,int j);
    void moveByOne(int rotate,int *i,int *j);     //改为引用传递？

signals:
    void closed();

public slots:
    void beginBtnClicked();
    void returnBtnClicked();
    void regretBtnClicked();

private:
    //先手者按钮组，先手颜色按钮组
    QGroupBox*  m_groupBox_PlayerFirst,*  m_groupBox_ColorFirst;
    //按钮组成员
    QRadioButton* m_computerRadioBtn,* m_playerRadioBtn, * m_blackRadioBtn,* m_whiteRadioBtn;
    //按钮
    QPushButton* m_returnBtn,* m_beginBtn,* m_regretBtn;
    //音效
    QSoundEffect* m_chessDownEffect, * m_clickOneEffect,* m_winEffect,* m_loseEffect;

    //链表，用于悔棋
    QList<QPair<int,int>> computerList;
    QList<QPair<int,int>> personList;

    //棋盘上每个点的值，0无子，1黑子，2白子
    int chess[19][19]={};
    //棋盘坐标
    int chess_x=0,chess_y=0,maxsource_x=0,maxsource_y=0;
    //当前颜色标志,输赢状态标志,是否开始标志
    int color_flag=0;
    bool win_flag=0, begin_flag=0, renji_flag = 0;
};

#endif // PLAYWITHCOMPUTER_H
