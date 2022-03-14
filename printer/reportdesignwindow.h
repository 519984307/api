#ifndef REPORTDESIGNWINDOW_H
#define REPORTDESIGNWINDOW_H

#include <QMainWindow>
#include "reportdesignview.h"
#include <QFileDialog>
#include <QMessageBox>

namespace Ui
{
class ReportDesignWindow;
}

class ReportDesignWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReportDesignWindow(QWidget* parent = nullptr);
    ~ReportDesignWindow();

private slots:
    void on_btnAdd_clicked();

    void on_btnSelect_clicked();

    void on_btnDelete_clicked();

    void on_btnDeSelectAll_clicked();

    void on_btnHorTile_clicked();

    void on_btnCopySelectCells_clicked();

    void on_btnPasteUnder_clicked();

    void on_btnVerTile_clicked();

    void on_btnSaveAs_clicked();

    void on_btnOpen_clicked();

    void on_btnRemoveBorder_clicked();

    void on_btnAddBorder_clicked();

    void on_btnProperty_clicked();

    void on_btnFitToMaxHeight_clicked();

    void on_btnCalValues_clicked();

    void on_btnSetResizeCellHeight_clicked();

private:
    Ui::ReportDesignWindow* ui;
    ReportDesignView* m_view;
};
void showReportDesignWindow(QWidget* parent = nullptr);

#endif // REPORTDESIGNWINDOW_H
