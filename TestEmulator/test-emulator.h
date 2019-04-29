#ifndef TESTEMULATOR_H
#define TESTEMULATOR_H

#include "../../TTI/Common/itestcasetemplate.h"

#include "test-emulator_global.h"

class TESTEMULATOR_SHARED_EXPORT TestEmulatorTests: public ITestCaseAdapter
{
public:
    TestEmulatorTests();
    virtual ~TestEmulatorTests();

// ITestCaseTemplate interface
public:
    virtual const QString ID();
    virtual const QString Name();
    virtual const QString Description();

    virtual void GetRunCommand(QString testCaseFullFileName,
                               QString extraTestCaseParams, QString testParams, QString outputFullFolderName,
                               QString &out_cmd, QStringList &out_arg, QString &out_workDir);

    virtual ITestOutputComparator *GetComparator();
    virtual ITestCaseEditWidget *GetTestCaseEditWidget(QWidget *parent);
    virtual IResultCompareWidget *GetResultCompareWidget(QWidget *parent);
};

#endif // TESTEMULATOR_H
