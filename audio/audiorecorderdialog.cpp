#include "audiorecorderdialog.h"
#include "ui_audiorecorderdialog.h"

AudioRecorderDialog::AudioRecorderDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AudioRecorderDialog)
{
    ui->setupUi(this);
    m_recorder = new QAudioRecorder(this);
    ui->cbbDev->addItems(m_recorder->audioInputs());
    m_tmr = new QTimer(this);
    connect(m_tmr, &QTimer::timeout, this, &AudioRecorderDialog::onTimeOut);
    m_start = 0;
    QDateTime d = QDateTime::currentDateTime();
    m_fileName = QApplication::applicationDirPath() + "/data/audios/" + d.toString("yyyyMMddhhmmss");
    m_path = m_fileName + ".wav";
}

AudioRecorderDialog::~AudioRecorderDialog()
{
    delete ui;
}

bool showAudioRecorderDialog(QString& path)
{
    AudioRecorderDialog* dlg = new AudioRecorderDialog();
    bool f;
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        f = true;
        path = dlg->path();
    }
    else
    {
        f = false;
        path = "";
    }
    delete dlg;
    return f;
}

void AudioRecorderDialog::on_btnOk_clicked()
{
    if (ui->btnOk->text() == "开始录制")
    {
        QAudioEncoderSettings audioSettings;
        qDebug() << audioSettings.codec();
        audioSettings.setCodec("audio/amr");
        audioSettings.setQuality(QMultimedia::HighQuality);
        m_recorder->setAudioInput(ui->cbbDev->currentText());
        m_recorder->setEncodingSettings(audioSettings);

        m_recorder->setOutputLocation(QUrl::fromLocalFile(m_fileName));
        m_recorder->record();
        m_tmr->start(1000);
        ui->btnOk->setText("停止录制");
    }
    else
    {
        m_recorder->stop();
        accept();
    }
}


void AudioRecorderDialog::on_btnCancel_clicked(bool checked)
{
    m_recorder->stop();
    reject();
}

void AudioRecorderDialog::onTimeOut()
{
    m_start++;
    ui->lblTime->setText(secondToString(m_start));


}

QString AudioRecorderDialog::path() const
{
    return m_path;
}

void AudioRecorderDialog::setPath(const QString& path)
{
    m_path = path;
}
