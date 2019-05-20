#include "musicthread.h"
#include <QDebug>

MusicThread::MusicThread()
{
    m_deploy = new Deploy();
    backMusic = new QSoundEffect(this);
    connect(m_deploy,SIGNAL(Deploy::valueChanged(int value)),this,SLOT(doVolumeChange(int value)),Qt::BlockingQueuedConnection);
}

MusicThread::~MusicThread()
{
    delete  m_deploy;
}

void MusicThread::run()
{
    backMusic->setSource(QUrl::fromLocalFile(":/sound/background.wav"));
    backMusic->setVolume(m_Volume);
    backMusic->setLoopCount(QSoundEffect::Infinite);
    backMusic->play();
}

void MusicThread::doVolumeChanged(int value)
{
    qDebug()<<"value is: "<<value;
    m_Volume = (double)value/100;
    backMusic->setVolume(m_Volume);
}
