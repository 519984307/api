#ifndef COLORTABLE_H
#define COLORTABLE_H

#include <QColor>
#include <QObject>
#include <QSet>
#include <QStack>
#include <QtDebug>
#include <QRandomGenerator>

class ColorTable : public QObject
{
    Q_OBJECT
public:
    QList<QColor>& colors();
    static ColorTable* getInstance();
    static void freeColorTable();
    static QColor getColor(int i);
    static int fontColorIndex;
    static int backColorIndex;
    static QStack<int> colorIndexes;
    static void addColorIndex(int i);
    static int lastIndex();
    static QColor getRandomColor();

private:
    explicit ColorTable(QObject* parent = nullptr);
    QList<QColor> m_colors;
    static ColorTable* m_instance;
signals:

public slots:
};

#endif // COLORTABLE_H
