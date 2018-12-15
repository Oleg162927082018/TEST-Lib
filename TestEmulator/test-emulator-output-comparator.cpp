#include "test-emulator-output-comparator.h"
#include <QDir>

void TestEmulatorOutputComparator::CalculateStatus(QStringList consoleOutput, QString outputFullFolderName,
                                           int exitCode, qint64 exeTimeMs,
                                           int *benchmarkCompareResult, int *previousCompareResult,
                                           QString &out_status, QColor &out_color)
{
    if(exitCode != 0) {

        out_status = QString::asprintf("FAIL: %i", exitCode);
        out_color = QColor(128,0,0);

    } else {

        if(benchmarkCompareResult == nullptr)
        {
            out_status = "PASS";
            out_color = QColor(0,255,0);

        } else if(*benchmarkCompareResult == 0) {

            out_status = "PASS";
            out_color = QColor(0,255,0);

        } else {

            if(previousCompareResult == nullptr) {

                out_status = "FAIL";
                out_color = QColor(255,0,0);

            } else if(*previousCompareResult == 0) {

                out_status = "FAIL";
                out_color = QColor(255,128,128);

            } else {

                out_status = "FAIL";
                out_color = QColor(255,0,0);

            }
        }
    }
}

int TestEmulatorOutputComparator::Compare(QString outputFullFolderName1, QString outputFullFolderName2)
{
    QString screenShotFullFileName1 = QDir::cleanPath(outputFullFolderName1 + "/img.png");
    QString screenShotFullFileName2 = QDir::cleanPath(outputFullFolderName2 + "/img.png");

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
