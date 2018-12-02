#include "test-emulator-edit-widget.h"
#include "ui_test-emulator-edit-widget.h"

#include <QFileDialog>
#include <QDirIterator>
#include <QStringBuilder>
#include <QDomDocument>

TestEmulatorEditWidget::TestEmulatorEditWidget(QWidget *parent) :
    ITestCaseEditWidget(parent),
    ui(new Ui::TestEmulatorEditWidget)
{
    ui->setupUi(this);
}

TestEmulatorEditWidget::~TestEmulatorEditWidget()
{
    delete ui;
}

void TestEmulatorEditWidget::SetData(QString config, QString params)
{
    QDomDocument doc;
    doc.setContent("<root>" + params + "</root>");
    QDomNode rootNode = doc.firstChild();

    //Bin path
    QDomElement binElement = rootNode.firstChildElement("bin");
    if(binElement.isNull())
    {
        ui->binBox->setText("");
    }
    else
    {
        ui->binBox->setText(binElement.text());
    }

    //Percent of bugs
    QDomElement prcBugsElement = rootNode.firstChildElement("prc-bugs");
    if(prcBugsElement.isNull())
    {
        ui->prcBugsBox->setValue(0);
    }
    else
    {
        ui->prcBugsBox->setValue(prcBugsElement.text().toInt());
    }

    //Sources
    QDomNode sourceNode = rootNode.firstChildElement("sources").firstChild();
    while(!sourceNode.isNull())
    {
        ui->srcList->addItem(sourceNode.toElement().text());
        sourceNode = sourceNode.nextSibling();
    }
}

void TestEmulatorEditWidget::GetData(QString &config, QString &params)
{
    params = "<bin>" + ui->binBox->text() + "</bin>\n" +
             "<prc-bugs>" + QString::number(ui->prcBugsBox->value()) + "</prc-bugs>\n";

    params += "<sources>\n";
    for(int i = 0; i < ui->srcList->count(); i++)
        { params += "  <source id=\"" + QString::number(i) + "\">" + ui->srcList->item(i)->text() + "</source>\n"; }
    params += "</sources>";
}

QMap<QString, QString> *TestEmulatorEditWidget::GetTestList()
{
    QMap<QString, QString> *testList = new QMap<QString, QString>();

    const QStringList pattern = QStringList() << "*.png";

    //For each source
    for(int i = 0; i < ui->srcList->count(); i++)
    {
        QString srcId = QString::number(i);
        QDir srcFolder = QDir(ui->srcList->item(i)->text());

        //Get all search folders
        QStringList allSearchFolders = QStringList(srcFolder.absolutePath());
        QDirIterator it(srcFolder.absolutePath(), QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
        while(it.hasNext()) { allSearchFolders.append(it.next()); }

        //For each sub folders and root (source) folder
        for(int j = 0; j < allSearchFolders.count(); j++)
        {
            QFileInfoList fileInfoList = QDir(allSearchFolders.at(j)).entryInfoList(pattern, QDir::Files);

            //For each files which was found
            for(int k = 0; k < fileInfoList.count(); k++)
            {
                QString relativeFileName = srcFolder.relativeFilePath(fileInfoList.at(k).filePath());
                testList->insert(srcFolder.dirName() + "/" + relativeFileName,
                                 "<path src=\"" + srcId + "\">" + relativeFileName + "</path>");
            }
        }
    }
    return testList;
}

void TestEmulatorEditWidget::on_srcAddBtn_clicked()
{
    QDir appFolder(qApp->applicationDirPath());

    QString srcFolderName = QFileDialog::getExistingDirectory(this, "Select Source Folder",
                               appFolder.filePath(""), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!srcFolderName.isEmpty()&& !srcFolderName.isNull())
    {
        ui->srcList->addItem(srcFolderName);
    }
}

void TestEmulatorEditWidget::on_srcDelBtn_clicked()
{
    qDeleteAll(ui->srcList->selectedItems());
}

void TestEmulatorEditWidget::on_binBtn_clicked()
{
    QDir appFolder(qApp->applicationDirPath());

    QString binFileName = QFileDialog::getOpenFileName(this, "Executable module",
                               appFolder.filePath("test-emulator.exe"), "Executable module (*.exe)");

    if(!binFileName.isEmpty()&& !binFileName.isNull())
    {
        ui->binBox->setText(binFileName);
    }
}
