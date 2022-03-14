#include "reportdesignwindow.h"
#include "ui_reportdesignwindow.h"

ReportDesignWindow::ReportDesignWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::ReportDesignWindow)
{
    ui->setupUi(this);
    m_view = new ReportDesignView(ui->wgtClient);
    addWidgetToPage(ui->wgtClient, m_view);
}

ReportDesignWindow::~ReportDesignWindow()
{
    delete ui;
}

void showReportDesignWindow(QWidget* parent)
{
    ReportDesignWindow* w = new ReportDesignWindow(parent);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->showMaximized();
}

void ReportDesignWindow::on_btnAdd_clicked()
{
    m_view->setOperation(OP_ADD_OBJECT);
}


void ReportDesignWindow::on_btnSelect_clicked()
{
    m_view->deselectAll();
    m_view->setOperation(OP_SELECT);
}


void ReportDesignWindow::on_btnDelete_clicked()
{
    m_view->deleteSelectCells();

}


void ReportDesignWindow::on_btnDeSelectAll_clicked()
{
    m_view->deselectAll();
}


void ReportDesignWindow::on_btnHorTile_clicked()
{
    m_view->setSelectCellsHorTile();
}


void ReportDesignWindow::on_btnCopySelectCells_clicked()
{
    m_view->copySelectCells();
}


void ReportDesignWindow::on_btnPasteUnder_clicked()
{
    m_view->setOperation(OP_PASTE_SELECT_OBJECTS);
}


void ReportDesignWindow::on_btnVerTile_clicked()
{
    m_view->setSelectCellsVerTile();
}


void ReportDesignWindow::on_btnSaveAs_clicked()
{
    QString path = QFileDialog::getSaveFileName();
    if (path == "")
    {
        return;
    }
    m_view->saveToFile(path);
}


void ReportDesignWindow::on_btnOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if (path == "")
    {
        return;
    }
    m_view->loadFromFile(path);
}


void ReportDesignWindow::on_btnRemoveBorder_clicked()
{
    m_view->processSelectCells([](ReportCell * cell)
    {
        cell->setDrawLeft(false);
        cell->setDrawTop(false);
        cell->setDrawRight(false);
        cell->setDrawBottom(false);
    });
}


void ReportDesignWindow::on_btnAddBorder_clicked()
{
    m_view->processSelectCells([](ReportCell * cell)
    {
        cell->setDrawLeft(true);
        cell->setDrawTop(true);
        cell->setDrawRight(true);
        cell->setDrawBottom(true);
    });
}


void ReportDesignWindow::on_btnProperty_clicked()
{
    ReportCell* cell = m_view->getFirstSelectCell();
    m_view->showCellPropertyDialog(cell);

}


void ReportDesignWindow::on_btnFitToMaxHeight_clicked()
{
    m_view->fitToMaxHeight();
}


void ReportDesignWindow::on_btnCalValues_clicked()
{
    QString s = QString("选中对象总长度:%1").arg(m_view->calSelectCellsSumWidth());
    QMessageBox::information(this, "计算结果", s);
}


void ReportDesignWindow::on_btnSetResizeCellHeight_clicked()
{
    m_view->resetSelectCellsHeightByFactor(0.5);
}

