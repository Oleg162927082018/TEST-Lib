#ifndef PLANTOMJSIMAGEVIEWER_H
#define PLANTOMJSIMAGEVIEWER_H

#include <QWidget>
#include <QScrollBar>
#include <QLabel>
#include <QScrollArea>

class PlantomJsImageViewer : public QScrollArea
{
    Q_OBJECT

public:
    explicit PlantomJsImageViewer(QWidget *parent = 0);
    ~PlantomJsImageViewer();

    void LoadImage(const QString &fullFileName);
    void SetScaleFactor(int percent);

private:
    QImage image;
    int scaleFactor;

    QLabel *imageLabel;
};

#endif // PLANTOMJSIMAGEVIEWER_H
