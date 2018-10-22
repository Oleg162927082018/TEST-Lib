#include "test-emulator-compare-widget.h"
#include "ui_test-emulator-compare-widget.h"

TestEmulatorCompareWidget::TestEmulatorCompareWidget(QWidget *parent) :
    IResultCompareWidget(parent),
    ui(new Ui::TestEmulatorCompareWidget)
{
    ui->setupUi(this);

    leftImageViewer = new TestEmulatorImageViewer(this);
    ui->horizontalLayout->addWidget(leftImageViewer);

    rightImageViewer = new TestEmulatorImageViewer(this);
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

TestEmulatorCompareWidget::~TestEmulatorCompareWidget()
{
    delete ui;
}

void TestEmulatorCompareWidget::SetLeftValue(QString leftValueFullFolderPath)
{
    leftImageViewer->LoadImage(leftValueFullFolderPath + "/img.png");
}

void TestEmulatorCompareWidget::SetRightValue(QString rightValueFullFolderPath)
{
    rightImageViewer->LoadImage(rightValueFullFolderPath + "/img.png");
}

void TestEmulatorCompareWidget::on_scaleSlider_valueChanged(int value)
{
    leftImageViewer->SetScaleFactor(value);
    rightImageViewer->SetScaleFactor(value);
}

void TestEmulatorCompareWidget::on_scalePlusBtn_clicked()
{
    int v = ui->scaleSlider->value() + ui->scaleSlider->pageStep();
    ui->scaleSlider->setValue(v);
}

void TestEmulatorCompareWidget::on_scaleMinusBtn_clicked()
{
    int v = ui->scaleSlider->value() - ui->scaleSlider->pageStep();
    ui->scaleSlider->setValue(v);
}
