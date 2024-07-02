#include "collector.h"

collector::collector(QString _ffmpegPath) : m_ffmpegPath(_ffmpegPath) { m_arguments << "-i"; }

collector::~collector() {}

void collector::setInputFile(QString _inputFileName)
{
    m_inputFileName = _inputFileName;
    m_arguments << m_inputFileName;
}

void collector::setOutputFile(QString _outputFileName)
{
    m_outputFileName = _outputFileName;
}

void collector::setArguments(QStringList _arguments)
{
    m_arguments << _arguments;
}

void collector::setQuality(int _videoBitrate, int _audioBitrate)
{
    QString videoBitrateOption = QString::number(_videoBitrate) + "k";
    QString audioBitrateOption = QString::number(_audioBitrate) + "k";

    m_arguments << "-b:v" << videoBitrateOption << "-b:a" << audioBitrateOption;
}

void collector::startConversion()
{
    m_arguments << m_outputFileName;

    ffmpegProcess = new QProcess();
    ffmpegProcess->setProgram(m_ffmpegPath);
    ffmpegProcess->setArguments(m_arguments);

    qDebug() << "Starting conversion...";
    ffmpegProcess->start();
    ffmpegProcess->waitForFinished();

    if (!ffmpegProcess->waitForStarted()) {
        qDebug() << "Failed to start conversion process.";
        return;
    }

     if (ffmpegProcess->exitCode() == 0) {
        qDebug() << "Conversion successful!";
     } else {
        qDebug() << "Conversion failed. Error:" << ffmpegProcess->errorString();
     }

     delete ffmpegProcess;
}

void collector::stopConversion()
{
    if (ffmpegProcess) {
        ffmpegProcess->kill();
        qDebug() << "Conversion stopped.";
    }
}
