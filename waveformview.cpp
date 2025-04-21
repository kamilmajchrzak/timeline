#include "waveformview.h"
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <cmath>
#include <sndfile.hh> // libsndfile

WaveformView::WaveformView(QWidget *parent) : QWidget(parent) {
    setMinimumHeight(100);
}

void WaveformView::loadWavFile(const QString &filePath) {
    SndfileHandle file(filePath.toStdString());
    if (file.error() || file.channels() > 2) {
        qWarning() << "Błąd otwarcia pliku WAV";
        return;
    }

    QVector<float> temp(file.frames());
    file.readf(temp.data(), file.frames());

    samples = temp;
    generateWaveform();
    update();
}

void WaveformView::generateWaveform() {
    waveformPath = QPainterPath();
    if (samples.isEmpty()) return;

    int w = width();
    int h = height();
    int step = samples.size() / w;
    waveformPath.moveTo(0, h/2);

    for (int i = 0; i < w; ++i) {
        float value = samples[i * step];
        float y = h/2 - value * (h / 2);
        waveformPath.lineTo(i, y);
    }
}

void WaveformView::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::cyan);
    painter.drawPath(waveformPath);

    painter.setPen(Qt::red);
    for (int x : markers)
        painter.drawLine(x, 0, x, height());
}

void WaveformView::mousePressEvent(QMouseEvent *event) {
    markers.append(event->pos().x());
    update();
}
