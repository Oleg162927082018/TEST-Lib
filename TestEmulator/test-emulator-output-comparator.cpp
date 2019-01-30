#include "test-emulator-output-comparator.h"
#include <QDir>

bool TestEmulatorOutputComparator::GetTestStatus(int status_index, QString &out_label, QColor &out_color, QString &out_description)
{
    out_description = "";
    switch(status_index) {
        case 0:
           out_label = "Not started";
           out_color = QColor(128,128,128);
           return true;
        case 1: //Exit code != 0
           out_label = "EXIT CODE";
           out_color = QColor(128,0,0);
           return true;
        case 2: //The best
           out_label = "Benchmark created";
           out_color = QColor(112,146,190);
           return true;
        case 3: //Perfect
           out_label = "Benchmark created";
           out_color = QColor(255,255,128);
           return true;
        case 4: //The best
           out_label = "Benchmark updated";
           out_color = QColor(64,128,128);
           return true;
        case 5: //Perfect
           out_label = "Benchmark updated";
           out_color = QColor(255,255,0);
           return true;
        case 6:
           out_label = "PASS";
           out_color = QColor(0,255,0);
           return true;
        case 7: //First fail
           out_label = "FAIL";
           out_color = QColor(255,0,0);
           return true;
        case 8: //Second fail
           out_label = "FAIL";
           out_color = QColor(255,128,128);
           return true;
        case 9: //Timeout expired
           out_label = "Timeout expired";
           out_color = QColor(0,0,255);
           return true;
        default:
            return false;
    }
}

void TestEmulatorOutputComparator::CalculateStatusIndex(ExitStatus exitStatus, int exitCode, qint64 exeTimeMs,
                                  QStringList consoleOutput, QString outputFullFolderName,
                                  int *benchmarkCompareResult, int *previousCompareResult,
                                  BenchmarkStatus benchmarkStatus,
                                  int &out_status_index, QString &out_comment)
{
    out_comment = "";

    if(exitStatus == NOT_STARTED) {
        out_status_index = 0;
        return;
    }

    if(exitStatus == EXIT_CODE) {
        out_status_index = 1;
        out_comment = QString::asprintf(": %i", exitCode);
        return;
    }

    if(exitStatus == TIMEOUT_EXPIRED) {
        out_status_index = 9;
        return;
    }

    //if(exitStatus == COMPLETED) {

    if(benchmarkStatus == THE_BEST_BENCHMARK_CREATED) {
        out_status_index = 2;
        return;
    }

    if(benchmarkStatus == PERFECT_BENCHMARK_CREATED) {
        out_status_index = 3;
        return;
    }

    if(benchmarkStatus == THE_BEST_BENCHMARK_UPDATED) {
        out_status_index = 4;
        return;
    }

    if(benchmarkStatus == PERFECT_BENCHMARK_UPDATED) {
        out_status_index = 5;
        return;
    }

    //if((exitStatus == COMPLETED) && (benchmarkStatus == NO_BENCHMARK)) {

    if((benchmarkCompareResult == nullptr) || (*benchmarkCompareResult == 0)) {
        out_status_index = 6;
        return;
    }

    //if((exitStatus == COMPLETED) && (benchmarkStatus == NO_BENCHMARK) && (*benchmarkCompareResult != 0)) {
    if((previousCompareResult == nullptr) || (*previousCompareResult != 0)) {
        out_status_index = 7;
        return;
    }

    //if((exitStatus == COMPLETED) && (benchmarkStatus == NO_BENCHMARK) && (*benchmarkCompareResult != 0) && (*previousCompareResult == 0)) {
    out_status_index = 8;

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
