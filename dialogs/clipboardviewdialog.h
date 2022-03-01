#ifndef CLIPBOARDVIEWDIALOG_H
#define CLIPBOARDVIEWDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>
#include "../controls/pixmapviewer.h"
#include <QClipboard>
#include <QApplication>
#include <QMimeData>

namespace Ui
{
class ClipBoardViewDialog;
}

class ClipBoardViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClipBoardViewDialog(QWidget* parent = nullptr);
    ~ClipBoardViewDialog();

private slots:
    void on_btnOk_clicked();

private:
    Ui::ClipBoardViewDialog* ui;
    QPlainTextEdit* m_textView;
    PixmapViewer* m_pixView;
};
void showClipBoardViewer();

#endif // CLIPBOARDVIEWDIALOG_H
