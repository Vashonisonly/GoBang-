#ifndef PEOPLETOGETHER_H
#define PEOPLETOGETHER_H

#include <QWidget>


class QGroupBox;
class QRadioButton;
class QPushButton;
class QSoundEffect;

class PlayTogether : public QWidget
{
    Q_OBJECT
public:
    explicit PlayTogether(QWidget *parent = nullptr);

protected:
    //绘制和按下操作
    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

signals:
void closed();

public slots:
void beginBtnClicked();
void returnBtnClicked();

private:
    void setBackground();
    bool rule(int chess_x, int chess_y);
    void judge();

private:
    //按钮
    QGroupBox*  m_groupBox;
    QRadioButton* m_blackRadioBtn,* m_whiteRadioBtn;
    QPushButton* m_returnBtn,* m_beginBtn;
    //音效
    QSoundEffect* m_chessDownEffect, * m_clickOneEffect;

    //棋盘上每个点的值，0无子，1黑子，2白子
    int chess[19][19]={};
    //棋盘坐标
    int chess_x=0,chess_y=0;
    //当前颜色标志,输赢状态标志,是否开始标志，
    int color_flag=0;
    bool win_flag=0, begin_flag=0;
};

#endif // PEOPLETOGETHER_H
