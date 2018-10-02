#include "phantomjs.h"

QList<ITestCaseAdapter *> GetTestCaseAdapters(void)
{
    QList<ITestCaseAdapter *> tcList;

    tcList.append(new PhantomJsTests());

    return tcList;
}
