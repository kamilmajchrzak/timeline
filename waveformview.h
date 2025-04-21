#pragma once

#include <QWidget>
#include <QVector>
#include <QPainterPath>
//#include <QAudioBuffer>
#include <QMouseEvent>

class WaveformView : public QWidget {
    Q_OBJECT
public:
    explicit WaveformView(QWidget *parent = nullptr);
    void loadWavFile(const QString &filePath);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<float> samples;
    QVector<int> markers;
    QPainterPath waveformPath;
    void generateWaveform();
};
