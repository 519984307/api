#include "fnappbarsetitemwidget.h"
#include "ui_fnappbarsetitemwidget.h"

FnAppBarSetItemWidget::FnAppBarSetItemWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FnAppBarSetItemWidget)
{
    ui->setupUi(this);
}

FnAppBarSetItemWidget::~FnAppBarSetItemWidget()
{
    delete ui;
}

void FnAppBarSetItemWidget::on_btnOpen_clicked()
{
    QString path=QFileDialog::getOpenFileName();
    ui->edtPath->setText(path);
}

const QString &FnAppBarSetItemWidget::path()
{
  m_path=ui->edtPath->text();
  m_path=m_path.replace("file:///","");
    return m_path;
}

void FnAppBarSetItemWidget::setPath(const QString &newPath)
{
    m_path = newPath;
    ui->edtPath->setText(m_path);
}

const QString &FnAppBarSetItemWidget::caption()
{
    m_caption=ui->edtCaption->text();
    return m_caption;
}

void FnAppBarSetItemWidget::setCaption(const QString &newCaption)
{
    m_caption = newCaption;
    ui->edtCaption->setText(m_caption);
}

