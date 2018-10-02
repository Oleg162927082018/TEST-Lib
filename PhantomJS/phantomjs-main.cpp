#include "phantomjs.h"

#include "phantomjs-edit-widget.h"
#include "phantomjs-output-comparator.h"
#include "phantomjs-compare-widget.h"

#include <QDir>
#include <QDirIterator>

PhantomJsTests::PhantomJsTests()
{
}

PhantomJsTests::~PhantomJsTests()
{
}

const QString PhantomJsTests::ID()
{
    return "PhantomJS";
}

const QString PhantomJsTests::Name()
{
    return "PhantomJS automated tests";
}

const QString PhantomJsTests::Description()
{
    return "PhantomJS automated tests.";
}

void PhantomJsTests::GetRunCommand(QString testCaseFullFileName, QDomDocument extraParams, QDomDocument testParams,
                                       QString outputFullFolderName, QString &out_cmd, QStringList &out_arg, QString &out_workDir)
{
    //phantomjs.cmd [JAVA SCRIPT] [OPTIONS] [http|https] [URL] [OUTPUT FOLDER]

    QString binFileName = extraParams.firstChildElement("bin").text();
    QString binFullFileName = QDir(QFileInfo(testCaseFullFileName).absoluteDir()).absoluteFilePath(binFileName);

    QString options = extraParams.firstChildElement("opt").text();
    QString url = extraParams.firstChildElement("url").text();
    QString urlProtocol = extraParams.firstChildElement("url").attribute("protocol", "http");

    QString scriptFullFileName;

    QString testSubFileName = testParams.firstChildElement("path").text();
    QString srcNum = testParams.firstChildElement("path").attribute("src");
    QDomElement srcList = extraParams.firstChildElement("sources");
    QDomElement srcPath = srcList.firstChildElement("source");
    while(!srcPath.isNull())
    {
        if(srcPath.attribute("id") == srcNum)
        {
            QDir srcDir(QFileInfo(testCaseFullFileName).absoluteDir().filePath(srcPath.text()));
            scriptFullFileName = srcDir.absoluteFilePath(testSubFileName);
        }

        srcPath = srcPath.nextSiblingElement("source");
    }

    out_workDir = QFileInfo(binFullFileName).absolutePath();
    out_cmd = "\"" + binFullFileName + "\" " + options + " \"" + scriptFullFileName + "\" " + urlProtocol + " " + url + " \"" + outputFullFolderName + "\" ";
    return;
}

ITestOutputComparator *PhantomJsTests::GetComparator()
{
    return new PhantomJsOutputComparator();
}

ITestCaseEditWidget *PhantomJsTests::GetTestCaseEditWidget(QWidget *parent)
{
    return new PhantomJsEditWidget(parent);
}

IResultCompareWidget *PhantomJsTests::GetResultCompareWidget(QWidget *parent)
{
    return new PhantomJsCompareWidget(parent);
}
