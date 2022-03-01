#include "sqlrunwidget.h"
#include "ui_sqlrunwidget.h"

SqlRunWidget::SqlRunWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SqlRunWidget)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(this);
    ui->lvData->setModel(m_model);
    m_helper = new ModelHelper(m_model, ui->lvData, this);
    m_helper->addDefaultContextMenus();
    ui->edtSql->setFocus();
}

SqlRunWidget::~SqlRunWidget()
{
    qDebug() << "SqlRunWidget::~SqlRunWidget()";
    delete ui;
}

QSqlDatabase SqlRunWidget::db() const
{
    return m_db;
}

void SqlRunWidget::setDb(const QSqlDatabase& db)
{
    m_db = db;
}

void SqlRunWidget::on_btnRun_clicked()
{
    QString sql = ui->edtSql->toPlainText();
    emit saveSql(m_uuid, sql);
    ui->edtLog->clear();
    m_model->clear();
    QSqlQuery qry(m_db);

    bool ret = qry.exec(sql);
    int index = ret == true ? 0 : 1;
    ui->wgtTabs->setCurrentIndex(index);
    if (ret)
    {
        ui->edtLog->appendHtml("<span style=\"color: #008000;\">执行成功</span>");
        sql = sql.toLower().trimmed();
        if (sql.startsWith("select"))
        {
            int n = qry.record().count();
            QStringList labels;
            for (int i = 0; i < n; i++)
            {
                labels << qry.record().field(i).name();
            }
            m_model->setHorizontalHeaderLabels(labels);
            while (qry.next())
            {
                QList<QStandardItem*> items;
                for (int i = 0; i < n; i++)
                {
                    QStandardItem* item = new QStandardItem();
                    item->setText(qry.value(i).toString());
                    items << item;

                }
                m_model->appendRow(items);
            }
        }
    }
    else
    {
        ui->edtLog->appendHtml("<span style=\"color:#CC2929;\">执行失败</span>");
        ui->edtLog->appendHtml("<span style=\"color:#CC2929;\">错误:" +
                               qry.lastError().text() + "</span>");

    }

    ui->edtLog->appendHtml("<hr>");
    ui->edtLog->appendHtml("");

}

QString SqlRunWidget::sql() const
{
    return m_sql;
}

void SqlRunWidget::setSql(const QString& sql)
{
    m_sql = sql;
    ui->edtSql->setPlainText(sql);
}

QString SqlRunWidget::uuid() const
{
    return m_uuid;
}

void SqlRunWidget::setUuid(const QString& uuid)
{
    m_uuid = uuid;
}


