#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QPushButton>
#include <QSoundEffect>
#include <QDesktopWidget>
#include <QParallelAnimationGroup>
#include "musicthread.h"
#include "deploy.h"
#include "PlayOnline.h"
#include "playtogether.h"
#include "playwithcomputer.h"

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

protected:
    void paintEvent(QPaintEvent* event);

private:
    void setBackground();
    void showAnimation();
    void openOrCloseFunction();

private:
    //音效
    QSoundEffect *effect;
    //线程中播放背景音乐
    MusicThread* m_music;

    //动画功能
    QPushButton *btnPeopleTogether;
    QPushButton *btnPeopleAndComputer;
    QPushButton *btnOnline;
    QPushButton *btnDeploy;
    QParallelAnimationGroup *group;

    //功能模块
    PlayTogether* m_playTogether ;
    PlayWithComputer* m_playWithComputer ;
    PlayOnline* m_playOnline ;
    Deploy* m_deploy ;
};

#endif // CLIENT_H
