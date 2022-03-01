#include "colortable.h"
ColorTable* ColorTable::m_instance = nullptr;
int ColorTable::fontColorIndex = 0;
int ColorTable::backColorIndex = ColorTable::lastIndex();
QStack<int> ColorTable::colorIndexes;
ColorTable::ColorTable(QObject* parent)
    : QObject(parent)
{

    int n = 0;
    int values[5] = { 0, 64, 128, 192, 255 };
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                m_colors << QColor(values[i], values[j], values[k]);
                n++;
            }
        }
    }
}

QList<QColor>& ColorTable::colors()
{
    return m_colors;
}

ColorTable* ColorTable::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new ColorTable();
    }
    return m_instance;
}

void ColorTable::freeColorTable()
{
    if (m_instance != nullptr)
    {
        delete m_instance;
    }
}

QColor ColorTable::getColor(int i)
{
    if (i == -1)
    {
        i = 0;
    }
    return getInstance()->colors().at(i);
}

void ColorTable::addColorIndex(int i)
{
    if (!colorIndexes.contains(i))
    {
        colorIndexes.push(i);
    }
}

int ColorTable::lastIndex()
{
    static int ret = getInstance()->colors().count() - 1;
    return ret;
}

QColor ColorTable::getRandomColor()
{
    static QColor colors[12] = { QColor(229, 77, 66), QColor(243, 123, 29), QColor(251, 189, 8),
                                 QColor(141, 198, 63), QColor(57, 181, 74), QColor(28, 187, 180), QColor(0, 129, 255),
                                 QColor(103, 57, 182), QColor(156, 38, 176), QColor(224, 57, 151), QColor(165, 103, 63), QColor(135, 153, 163)
                               };
    int i = QRandomGenerator::global()->bounded(0, 11);
    return colors[i];
}
