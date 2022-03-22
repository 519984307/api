#include "map3dobjectpropertydialog.h"
#include "ui_map3dobjectpropertydialog.h"

Map3dObjectPropertyDialog::Map3dObjectPropertyDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Map3dObjectPropertyDialog)
{
    ui->setupUi(this);
}

Map3dObjectPropertyDialog::~Map3dObjectPropertyDialog()
{
    delete ui;
}

Map3dObject* Map3dObjectPropertyDialog::map3dObject() const
{
    return m_map3dObject;
}

void Map3dObjectPropertyDialog::setMap3dObject(Map3dObject* newMap3dObject)
{
    m_map3dObject = newMap3dObject;
    ui->edtName->setText(m_map3dObject->name());
    QColor c = m_map3dObject->color();
    m_color = c;
    int r, g, b;
    c.getRgb(&r, &g, &b);
    ui->btnColor->setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(r).arg(g).arg(b));
    ui->edtHeight->setText(QString("%1").arg(m_map3dObject->height()));
    ui->cbbObjectType->setCurrentText(m_map3dObject->objectType());
    ui->edtIconIndex->setText(QString("%1").arg(m_map3dObject->iconIndex()));
    ui->edtDevId->setText(m_map3dObject->devId());
}

void showMap3dObjectPropertyDialog(Map3dObject* obj)
{
    Map3dObjectPropertyDialog* dlg = new Map3dObjectPropertyDialog();
    dlg->setMap3dObject(obj);
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {

    }
    delete dlg;
}

void Map3dObjectPropertyDialog::on_btnColor_clicked()
{
    QColor c = QColorDialog::getColor(m_color);

    int r, g, b;
    c.getRgb(&r, &g, &b);
    ui->btnColor->setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(r).arg(g).arg(b));
    m_color = c;
}


void Map3dObjectPropertyDialog::on_btnOk_clicked()
{
    m_map3dObject->setName(ui->edtName->text());
    m_map3dObject->setColor(m_color);
    m_map3dObject->setHeight(ui->edtHeight->text().toFloat());
    m_map3dObject->setObjectType(ui->cbbObjectType->currentText());
    m_map3dObject->setIconIndex(ui->edtIconIndex->text().toInt());
    m_map3dObject->setDevId(ui->edtDevId->text());
    accept();
}


void Map3dObjectPropertyDialog::on_btnCancel_clicked()
{
    reject();
}

