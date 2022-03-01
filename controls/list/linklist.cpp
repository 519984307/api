#include "linklist.h"
#include "ui_linklist.h"

LinkList::LinkList(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LinkList)
{
    ui->setupUi(this);
    m_linkWidth = 256;
    m_linkHeight = 32;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setMaxTop(16);
    m_helper->setItemsTop(16);
    setMouseTracking(true);
    m_selLink = nullptr;
    addDefaultMenu();

}

LinkList::~LinkList()
{
    delete ui;
}

int LinkList::linkWidth() const
{
    return m_linkWidth;
}

void LinkList::setLinkWidth(int newLinkWidth)
{
    m_linkWidth = newLinkWidth;
}

int LinkList::linkHeight() const
{
    return m_linkHeight;
}

void LinkList::setLinkHeight(int newLinkHeight)
{
    m_linkHeight = newLinkHeight;
}

void LinkList::clearLinks()
{
    qDeleteAll(m_linkInfos);
    m_linkInfos.clear();
    m_helper->setItemsTop(16);
    m_selLink = nullptr;
    update();
}

LinkInfo* LinkList::addLink(QString name, QString url)
{
    LinkInfo* link = new LinkInfo(this);
    link->setName(name);
    link->setUrl(url);
    m_linkInfos << link;
    update();
    return link;
}

void LinkList::addDefaultMenu()
{
    QStringList menuNames;
    menuNames << "复制内容";

    for (int i = 0; i < menuNames.count(); i++)
    {
        QAction* act = new QAction(this);
        act->setText(menuNames[i]);
        connect(act, &QAction::triggered, this, &LinkList::onMenuTriggered);
        addAction(act);

    }

}

void LinkList::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QRect clientRc = m_helper->clientRect();
    QPoint curPt = m_helper->cursorPos();
    painter.fillRect(clientRc, QBrush(Qt::white));
    int t = m_helper->itemsTop();
    int l = 16;
    for (int i = 0; i < m_linkInfos.count(); i++)
    {
        LinkInfo* link = m_linkInfos.at(i);
        QRect rc(l, t, m_linkWidth, m_linkHeight);
        link->setRect(rc);
        if (clientRc.contains(rc))
        {
            if (rc.contains(curPt))
            {
                painter.fillRect(rc, QBrush(QColor(223, 223, 223)));


            }

            QFont font = painter.font();
            font.setPixelSize(16);
            painter.setFont(font);
            QRect textRc = QRect(rc.left() + 6, rc.top(), rc.width() - 12, rc.height());

            QTextOption op;
            op.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            op.setWrapMode(QTextOption::NoWrap);

            QFontMetrics fm = painter.fontMetrics();
            QString showTxt = link->name().trimmed();
            if (fm.boundingRect(showTxt).width() > textRc.width())
            {
                showTxt = fm.elidedText(showTxt, Qt::ElideRight, textRc.width());
            }


            painter.drawText(textRc, showTxt, op);


        }
        if ((l + m_linkWidth * 2 + 32) > width())
        {
            l = 16;
            t += m_linkHeight + 16;
        }
        else
        {
            l += m_linkWidth + 32;
        }


        if (t > (height() + 128))
        {
            break;
        }

    }
    painter.end();
}

void LinkList::mousePressEvent(QMouseEvent* event)
{
    m_selLink = nullptr;
    QPoint curPt = m_helper->cursorPos();

    for (LinkInfo* link : m_linkInfos)
    {
        if (link->rect().contains(curPt))
        {
            if (event->button() == Qt::LeftButton)
            {
                emit clickLink(link);
            }
            m_selLink = link;
            break;
        }
    }



}

void LinkList::mouseMoveEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    QPoint gPt = cursor().pos();
    for (LinkInfo* link : m_linkInfos)
    {
        if (link->rect().contains(curPt))
        {
            QToolTip::showText(gPt, link->name() + "\n" + link->url()
                               + "\n" + link->createDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            break;
        }
    }
    update();

}

void LinkList::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    m_helper->moveTop(y);
    update();
}

void LinkList::onMenuTriggered()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "复制内容")
    {
        if (m_selLink != nullptr)
        {
            qApp->clipboard()->setText(m_selLink->name());
        }

    }

}
