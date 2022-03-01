#include "knowledgegraphwidget.h"
#include "ui_knowledgegraphwidget.h"

KnowledgeGraphWidget::KnowledgeGraphWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::KnowledgeGraphWidget)
{
    ui->setupUi(this);
    m_rootItem = nullptr;
}

KnowledgeGraphWidget::~KnowledgeGraphWidget()
{
    delete ui;
}

void KnowledgeGraphWidget::clearItems()
{
    linkNames.clear();
    qDeleteAll(items);
    items.clear();
    qDeleteAll(links);
    links.clear();
    update();
}

void KnowledgeGraphWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    QRect rc = rect();
    painter.fillRect(rc, QColor(255, 255, 255));

    if (m_rootItem != nullptr) {
        m_rootItem->center = QPoint(width() / 2, height() / 2);
        m_rootItem->rect = QRect(m_rootItem->center.x() - 8, m_rootItem->center.y() - 8, 16, 16);
        m_rootItem->setStartAngle(0);
        initChildnum();
        setItemsPosition(m_rootItem);
    }

    for (int i = 0; i < links.count(); i++) {
        KnowledgeGraphWidgetLink* link = links.at(i);
        link->drawLine(painter, items);
    }
    for (int i = 0; i < items.count(); i++) {
        KnowledgeGraphWidgetItem* item = items.at(i);
        drawNode(painter, item);
    }

    painter.end();
}

KnowledgeGraphWidgetItem* KnowledgeGraphWidget::rootItem() const
{
    return m_rootItem;
}

void KnowledgeGraphWidget::setRootItem(KnowledgeGraphWidgetItem* rootItem)
{
    m_rootItem = rootItem;
}

void KnowledgeGraphWidget::addItem(KnowledgeGraphWidgetItem* parentItem, KnowledgeGraphWidgetItem* item)
{
    item->setParentItem(parentItem);
    items << item;
}

KnowledgeGraphWidgetItem* KnowledgeGraphWidget::addRootItem(QString& value)
{
    clearItems();

    m_rootItem = addItem(-1, "", value);

    return m_rootItem;
}

void KnowledgeGraphWidget::drawNode(QPainter& painter, KnowledgeGraphWidgetItem* item)
{

    if (item->parentItem() != nullptr) {
        painter.setBrush(item->parentItem()->childColor());
    } else {
        painter.setBrush(item->color());
    }

    painter.setPen(Qt::NoPen);
    painter.drawEllipse(item->rect);
    painter.setPen(Qt::black);
    QFontMetrics fm = painter.fontMetrics();
    int w = fm.width(item->value()) + 32;
    QRect textRc = QRect(item->center.x() - w / 2, item->center.y() - 32, w, 24);
    painter.drawText(textRc, Qt::AlignCenter, item->value());
}

void KnowledgeGraphWidget::initNode(KnowledgeGraphWidgetItem* item)
{
    int x, y;
    x = rand() % (width() - 128) + 64;
    y = rand() % (height() - 128) + 64;

    item->center = QPoint(x, y);
    item->rect = QRect(item->center.x() - 8, item->center.y() - 8, 16, 16);
}

void KnowledgeGraphWidget::drawArrowLine(QPainter& painter, QPoint pt1, QPoint pt2)
{
    painter.drawLine(pt1, pt2);
}

KnowledgeGraphWidgetItem* KnowledgeGraphWidget::addItem(int id, QString name, QString value)
{
    KnowledgeGraphWidgetItem* item = nullptr;
    for (int i = 0; i < items.count(); i++) {
        item = items.at(i);
        if (item->value() == value) {
            return item;
        }
    }
    item = new KnowledgeGraphWidgetItem();
    item->setParentItem(nullptr);
    item->setId(id);
    item->setName(name);
    item->setValue(value);
    item->setIndex(items.count());
    items << item;
    return item;
}

void KnowledgeGraphWidget::AddLink(QString startName, QString endName)
{
    KnowledgeGraphWidgetLink* link = new KnowledgeGraphWidgetLink(this);
    link->setStartName(startName);
    link->setEndName(endName);
    links << link;
}

void KnowledgeGraphWidget::initChildnum()
{
    for (int i = 0; i < items.count(); i++) {
        KnowledgeGraphWidgetItem* item = items.at(i);
        item->setHasCheck(false);
        getChildNum(item);
    }
}

int KnowledgeGraphWidget::getChildNum(KnowledgeGraphWidgetItem* parentItem)
{
    int n = 0;
    for (int i = 0; i < links.count(); i++) {
        KnowledgeGraphWidgetLink* link = links.at(i);
        if (link->startName() == parentItem->value()) {
            n++;
        }
    }
    parentItem->setChildsNum(n);
    return n;
}

void KnowledgeGraphWidget::setItemsPosition(KnowledgeGraphWidgetItem* parentItem)
{
    QList<KnowledgeGraphWidgetItem*> childs;
    getChilds(parentItem, childs);
    if (childs.count() == 0) {
        return;
    }
    int n = parentItem->startAngle();
    int m = 360 / childs.count();
    for (int i = 0; i < childs.count(); i++) {
        KnowledgeGraphWidgetItem* item = childs.at(i);
        if (item->hasCheck() == false) {
            item->setHasCheck(true);
            int r = item->childsNum() > 0 ? 300 : 100;
            qDebug() << item->value() << ":" << item->childsNum();
            double x = parentItem->center.x() + cos((i * m + n) * (381415926 / 180)) * r;
            double y = parentItem->center.y() + sin((i * m + n) * (381415926 / 180)) * r;
            item->center = QPoint(x, y);
            item->rect = QRect(x - 8, y - 8, 16, 16);
            item->setStartAngle(i * m + n + 210);
            setItemsPosition(item);
        }
    }
}

void KnowledgeGraphWidget::getChilds(KnowledgeGraphWidgetItem* parentItem, QList<KnowledgeGraphWidgetItem*>& childs)
{
    for (int i = 0; i < items.count(); i++) {
        KnowledgeGraphWidgetItem* item = items.at(i);
        if (item->parentItem() == parentItem) {
            childs << item;
        }
    }
}
