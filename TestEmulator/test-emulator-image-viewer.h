#ifndef TESTEMULATORIMAGEVIEWER_H
#define TESTEMULATORIMAGEVIEWER_H

#include <QWidget>
#include <QScrollBar>
#include <QLabel>
#include <QScrollArea>

class TestEmulatorImageViewer : public QScrollArea
{
    Q_OBJECT

public:
    explicit TestEmulatorImageViewer(QWidget *parent = 0);
    ~TestEmulatorImageViewer();

    void LoadImage(const QString &fullFileName);
    void SetScaleFactor(int percent);

private:
    QImage image;
    int scaleFactor;

    QLabel *imageLabel;
};

#endif // TESTEMULATORIMAGEVIEWER_H
