#include "countlabelview.h"
#include "ui_countlabelview.h"

CountLabelView::CountLabelView(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CountLabelView)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_addAction = new QAction(this);
    m_addAction->setText("添加标签");
    connect(m_addAction, &QAction::triggered, this, &CountLabelView::onAddActionTriggered);
    addMenus();
    m_helper->setItemsTop(16);
    m_helper->setMaxTop(16);
}

CountLabelView::~CountLabelView()
{
    delete ui;
}

void CountLabelView::addMenus()
{
    QStringList menuNames;
    menuNames << "添加标签";
    for (int i = 0; i < menuNames.count(); i++)
    {
        if (menuNames[i] == "添加标签")
        {
            addAction(m_addAction);
        }
        else
        {
            QAction* act = new QAction(this);
            act->setText(menuNames[i]);
            addAction(act);
        }

    }
}

void CountLabelView::loadCountLabel(QString caption, QString uuid)
{
    CountLabelItem* item = new CountLabelItem(this);
    item->setCaption(caption);
    item->setUuid(uuid);
    item->setValue("0");
    m_items << item;
}

void CountLabelView::updateValues()
{
    for (int i = 0; i < m_items.count(); i++)
    {
        CountLabelItem* item = m_items.at(i);
        emit updateCountLabelValue(item);
    }
    update();
}

void CountLabelView::onAddActionTriggered()
{

    QString s;
    bool ret = setValue("添加标签", "标签", s);
    if (ret)
    {
        CountLabelItem* item = new CountLabelItem(this);
        item->setCaption(s);
        item->setValue("0");
        m_items << item;
        emit addCountLabel(item);
        emit updateCountLabelValue(item);
        update();

    }
}

void CountLabelView::paintEvent(QPaintEvent* event)
{

    QRect clientRc = m_helper->clientRect();
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    painter.fillRect(clientRc, QBrush(Qt::white));

    int t = m_helper->itemsTop();
    int l = 16;
    for (int i = 0; i < m_items.count(); i++)
    {

        CountLabelItem* item = m_items.at(i);
        QFontMetrics fm = painter.fontMetrics();
        int w = fm.width(item->caption() + item->value()) + 64;
        int w1 = fm.width(item->caption()) + 32;
        int w2 = fm.width(item->value()) + 32;
        int h = fm.height() + 16;

        if ((l + w) > width())
        {
            l = 16;
            t += h + 16;
        }



        painter.setPen(Qt::NoPen);
        QRect rc1 = QRect(l, t, w1, h);
        painter.setBrush(item->backgroundColor());
        painter.drawRoundedRect(rc1, 4, 4);
        QRect rc1r = QRect(l + w1 - 4, t, 4, h);
        painter.drawRect(rc1r);




        QRect rc2 = QRect(l + w1, t, w2, h);
        painter.setBrush(item->backgroundColor().darker());
        painter.drawRoundedRect(rc2, 4, 4);

        QRect rc2l = QRect(l + w1, t, 4, h);
        painter.drawRect(rc2l);


        painter.setPen(Qt::white);
        painter.drawText(rc1, Qt::AlignCenter, item->caption());
        painter.drawText(rc2, Qt::AlignCenter, item->value());

        item->setRect(QRect(l, t, w, h));

        l += w;
        l += 16;



    }

    painter.end();



}

void CountLabelView::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_items.count(); i++)
    {
        CountLabelItem* item = m_items.at(i);
        if (item->rect().contains(curPt))
        {
            emit clickLabel(item);
        }
    }
}
