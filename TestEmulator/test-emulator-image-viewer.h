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
    explicit TestEmulatorImageViewer(QWidget *parent = nullptr);
    ~TestEmulatorImageViewer();

    void LoadImage(const QString &fullFileName);
    void SetScaleFactor(int percent);
    void Clear();

private:
    QString imageFullFileName;
    QImage image;
    int scaleFactor;

    QLabel *imageLabel;
};

#endif // TESTEMULATORIMAGEVIEWER_H
