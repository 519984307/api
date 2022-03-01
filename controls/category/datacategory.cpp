#include "datacategory.h"
#include "ui_datacategory.h"

DataCateGory::DataCateGory(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DataCateGory)
{
    ui->setupUi(this);
}

DataCateGory::~DataCateGory()
{
    qDebug() << "~DataCateGory()";
    delete ui;
}

QString DataCateGory::caption() const
{
    return m_caption;
}

void DataCateGory::setCaption(const QString& caption)
{
    m_caption = caption;
}

void DataCateGory::paintEvent(QPaintEvent* event)
{
    QRect rc;

    QPainter painter;
    painter.begin(this);
    rc.setRect(6, 0, width() - 12, height());
    QFont font = painter.font();
    font.setFamily("微软雅黑");
    font.setPointSize(11);
    painter.setFont(font);
    painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, m_caption);
    painter.end();
}

void DataCateGory::mousePressEvent(QMouseEvent* event)
{
    m_listWidget->setCurrentItem(m_item);
    emit onClick();
}

int DataCateGory::id() const
{
    return m_id;
}

void DataCateGory::setId(int id)
{
    m_id = id;
}

QListWidget* DataCateGory::listWidget() const
{
    return m_listWidget;
}

void DataCateGory::setListWidget(QListWidget* listWidget)
{
    m_listWidget = listWidget;
}

QListWidgetItem* DataCateGory::item() const
{
    return m_item;
}

void DataCateGory::setItem(QListWidgetItem* item)
{
    m_item = item;
}

DataCateGoryItem newDataCateGoryItem(int id, QString name)
{
    DataCateGoryItem item;
    item.id = id;
    item.name = name;
    return item;
}
