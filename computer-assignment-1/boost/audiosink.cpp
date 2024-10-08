#include "audiosink.h"

AudioSink::AudioSink(QObject *parent): QObject{parent}
{
    m_devices = new QMediaDevices{this};

    m_format.setSampleRate(8000);
    m_format.setChannelCount(1);
    m_format.setSampleFormat(QAudioFormat::Int16);

    m_audioSink = new QAudioSink{m_devices->defaultAudioOutput(),
                                 m_format,nullptr};
    m_audioSink->reset();

    auto io = m_audioSink->start();
    if(!io->open(QIODevice::WriteOnly))
    {
        qDebug() << "AudioSink Device ";
    }
    connect(this,&AudioSink::checkAudioDataReceived,[&,io]()
            {
                audioSinkData(io);
            });

}



AudioSink::~AudioSink()
{
    delete m_audioSink;
    delete m_devices;
}


void AudioSink::audioDataReceived(QByteArray newAudioBuffer, qreal newAudioLevel)
{
    m_buffer = newAudioBuffer;
    m_audioLevel = newAudioLevel;
    qDebug() << m_audioLevel;
    emit checkAudioDataReceived();
}


void AudioSink::audioSinkData(QIODevice *IO)
{
    int len = m_buffer.size();
    if(len)
        IO->write(m_buffer.constData(),len);
}
