#ifndef RINGLIST_H
#define RINGLIST_H

#include <QObject>
#include <QWidget>
#include <QList>
template<typename T>
class RingList: public QList<T>
{
public:
    inline T next()
    {
        if ((m_currentIndex + 1) <= (this->count() - 1))
        {
            m_currentIndex++;
        }
        else
        {
            m_currentIndex = 0;
        }
        return this->at(m_currentIndex);
    }
    inline T prev()
    {
        if ((m_currentIndex - 1) >= 0)
        {
            m_currentIndex--;
        }
        else
        {
            m_currentIndex = this->count() - 1;
        }
        return this->at(m_currentIndex);
    }
    inline void reset()
    {
        m_currentIndex = -1;
    }


    inline int currentIndex() const
    {
        return m_currentIndex;
    }
    void setCurrentIndex(int newCurrentIndex)
    {
        m_currentIndex = newCurrentIndex;
    }

private:
    int m_currentIndex = -1;

};

#endif // RINGLIST_H
