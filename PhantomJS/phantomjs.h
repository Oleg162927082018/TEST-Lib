#ifndef PHANTOMJS_H
#define PHANTOMJS_H

#include "../../TTI/Common/itestcasetemplate.h"
#include "phantomjs_global.h"

class PHANTOMJS_SHARED_EXPORT PhantomJsTests: public ITestCaseAdapter
{
public:
    PhantomJsTests();
    virtual ~PhantomJsTests();

// ITestCaseTemplate interface
public:
    virtual const QString ID();
    virtual const QString Name();
    virtual const QString Description();

    virtual void GetRunCommand(QString testCaseFullFileName, QDomDocument extraParams, QDomDocument testParams,
                               QString outputFullFolderName, QString &out_cmd, QStringList &out_arg, QString &out_workDir);

    virtual ITestOutputComparator *GetComparator();
    virtual ITestCaseEditWidget *GetTestCaseEditWidget(QWidget *parent);
    virtual IResultCompareWidget *GetResultCompareWidget(QWidget *parent);
};

#endif // PHANTOMJS_H
