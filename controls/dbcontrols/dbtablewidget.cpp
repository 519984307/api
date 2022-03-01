#include "dbtablewidget.h"
#include "ui_dbtablewidget.h"

DbTableWidget::DbTableWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::DbTableWidget)
{
    ui->setupUi(this);

}

DbTableWidget::~DbTableWidget()
{
    delete ui;
}

QString DbTableWidget::tableName() const
{
    return m_tableName;
}

void DbTableWidget::setTableName(const QString& tableName)
{
    m_tableName = tableName;
    m_model = new QSqlTableModel(this, m_db);
    qDebug() << m_db.isOpen();
    m_model->setTable(m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_helper = new ModelHelper(m_model, ui->lvData, this);
    emit ui->btnRefresh->clicked();

}

QSqlDatabase DbTableWidget::db() const
{
    return m_db;
}

void DbTableWidget::setDb(const QSqlDatabase& db)
{
    m_db = db;
}





void DbTableWidget::on_btnRefresh_clicked()
{
    m_model->select();
    bool ret = m_model->select();
    if (!ret)
    {
        ui->lblInfo->setText(m_model->lastError().text());
    }
    ui->lblTableInfo->setText(QString("行%1 列:%2").arg(m_model->rowCount()).arg(m_model->columnCount()));
    m_helper->addDefaultContextMenus();
    m_helper->setTableName(m_tableName);
}
