#include "AudioRecorder.h"
#include <QDebug>


AudioSource::AudioSource(QObject *parent): QObject{parent}
{
    m_devices = new QMediaDevices{this};

    m_format.setSampleRate(8000);
    m_format.setChannelCount(1);
    m_format.setSampleFormat(QAudioFormat::Int16);

    m_audioSource = new QAudioSource{m_devices->defaultAudioInput(),
                                     m_format,nullptr};
    m_audioSource->reset();
    auto io = m_audioSource->start();

    if(!io->open(QIODevice::ReadOnly))
        qDebug() << "AudioSource didn't found .";
    else
        connect(io,&QIODevice::readyRead,[&,io]() {audioSourceData(io,m_audioSource);});
}

AudioSource::~AudioSource(){
    delete m_audioSource;
    delete m_devices;
}



void AudioSource::audioSourceData(QIODevice *IO, QAudioSource *audioSource){
    qint64 len = audioSource->bytesAvailable();
    const int BufferSize = 2048;
    // if len > BufferSize it must change the buffer size
    len = BufferSize;

    char buffer[BufferSize];
    qint64 l = IO->read(buffer, len);

    m_buffer = std::string(buffer, l);
    m_audioLevel = audioSourceLevel(buffer, l);
    emit audioDataTransmit(m_buffer, m_audioLevel);
}


qreal AudioSource::audioSourceLevel(const char * data, qint64 length)
{
    const int channelBytes = m_format.bytesPerSample();
    const int sampleBytes = m_format.bytesPerFrame();
    const int numSamples = length / sampleBytes;

    float maxValue = 0;
    const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);

    for (int i = 0; i < numSamples; ++i)
    {
        for (int j = 0; j < m_format.channelCount(); ++j)
        {
            float value = m_format.normalizedSampleValue(ptr);

            maxValue = qMax(value, maxValue);
            ptr += channelBytes;
        }
    }

    return maxValue;
}
