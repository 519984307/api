#ifndef DATACATEGORY_H
#define DATACATEGORY_H

#include <QDebug>
#include <QListWidgetItem>
#include <QPainter>
#include <QWidget>

namespace Ui {
class DataCateGory;
}
struct DataCateGoryItem {
    int id;
    QString name;
};

class DataCateGory : public QWidget {
    Q_OBJECT

public:
    explicit DataCateGory(QWidget* parent = nullptr);
    ~DataCateGory();

    QString caption() const;
    void setCaption(const QString& caption);
    QListWidgetItem* item() const;
    void setItem(QListWidgetItem* item);

    QListWidget* listWidget() const;
    void setListWidget(QListWidget* listWidget);

    int id() const;
    void setId(int id);

signals:
    void onClick();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::DataCateGory* ui;
    QString m_caption;
    QString m_remark;
    QString m_number;
    bool m_showNumber;
    QListWidgetItem* m_item;
    QListWidget* m_listWidget;
    int m_id;
};
DataCateGoryItem newDataCateGoryItem(int id, QString name);
#endif // DATACATEGORY_H
