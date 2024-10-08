#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QIODevice>
#include <QAudioFormat>
#include <QAudioSource>
#include <QMediaDevices>
#include <string>

class AudioSource : public QObject
{
    Q_OBJECT

public:
    explicit AudioSource(QObject *parent = nullptr);
    ~AudioSource();
    std::string m_buffer;

signals:
    void audioDataTransmit(const std::string &buffer, qreal audioLevel);

private slots:
    void audioSourceData(QIODevice *IO, QAudioSource *audioSource);

private:
    QMediaDevices *m_devices;
    QAudioFormat m_format;
    QAudioSource *m_audioSource;

    qreal m_audioLevel;

    qreal audioSourceLevel(const char *data, qint64 length);
};

#endif // AUDIORECORDER_H
