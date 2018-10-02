#include "phantomjs-output-comparator.h"
#include <QDir>

void PhantomJsOutputComparator::CalculateStatus(QStringList consoleOutput, QString outputFullFolderName,
                                           int exitCode, qint64 exeTimeMs, int benchmarkCompareResult, int previousCompareResult,
                                           QString &out_status, QColor &out_color)
{
    if(benchmarkCompareResult == -1)
    {
        if(exitCode == 0)
        {
            //If result of compare with benchmark is -1, it means benchmark not found
            //or compression level set up zero. It is not valid for TATest.
            //In this case application set benchmark (or the best result) current result.
            out_status = "Benchmark created";
            out_color = QColor(64,128,128);
            return;
        }
        else
        {
            out_status = "Test crashed!";
            out_color = QColor(128,0,0);
            return;
        }
    }

    if(benchmarkCompareResult == 0)
    {
        out_status = "PASS";
        out_color = QColor(0,255,0);
        return;
    }

    if(benchmarkCompareResult > 0)
    {
        if(previousCompareResult != 0)
        {
            out_status = "FAIL";
            out_color = QColor(255,0,0);
            return;
        }
        else
        {
            out_status = "FAIL";
            out_color = QColor(255,128,128);
            return;
        }
    }
}

int PhantomJsOutputComparator::Compare(QString outputFullFolderName1, QString outputFullFolderName2)
{
    QString screenShotFullFileName1 = QDir::cleanPath(outputFullFolderName1 + "/1.png");
    QString screenShotFullFileName2 = QDir::cleanPath(outputFullFolderName2 + "/1.png");

    if((!QFileInfo(screenShotFullFileName1).exists()) || (!QFileInfo(screenShotFullFileName2).exists()))
    {
        return -1;
    }

    QImage img1(screenShotFullFileName1);
    QImage img2(screenShotFullFileName2);
    if(img1.isNull() || img2.isNull())
    {
        return -1;
    }
    else
    {
        if(img1 == img2)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}
