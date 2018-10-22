#ifndef TESTEMULATOR_EDITWIDGET_H
#define TESTEMULATOR_EDITWIDGET_H

#include "../../TTI/Common/itestcasetemplate.h"

namespace Ui {
class TestEmulatorEditWidget;
}

class TestEmulatorEditWidget : public ITestCaseEditWidget
{
    Q_OBJECT

public:
    explicit TestEmulatorEditWidget(QWidget *parent = 0);
    ~TestEmulatorEditWidget();

private slots:
    void on_srcAddBtn_clicked();
    void on_srcDelBtn_clicked();
    void on_binBtn_clicked();

private:
    Ui::TestEmulatorEditWidget *ui;

    // ITestCaseEditWidget interface
public:
    virtual void SetData(QDomDocument *config, QDomDocument *params);
    virtual void GetData(QDomDocument *config, QDomDocument *params);
    virtual QMap<QString, QDomDocument *> *GetTestList();
};

#endif // TESTEMULATOR_EDITWIDGET_H
