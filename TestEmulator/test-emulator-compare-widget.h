#ifndef TESTEMULATOR_COMPAREWIDGET_H
#define TESTEMULATOR_COMPAREWIDGET_H

#include "../../TTI/Common/itestcasetemplate.h"

#include "test-emulator-image-viewer.h"

namespace Ui {
class TestEmulatorCompareWidget;
}

class TestEmulatorCompareWidget : public IResultCompareWidget
{
    Q_OBJECT

public:
    explicit TestEmulatorCompareWidget(QWidget *parent = 0);
    ~TestEmulatorCompareWidget();

private:
    Ui::TestEmulatorCompareWidget *ui;

    TestEmulatorImageViewer *leftImageViewer;
    TestEmulatorImageViewer *rightImageViewer;

    // IResultCompareWidget interface
public:
    virtual void SetLeftValue(QString leftValueFullFolderPath);
    virtual void SetRightValue(QString rightValueFullFolderPath);
private slots:
    void on_scaleSlider_valueChanged(int value);
    void on_scalePlusBtn_clicked();
    void on_scaleMinusBtn_clicked();
};

#endif // TESTEMULATOR_COMPAREWIDGET_H
