#include "searchedit.h"

SearchEdit::SearchEdit(QWidget* parent) : QLineEdit(parent)
{

}

void SearchEdit::paintEvent(QPaintEvent* event)
{

    QLineEdit::paintEvent(event);

    if (m_suggestString != "")
    {
        QString s = m_suggestString;
        QPainter painter;
        painter.begin(this);
        QFontMetrics fm = painter.fontMetrics();
        int w = fm.width(text());
        QRect rc(3 + w, 0, width() - w - 3, height());
        painter.setPen(Qt::lightGray);
        QString s1 = s.mid(text().length());

        painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, s1);

        if (m_selStrings.count() > 1)
        {
            QString numInfo = QString("%1/%2").arg(m_selStringIndex + 1).arg(m_selStrings.count());
            QRect numRc(width() - 100, 0, 97, height());
            painter.drawText(numRc, Qt::AlignRight | Qt::AlignVCenter, numInfo);

        }
        painter.end();
    }


}

void SearchEdit::keyPressEvent(QKeyEvent* event)
{
    QLineEdit::keyPressEvent(event);

    if (event->key() == Qt::Key_Return)
    {
        if (m_suggestString != "")
        {
            setText(m_suggestString);
            emit selectSuggestString(m_suggestString);
        }
    }
    else if (event->key() == Qt::Key_Backspace)
    {
        qDebug() << "back";
        m_suggestString = getSuggestString();
        update();
    }
    else if (event->key() == Qt::Key_Down)
    {
        if (m_selStrings.count() == 0)
        {
            return;
        }
        int n = m_selStringIndex + 1;

        if (n <= (m_selStrings.count() - 1))
        {
            m_selStringIndex++;
            m_suggestString = m_selStrings[m_selStringIndex];
            update();
        }
    }
    else if (event->key() == Qt::Key_Up)
    {
        if (m_selStrings.count() == 0)
        {
            return;
        }
        int n = m_selStringIndex - 1;

        if (n >= 0)
        {
            m_selStringIndex--;
            m_suggestString = m_selStrings[m_selStringIndex];
            update();
        }
    }
}

void SearchEdit::inputMethodEvent(QInputMethodEvent* event)
{
    QLineEdit::inputMethodEvent(event);
    m_suggestString = getSuggestString();
}



QString SearchEdit::getSuggestString()
{
    QString ret = "";
    if (text() == "")
    {
        return ret;
    }
    m_selStrings.clear();
    for (const QString& s : qAsConst(m_suggestStrings))
    {
        if (s.startsWith(text()))
        {
            m_selStrings << s;

        }
    }
    if (m_selStrings.count() > 0)
    {
        ret = m_selStrings[0];
        m_selStringIndex = 0;
    }
    return ret;

}

const QStringList& SearchEdit::suggestStrings() const
{
    return m_suggestStrings;
}

void SearchEdit::setSuggestStrings(const QStringList& newSuggestStrings)
{
    m_suggestStrings = newSuggestStrings;
}
