#ifndef ORDEREDMAP_H
#define ORDEREDMAP_H
#include <QList>
#include <QMap>
template<typename T1, typename T2>
class OrderedMap
{
public:
    OrderedMap()
    {

    }
    void addValue(T1 t1, T2 t2)
    {
        m_list.append(t1);
        m_map.insert(t1, t2);
    }
    void setValue(T1 t1, T2 t2)
    {
        m_map[t1] = t2;
    }
    void getkeyValue(int i, T1& t1, T2& t2)
    {
        t1 = m_list.at(i);
        t2 = m_map[t1];
    }
    T1 getKey(int i)
    {
        T1 t1 = m_list.at(i);
        return t1;
    }
    T2 getValue(int i)
    {
        T1 t1 = m_list.at(i);
        return m_map[t1];
    }
    int count()
    {
        return m_list.count();
    }
private:
    QList<T1> m_list;
    QMap<T1, T2> m_map;
};

#endif // ORDEREDMAP_H
