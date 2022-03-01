#ifndef SEARCHEDIT_H
#define SEARCHEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QInputMethodEvent>

class SearchEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SearchEdit(QWidget* parent = nullptr);

    const QStringList& suggestStrings() const;
    void setSuggestStrings(const QStringList& newSuggestStrings);
signals:
    void selectSuggestString(const QString& s);
protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void inputMethodEvent(QInputMethodEvent* event) override;

signals:
private:
    QStringList m_suggestStrings;
    QString m_suggestString;
    QStringList m_selStrings;
    int m_selStringIndex;
    QString getSuggestString();
};

#endif // SEARCHEDIT_H
