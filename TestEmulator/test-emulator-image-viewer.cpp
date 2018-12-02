#include "test-emulator-image-viewer.h"

#include <QImageReader>
#include <QImage>

TestEmulatorImageViewer::TestEmulatorImageViewer(QWidget *parent) : QScrollArea(parent)
{
    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->resize(0,0);

    setBackgroundRole(QPalette::Dark);
    setWidget(imageLabel);
    setVisible(true);

    scaleFactor = 100;
}

TestEmulatorImageViewer::~TestEmulatorImageViewer()
{
}

void TestEmulatorImageViewer::LoadImage(const QString &fullFileName)
{
    if(imageFullFileName.compare(fullFileName) != 0) {

        imageFullFileName = fullFileName;
        QImageReader reader(imageFullFileName);
        reader.setAutoTransform(true);
        const QImage newImage = reader.read();

        if (!newImage.isNull()) {
            image = newImage;

            imageLabel->setPixmap(QPixmap::fromImage(image));
            imageLabel->resize((scaleFactor * imageLabel->pixmap()->size())/100);

            //imageLabel->adjustSize();
        } else { Clear(); }
    }
}

void TestEmulatorImageViewer::SetScaleFactor(int percent)
{
    scaleFactor = percent;
    if(imageLabel->pixmap() != nullptr)
    {
        imageLabel->resize((scaleFactor * imageLabel->pixmap()->size())/100);
    }
}

void TestEmulatorImageViewer::Clear()
{
    imageFullFileName.clear();
    imageLabel->clear();
    imageLabel->resize(0,0);
}
