#ifndef AUDIOSINK_H
#define AUDIOSINK_H

#include <QObject>
#include <QDebug>
#include <QIODevice>
#include <QAudioFormat>
#include <QMediaDevices>
#include <QAudioSink>

class AudioSink : public QObject
{
    Q_OBJECT

public:
    explicit AudioSink(QObject *parent = nullptr);
    ~AudioSink();

signals:
    void checkAudioDataReceived();

public slots:
    void audioDataReceived(QByteArray newAudioBuffer, qreal newAudioLevel);


private:
    void audioSinkData(QIODevice *IO);

    QMediaDevices *m_devices;
    QAudioFormat m_format;
    QAudioSink *m_audioSink;
    QByteArray m_buffer;
    qreal m_audioLevel;
};

#endif // AUDIOSINK_H
