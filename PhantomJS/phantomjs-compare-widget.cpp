#include "phantomjs-compare-widget.h"
#include "ui_phantomjs-compare-widget.h"

PhantomJsCompareWidget::PhantomJsCompareWidget(QWidget *parent) :
    IResultCompareWidget(parent),
    ui(new Ui::PhantomJsCompareWidget)
{
    ui->setupUi(this);

    leftImageViewer = new PlantomJsImageViewer(this);
    ui->horizontalLayout->addWidget(leftImageViewer);

    rightImageViewer = new PlantomJsImageViewer(this);
    ui->horizontalLayout->addWidget(rightImageViewer);

    connect(leftImageViewer->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            rightImageViewer->horizontalScrollBar(), SLOT(setValue(int)));

    connect(leftImageViewer->verticalScrollBar(), SIGNAL(valueChanged(int)),
            rightImageViewer->verticalScrollBar(), SLOT(setValue(int)));

    connect(rightImageViewer->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            leftImageViewer->horizontalScrollBar(), SLOT(setValue(int)));

    connect(rightImageViewer->verticalScrollBar(), SIGNAL(valueChanged(int)),
            leftImageViewer->verticalScrollBar(), SLOT(setValue(int)));
}

PhantomJsCompareWidget::~PhantomJsCompareWidget()
{
    delete ui;
}

void PhantomJsCompareWidget::SetLeftValue(QString leftValueFullFolderPath)
{
    leftImageViewer->LoadImage(leftValueFullFolderPath + "/1.png");
}

void PhantomJsCompareWidget::SetRightValue(QString rightValueFullFolderPath)
{
    rightImageViewer->LoadImage(rightValueFullFolderPath + "/1.png");
}

void PhantomJsCompareWidget::on_scaleSlider_valueChanged(int value)
{
    leftImageViewer->SetScaleFactor(value);
    rightImageViewer->SetScaleFactor(value);
}

void PhantomJsCompareWidget::on_scalePlusBtn_clicked()
{
    int v = ui->scaleSlider->value() + ui->scaleSlider->pageStep();
    ui->scaleSlider->setValue(v);
}

void PhantomJsCompareWidget::on_scaleMinusBtn_clicked()
{
    int v = ui->scaleSlider->value() - ui->scaleSlider->pageStep();
    ui->scaleSlider->setValue(v);
}
