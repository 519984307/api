#include "fnappbarsetdialog.h"
#include "ui_fnappbarsetdialog.h"

FnAppBarSetDialog::FnAppBarSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FnAppBarSetDialog)
{
    ui->setupUi(this);

}

FnAppBarSetDialog::~FnAppBarSetDialog()
{
    delete ui;
}

void FnAppBarSetDialog::on_btnAdd_clicked()
{
    QListWidgetItem *item=new QListWidgetItem(ui->lvData);
    item->setSizeHint(QSize(ui->lvData->width()-48,48));
    FnAppBarSetItemWidget *w=new FnAppBarSetItemWidget(ui->lvData);
    ui->lvData->setItemWidget(item,w);

}

const QString &FnAppBarSetDialog::configPath() const
{
    return m_configPath;
}

void FnAppBarSetDialog::setConfigPath(const QString &newConfigPath)
{
    m_configPath = newConfigPath;

}

void FnAppBarSetDialog::saveConfigs()
{
    QJsonDocument jdoc;
    QJsonArray arr;
    for(int i=0;i<ui->lvData->count();i++)
    {
        QListWidgetItem *item=ui->lvData->item(i);
        FnAppBarSetItemWidget *w=static_cast<FnAppBarSetItemWidget*>(ui->lvData->itemWidget(item));
        QJsonObject obj;
        obj["uuid"]=w->uuid();
        obj["caption"]=w->caption();
        obj["path"]=w->path();
        arr.append(obj);
    }
    jdoc.setArray(arr);
    QFile file(m_configPath);
    file.open(QIODevice::WriteOnly);
    file.write(jdoc.toJson());
    file.close();

}




void FnAppBarSetDialog::on_btnOk_clicked()
{
    saveConfigs();
    accept();

}


void FnAppBarSetDialog::on_btnCancel_clicked()
{
    reject();
}

const QList<FnAppBarItem *> &FnAppBarSetDialog::items() const
{
    return m_items;
}

void FnAppBarSetDialog::setItems(const QList<FnAppBarItem *> &newItems)
{
    m_items = newItems;
    for(int i=0;i<m_items.count();i++)
    {
        FnAppBarItem *appItem=m_items.at(i);
        QListWidgetItem *item=new QListWidgetItem(ui->lvData);
        item->setSizeHint(QSize(ui->lvData->width()-48,48));
        FnAppBarSetItemWidget *w=new FnAppBarSetItemWidget(ui->lvData);
        w->setUuid(appItem->uuid());
        w->setCaption(appItem->caption());
        w->setPath(appItem->path());
        ui->lvData->setItemWidget(item,w);
    }

}

