#ifndef MAP3DOBJECTPROPERTYDIALOG_H
#define MAP3DOBJECTPROPERTYDIALOG_H

#include <QDialog>
#include "map3dobject.h"
#include <QColorDialog>
class Map3dObject;
namespace Ui
{
class Map3dObjectPropertyDialog;
}

class Map3dObjectPropertyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Map3dObjectPropertyDialog(QWidget* parent = nullptr);
    ~Map3dObjectPropertyDialog();

    Map3dObject* map3dObject() const;
    void setMap3dObject(Map3dObject* newMap3dObject);

private slots:
    void on_btnColor_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::Map3dObjectPropertyDialog* ui;
    Map3dObject* m_map3dObject;
    QColor m_color;
};
void showMap3dObjectPropertyDialog(Map3dObject* obj);

#endif // MAP3DOBJECTPROPERTYDIALOG_H
