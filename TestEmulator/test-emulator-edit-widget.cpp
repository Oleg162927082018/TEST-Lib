#include "test-emulator-edit-widget.h"
#include "ui_test-emulator-edit-widget.h"

#include <QFileDialog>
#include <QDirIterator>

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

void TestEmulatorEditWidget::SetData(QDomDocument *config, QDomDocument *params)
{
    //Bin path
    QDomElement binElement = params->firstChildElement("bin");
    if(binElement.isNull())
    {
        ui->binBox->setText("");
    }
    else
    {
        ui->binBox->setText(binElement.text());
    }

    //Percent of bugs
    QDomElement prcBugsElement = params->firstChildElement("prc-bugs");
    if(prcBugsElement.isNull())
    {
        ui->prcBugsBox->setValue(0);
    }
    else
    {
        ui->prcBugsBox->setValue(prcBugsElement.text().toInt());
    }
}

void TestEmulatorEditWidget::GetData(QDomDocument *config, QDomDocument *params)
{
    //Executable module path
    QDomElement binElement = params->firstChildElement("bin");
    if(binElement.isNull())
    {
        binElement = params->createElement("bin");
        params->appendChild(binElement);

        QDomText binValue = params->createTextNode(ui->binBox->text());
        binElement.appendChild(binValue);
    }
    else
    {
        binElement.firstChild().setNodeValue(ui->binBox->text());
    }

    //Percent of bugs
    QDomElement prcBugsElement = params->firstChildElement("prc-bugs");
    if(prcBugsElement.isNull())
    {
        prcBugsElement = params->createElement("prc-bugs");
        params->appendChild(prcBugsElement);

        QDomText prcBugsValue = params->createTextNode(QString::number(ui->prcBugsBox->value()));
        prcBugsElement.appendChild(prcBugsValue);
    }
    else
    {
        prcBugsElement.firstChild().setNodeValue(QString::number(ui->prcBugsBox->value()));
    }

    //Source
    QDomElement newSourcesElement = params->createElement("sources");

    for(int i = 0; i < ui->srcList->count(); i++)
    {
        QDomElement sourceElement = params->createElement("source");
        sourceElement.setAttribute("id", i);
        newSourcesElement.appendChild(sourceElement);

        QDomText sourceValue = params->createTextNode(ui->srcList->item(i)->text());
        sourceElement.appendChild(sourceValue);
    }

    QDomElement oldSourcesElement = params->firstChildElement("sources");
    if(oldSourcesElement.isNull())
    {
        params->appendChild(newSourcesElement);
    }
    else
    {
        params->replaceChild(newSourcesElement, oldSourcesElement);
    }
}

QMap<QString, QDomDocument *> *TestEmulatorEditWidget::GetTestList()
{
    QMap<QString, QDomDocument *> *testList = new QMap<QString, QDomDocument *>();

    const QStringList pattern = QStringList() << "*.png";

    for(int i = 0; i < ui->srcList->count(); i++)
    {
        QString srcId = QString::number(i);
        QDir srcFolder = QDir(ui->srcList->item(i)->text());

        //Get all search folders
        QStringList allSearchFolders = QStringList(srcFolder.absolutePath());
        QDirIterator it(srcFolder.absolutePath(), QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
        while(it.hasNext()) { allSearchFolders.append(it.next()); }

        for(int j = 0; j < allSearchFolders.count(); j++)
        {
            QFileInfoList fileInfoList = QDir(allSearchFolders.at(j)).entryInfoList(pattern, QDir::Files);

            for(int k = 0; k < fileInfoList.count(); k++)
            {
                QString relativeFileName = srcFolder.relativeFilePath(fileInfoList.at(k).filePath());

                QDomDocument *doc = new QDomDocument();

                QDomElement testNode = doc->createElement("path");
                doc->appendChild(testNode);

                QDomText pathValue = doc->createTextNode(relativeFileName);
                testNode.appendChild(pathValue);

                testNode.setAttribute("src", srcId);

                testList->insert(srcFolder.dirName() + "/" + relativeFileName, doc);
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
                               appFolder.filePath("phantomjs.exe"), "Executable module (*.exe)");

    if(!binFileName.isEmpty()&& !binFileName.isNull())
    {
        ui->binBox->setText(binFileName);
    }
}
