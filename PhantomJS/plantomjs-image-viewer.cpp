#include "plantomjs-image-viewer.h"

#include <QImageReader>
#include <QImage>

PlantomJsImageViewer::PlantomJsImageViewer(QWidget *parent) : QScrollArea(parent)
{
    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    setBackgroundRole(QPalette::Dark);
    setWidget(imageLabel);
    setVisible(true);

    scaleFactor = 100;
}

PlantomJsImageViewer::~PlantomJsImageViewer()
{
}

void PlantomJsImageViewer::LoadImage(const QString &fullFileName)
{
    QImageReader reader(fullFileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();

    if (!newImage.isNull()) {
        image = newImage;

        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize((scaleFactor * imageLabel->pixmap()->size())/100);
        //imageLabel->adjustSize();
    }
}

void PlantomJsImageViewer::SetScaleFactor(int percent)
{
    scaleFactor = percent;
    imageLabel->resize((scaleFactor * imageLabel->pixmap()->size())/100);
}