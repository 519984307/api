#include "textpreviewer.h"
#include "ui_textpreviewer.h"

TextPreViewer::TextPreViewer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::TextPreViewer)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(16);
    m_helper->setMaxTop(16);
    m_fontSize = 16;
    m_firstLineAsTitle = true;
    setMouseTracking(true);
    this->setAttribute(Qt::WA_AcceptTouchEvents);
}

TextPreViewer::~TextPreViewer()
{
    delete ui;
}





void TextPreViewer::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter;
    painter.begin(this);
    QRect clientRc = m_helper->clientRect();
    painter.fillRect(clientRc, QBrush(Qt::white));


    int t = m_helper->itemsTop();
    for (int i = 0; i < m_lines.count(); i++)
    {
        DrawTextItem* item = m_lines.at(i);
        QString text = item->text();
        QFont font = painter.font();
        font.setPixelSize(m_fontSize);
        if (m_firstLineAsTitle)
        {
            font.setBold(i == 0);

        }
        else
        {
            font.setBold(false);
        }
        painter.setFont(font);
        QFontMetrics fm = painter.fontMetrics();
        QRect rc(m_fontSize, t - 1, fm.width(text) + m_fontSize * 2, fm.height() + 2);


        if ((m_firstLineAsTitle) && (i == 0))
        {
            rc = QRect((width() - rc.width()) / 2, rc.top(), rc.width(), rc.height());



        }
        else
        {


        }
        item->setRect(rc);
        QPen pen = painter.pen();
        pen.setColor(item->textColor());
        painter.setPen(pen);
        painter.drawText(rc, Qt::AlignCenter, text);
        t += fm.height() + m_fontSize / 2;
    }

    painter.end();
}

void TextPreViewer::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    if (qApp->keyboardModifiers() == Qt::ControlModifier)
    {
        if (y > 0)
        {
            m_fontSize += 2;
        }
        else
        {
            m_fontSize -= 2;
            if (m_fontSize < 8)
            {
                m_fontSize = 8;
            }
        }
        update();
    }
    else
    {
        m_helper->moveTop(y);
    }
}

void TextPreViewer::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_lines.count(); i++)
    {
        DrawTextItem* item = m_lines.at(i);
        if (item->rect().contains(curPt))
        {
            emit clickItem(item);
            break;
        }
    }
    m_helper->startMouseDown();
}

void TextPreViewer::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    m_helper->startMouseUp();
}

void TextPreViewer::mouseMoveEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    if (m_helper->mousedownFlag())
    {
        QPoint pt = m_helper->cursorPos();
        int y = pt.y() - m_helper->mouseMovePoint().y();
        m_helper->moveTop(y);
        m_helper->setMouseMovePoint(pt);
    }
}

void TextPreViewer::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_lines.count(); i++)
    {
        DrawTextItem* item = m_lines.at(i);
        if (item->rect().contains(curPt))
        {
            emit doubleClickItem(item);
            break;
        }
    }
    update();
}

bool TextPreViewer::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::TouchBegin:
    {

        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        QList<QTouchEvent::TouchPoint> points = touchEvent->touchPoints();
        if (points.count() == 2)
        {
            m_helper->setStartTouchPoint0(points.at(0).screenPos().toPoint());
            m_helper->setStartTouchPoint1(points.at(1).screenPos().toPoint());
            m_helper->startTouch();
        }
        return true;
    }
    case QEvent::TouchUpdate:
    {
        qDebug() << "CProjectionPicture::event";
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        if (touchPoints.count() == 2)
        {
            m_helper->setIsTwoPoint(true);//两指时不让移动
            const QTouchEvent::TouchPoint& touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint& touchPoint1 = touchPoints.last();
            m_touchLen1 = QLineF(touchPoint0.screenPos().toPoint(), touchPoint1.screenPos().toPoint()).length();
            m_touchLen2 = QLineF(touchPoint0.lastScreenPos().toPoint(), touchPoint1.lastScreenPos().toPoint()).length();
            bool f = m_touchLen1 > m_touchLen2  ? true : false;


            if (touchEvent->touchPointStates() & Qt::TouchPointMoved)
            {

                if (f == true)
                {
                    m_fontSize += 1;
                    if (m_fontSize > 32)
                    {
                        m_fontSize = 32;
                    }
                }
                else
                {
                    m_fontSize -= 1;
                    if (m_fontSize < 8)
                    {
                        m_fontSize = 8;
                    }
                }
                m_helper->setStartTouchPoint0(touchPoint0.screenPos().toPoint());
                m_helper->setStartTouchPoint1(touchPoint1.screenPos().toPoint());
            }

            update();
        }
        else if (touchPoints.count() == 1)
        {


            m_helper->setIsTwoPoint(false);//两指时不让移动
            const QTouchEvent::TouchPoint& touchPoint = touchPoints.first();

            QPoint curPt = touchPoint.screenPos().toPoint();
            QPoint oldPt = touchPoint.lastScreenPos().toPoint();
            int d = curPt.y() - oldPt.y();



            if (touchEvent->touchPointStates() & Qt::TouchPointMoved)
            {

                m_helper->moveTop(d);
            }





            update();
        }
        return true;
    }
    case QEvent::TouchEnd:
    {
        m_helper->endTouch();
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        if (touchPoints.count() == 1)
        {
            const QTouchEvent::TouchPoint& touchPoint = touchPoints.first();

            QPoint curPt = touchPoint.pos().toPoint();
            for (int i = 0; i < m_lines.count(); i++)
            {
                DrawTextItem* item = m_lines.at(i);
                if (item->rect().contains(curPt))
                {
                    emit clickItem(item);
                    break;
                }
            }
        }


        return true;
    }

    default:
        break;
    }

    return QWidget::event(event);


}

const QList<DrawTextItem*>& TextPreViewer::lines() const
{
    return m_lines;
}

void TextPreViewer::setLines(const QList<DrawTextItem*>& newLines)
{
    m_lines = newLines;
}

void TextPreViewer::loadLines(QStringList& lines)
{
    qDeleteAll(m_lines);
    m_lines.clear();
    for (int i = 0; i < lines.count(); i++)
    {
        DrawTextItem* item = new DrawTextItem(this);
        item->setText(lines[i]);
        m_lines << item;
    }
    m_helper->setItemsTop(m_fontSize);
    update();

}





int TextPreViewer::fontSize() const
{
    return m_fontSize;
}

void TextPreViewer::setFontSize(int newFontSize)
{
    m_fontSize = newFontSize;
}
