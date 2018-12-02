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
    explicit TestEmulatorEditWidget(QWidget *parent = nullptr);
    ~TestEmulatorEditWidget();

private slots:
    void on_srcAddBtn_clicked();
    void on_srcDelBtn_clicked();
    void on_binBtn_clicked();

private:
    Ui::TestEmulatorEditWidget *ui;

    // ITestCaseEditWidget interface
public:
    virtual void SetData(QString config, QString params);
    virtual void GetData(QString &config, QString &params);
    //Return collection of pairs path of test and string which contain data for run test
    //Example: <"rootFolder/subFolder/subSubFolder/test-001.script","<path src="0">test-001.script</path>"
    virtual QMap<QString, QString> *GetTestList();
};

#endif // TESTEMULATOR_EDITWIDGET_H
