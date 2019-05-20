#ifndef MUSICTHREAD_H
#define MUSICTHREAD_H
#include <QThread>
#include <QSoundEffect>
#include <QApplication>
#include "deploy.h"

class MusicThread:public QThread
{
    Q_OBJECT
public:
    MusicThread();
    ~MusicThread();
    void doVolumeChanged(int value);
protected:
    void run();
private:
    QSoundEffect* backMusic;
    Deploy* m_deploy;
    double m_Volume=0.5;
};

#endif // MUSICTHREAD_H
