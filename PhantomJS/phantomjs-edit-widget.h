#ifndef PHANTOMJS_EDITWIDGET_H
#define PHANTOMJS_EDITWIDGET_H

#include "../../TTI/Common/itestcasetemplate.h"

namespace Ui {
class PhantomJsEditWidget;
}

class PhantomJsEditWidget : public ITestCaseEditWidget
{
    Q_OBJECT

public:
    explicit PhantomJsEditWidget(QWidget *parent = 0);
    ~PhantomJsEditWidget();

private slots:
    void on_srcAddBtn_clicked();
    void on_srcDelBtn_clicked();
    void on_binBtn_clicked();

private:
    Ui::PhantomJsEditWidget *ui;

    // ITestCaseEditWidget interface
public:
    virtual void SetData(QDomDocument *config, QDomDocument *params);
    virtual void GetData(QDomDocument *config, QDomDocument *params);
    virtual QMap<QString, QDomDocument *> *GetTestList();
};

#endif // PHANTOMJS_EDITWIDGET_H
