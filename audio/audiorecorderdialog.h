#ifndef AUDIORECORDERDIALOG_H
#define AUDIORECORDERDIALOG_H

#include <QDialog>
#include <QFile>
#include <QApplication>
#include <QAudioRecorder>
#include <QDebug>
#include <QUrl>
#include <QTimer>
#include "src/api/algo/fndatetime.h"
#include <QDateTime>



namespace Ui
{
class AudioRecorderDialog;
}

class AudioRecorderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AudioRecorderDialog(QWidget* parent = nullptr);
    ~AudioRecorderDialog();
    qint64 addWavHeader(QString catheFileName, QString wavFileName);

    QString path() const;
    void setPath(const QString& path);

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked(bool checked);
    void onTimeOut();
private:
    Ui::AudioRecorderDialog* ui;
    QString m_path;
    QString m_fileName;
    int m_start;
    QAudioRecorder* m_recorder;
    QTimer* m_tmr;
};
bool showAudioRecorderDialog(QString& path);

#endif // AUDIORECORDERDIALOG_H
