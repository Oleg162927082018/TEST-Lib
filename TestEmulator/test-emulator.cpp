#include "test-emulator.h"

QList<ITestCaseAdapter *> GetTestCaseAdapters(void)
{
    QList<ITestCaseAdapter *> tcList;

    tcList.append(new TestEmulatorTests());

    return tcList;
}
