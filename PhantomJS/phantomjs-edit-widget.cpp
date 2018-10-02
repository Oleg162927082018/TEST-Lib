#include "phantomjs-edit-widget.h"
#include "ui_phantomjs-edit-widget.h"

#include <QFileDialog>
#include <QDirIterator>

PhantomJsEditWidget::PhantomJsEditWidget(QWidget *parent) :
    ITestCaseEditWidget(parent),
    ui(new Ui::PhantomJsEditWidget)
{
    ui->setupUi(this);
}

PhantomJsEditWidget::~PhantomJsEditWidget()
{
    delete ui;
}

void PhantomJsEditWidget::SetData(QDomDocument *config, QDomDocument *params)
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

    //Options
    QDomElement optElement = params->firstChildElement("opt");
    if(optElement.isNull())
    {
        ui->optBox->setText("");
    }
    else
    {
        ui->optBox->setText(optElement.text());
    }
}

void PhantomJsEditWidget::GetData(QDomDocument *config, QDomDocument *params)
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

    //Options
    QDomElement optElement = params->firstChildElement("opt");
    if(optElement.isNull())
    {
        optElement = params->createElement("opt");
        params->appendChild(optElement);

        QDomText optValue = params->createTextNode(ui->optBox->text());
        optElement.appendChild(optValue);
    }
    else
    {
        optElement.firstChild().setNodeValue(ui->optBox->text());
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

QMap<QString, QDomDocument *> *PhantomJsEditWidget::GetTestList()
{
    QMap<QString, QDomDocument *> *testList = new QMap<QString, QDomDocument *>();

    const QStringList pattern = QStringList() << "*.js";

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

void PhantomJsEditWidget::on_srcAddBtn_clicked()
{
    QDir appFolder(qApp->applicationDirPath());

    QString srcFolderName = QFileDialog::getExistingDirectory(this, "Select Source Folder",
                               appFolder.filePath(""), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!srcFolderName.isEmpty()&& !srcFolderName.isNull())
    {
        ui->srcList->addItem(srcFolderName);
    }
}

void PhantomJsEditWidget::on_srcDelBtn_clicked()
{
    qDeleteAll(ui->srcList->selectedItems());
}

void PhantomJsEditWidget::on_binBtn_clicked()
{
    QDir appFolder(qApp->applicationDirPath());

    QString binFileName = QFileDialog::getOpenFileName(this, "Executable module",
                               appFolder.filePath("phantomjs.exe"), "Executable module (*.exe)");

    if(!binFileName.isEmpty()&& !binFileName.isNull())
    {
        ui->binBox->setText(binFileName);
    }
}
