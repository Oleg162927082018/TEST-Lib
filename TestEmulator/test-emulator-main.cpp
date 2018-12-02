#include "test-emulator.h"

#include "test-emulator-edit-widget.h"
#include "test-emulator-output-comparator.h"
#include "test-emulator-compare-widget.h"

#include <QDir>
#include <QDirIterator>
#include <QDomDocument>

TestEmulatorTests::TestEmulatorTests()
{
}

TestEmulatorTests::~TestEmulatorTests()
{
}

const QString TestEmulatorTests::ID()
{
    return "Test Emulator";
}

const QString TestEmulatorTests::Name()
{
    return "Test emulator automated tests";
}

const QString TestEmulatorTests::Description()
{
    return "Test emulator automated tests.";
}

void TestEmulatorTests::GetRunCommand(QString testCaseFullFileName,
                                      QString extraTestCaseParams, QString testParams, QString outputFullFolderName,
                                      QString &out_cmd, QStringList &out_arg, QString &out_workDir)
{
    //test-emulator.exe [IMAGE FILE NAME] [PERCENT OF "BUGS"] [OUTPUT FOLDER]
    QDomDocument doc1;
    doc1.setContent("<root>" + testParams + "</root>");
    QDomNode rootNode = doc1.firstChild();

    QDomElement pathTestParamNode = rootNode.firstChildElement("path");
    QString testSubFileName = pathTestParamNode.text();
    QString srcNum = pathTestParamNode.attribute("src");

    QDomDocument doc2;
    doc2.setContent("<root>" + extraTestCaseParams + "</root>");
    QDomNode extraTestCaseParamNode = doc2.firstChild();

    QString binFileName = extraTestCaseParamNode.firstChildElement("bin").text();
    QString binFullFileName = QDir(QFileInfo(testCaseFullFileName).absoluteDir()).absoluteFilePath(binFileName);
    QString bugsProcent = extraTestCaseParamNode.firstChildElement("prc-bugs").text();

    QDomElement srcList = extraTestCaseParamNode.firstChildElement("sources");
    QDomElement srcPath = srcList.firstChildElement("source");

    QString imageFullFileName;
    while(!srcPath.isNull())
    {
        if(srcPath.attribute("id") == srcNum)
        {
            QDir srcDir(QFileInfo(testCaseFullFileName).absoluteDir().filePath(srcPath.text()));
            imageFullFileName = srcDir.absoluteFilePath(testSubFileName);
        }

        srcPath = srcPath.nextSiblingElement("source");
    }

    out_workDir = QFileInfo(binFullFileName).absolutePath();
    out_cmd = "\"" + binFullFileName + "\" \"" + imageFullFileName + "\" " + bugsProcent + " \"" + outputFullFolderName + "\"";
    return;
}

ITestOutputComparator *TestEmulatorTests::GetComparator()
{
    return new TestEmulatorOutputComparator();
}

ITestCaseEditWidget *TestEmulatorTests::GetTestCaseEditWidget(QWidget *parent)
{
    return new TestEmulatorEditWidget(parent);
}

IResultCompareWidget *TestEmulatorTests::GetResultCompareWidget(QWidget *parent)
{
    return new TestEmulatorCompareWidget(parent);
}
