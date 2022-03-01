#ifndef CACHELIST_H
#define CACHELIST_H

#include <QObject>
#include <QList>
#include <QDebug>


template<typename T>
class CacheList : public QList<T>
{
public:
    CacheList<T>()
    {
        m_maxCacheNum = 10000;
    }



    inline int maxCacheNum()
    {
        return m_maxCacheNum;
    }
    inline void setMaxCacheNum(int newMaxCacheNum)
    {
        m_maxCacheNum = newMaxCacheNum;
    }

    inline void addValue(T t, void (*func)(T t1) = nullptr)
    {
        if (this->length() == m_maxCacheNum)
        {

            T tmp = this->at(0);
            this->removeAt(0);
            if (func != nullptr)
            {
                func(tmp);
            }
        }
        this->append(t);


    }

    inline void addObject(T t)
    {
        if (this->length() == m_maxCacheNum)
        {

            T tmp = this->at(0);
            this->removeAt(0);
            delete tmp;
        }
        this->append(t);


    }




private:
    int m_maxCacheNum = 100;


};

#endif // CACHELIST_H
