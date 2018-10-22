#ifndef TESTEMULATOR_OUTPUT_COMPARATOR_H
#define TESTEMULATOR_OUTPUT_COMPARATOR_H

#include "../../TTI/Common/itestcasetemplate.h"

class TestEmulatorOutputComparator : public ITestOutputComparator
{
public:
    virtual void CalculateStatus(QStringList consoleOutput, QString outputFullFolderName,
								int exitCode, qint64 exeTimeMs, int benchmarkCompareResult, int previousCompareResult,
								QString &out_status, QColor &out_color);
    virtual int Compare(QString outputFullFolderName1, QString outputFullFolderName2);
};

#endif // TESTEMULATOR_OUTPUT_COMPARATOR_H
