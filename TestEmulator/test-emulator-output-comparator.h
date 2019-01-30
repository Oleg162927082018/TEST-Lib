#ifndef TESTEMULATOR_OUTPUT_COMPARATOR_H
#define TESTEMULATOR_OUTPUT_COMPARATOR_H

#include "../../TTI/Common/itestcasetemplate.h"

class TestEmulatorOutputComparator : public ITestOutputComparator
{
public:
    virtual bool GetTestStatus(int status_index, QString &out_label, QColor &out_color, QString &out_description);

    virtual void CalculateStatusIndex(ExitStatus exitStatus, int exitCode, qint64 exeTimeMs,
                                      QStringList consoleOutput, QString outputFullFolderName,
                                      int *benchmarkCompareResult, int *previousCompareResult,
                                      BenchmarkStatus benchmarkStatus,
                                      int &out_status_index, QString &out_comment);

    virtual int Compare(QString outputFullFolderName1, QString outputFullFolderName2);
};

#endif // TESTEMULATOR_OUTPUT_COMPARATOR_H
