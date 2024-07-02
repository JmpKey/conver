#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <QProcess>
#include <QString>
#include <QStringList>
#include <QDebug>

class collector
{
public:
    collector(QString _ffmpegPath);
    ~collector();

    void setInputFile(QString _inputFileName);
    void setOutputFile(QString _outputFileName);
    void setArguments(QStringList _arguments);
    void setQuality(int _videoBitrate, int _audioBitrate);
    void startConversion();
    void stopConversion();

private:
    QString m_ffmpegPath;
    QString m_inputFileName;
    QString m_outputFileName;
    QStringList m_arguments;
    QProcess* ffmpegProcess;
};

#endif // COLLECTOR_H
