#ifndef PHANTOMJS_COMPAREWIDGET_H
#define PHANTOMJS_COMPAREWIDGET_H

#include "../../TTI/Common/itestcasetemplate.h"

#include "plantomjs-image-viewer.h"

namespace Ui {
class PhantomJsCompareWidget;
}

class PhantomJsCompareWidget : public IResultCompareWidget
{
    Q_OBJECT

public:
    explicit PhantomJsCompareWidget(QWidget *parent = 0);
    ~PhantomJsCompareWidget();

private:
    Ui::PhantomJsCompareWidget *ui;

    PlantomJsImageViewer *leftImageViewer;
    PlantomJsImageViewer *rightImageViewer;

    // IResultCompareWidget interface
public:
    virtual void SetLeftValue(QString leftValueFullFolderPath);
    virtual void SetRightValue(QString rightValueFullFolderPath);
private slots:
    void on_scaleSlider_valueChanged(int value);
    void on_scalePlusBtn_clicked();
    void on_scaleMinusBtn_clicked();
};

#endif // PHANTOMJS_COMPAREWIDGET_H
