#include "qrcodewidget.h"

QRCodeWidget::QRCodeWidget(QWidget* parent)
    : QWidget(parent)

{
    m_qrcodeVersion = 2;
}

QRCodeWidget::~QRCodeWidget()
{
}

void QRCodeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    int qrcodeWidth = width() < height() ? width() : height();
    qrcodeWidth = qrcodeWidth - 4;
    int blockWidth = qrcodeWidth / m_qrcodeWidth;
    int qrcodeTop = (height() - qrcodeWidth) / 2;
    int qrcodeLeft = (width() - qrcodeWidth) / 2;
    for (int i = 0; i < m_blocks.count(); i++) {
        QRCodeBlock block = m_blocks.at(i);
        QRect rc = QRect(block.x * blockWidth + qrcodeLeft, block.y * blockWidth + qrcodeTop, blockWidth, blockWidth);
        if (block.data == 1) {
            painter.fillRect(rc, Qt::black);
        } else {
            painter.fillRect(rc, Qt::white);
        }
    }
    painter.end();
}

void QRCodeWidget::resizeEvent(QResizeEvent* event)
{
    update();
}

int QRCodeWidget::qrcodeVersion() const
{
    return m_qrcodeVersion;
}

void QRCodeWidget::setQrcodeVersion(int qrcodeVersion)
{
    m_qrcodeVersion = qrcodeVersion;
}

QString QRCodeWidget::qrcode() const
{
    return m_qrcode;
}

void QRCodeWidget::setQrcode(const QString& qrcode)
{
    m_qrcode = qrcode;
    QRcode* code;

    code = QRcode_encodeString(qrcode.toLocal8Bit().data(), m_qrcodeVersion, QR_ECLEVEL_L, QR_MODE_8, 0);
    m_blocks.clear();
    m_qrcodeWidth = code->width;
    for (int i = 0; i < code->width; i++) {
        QString s = "";
        for (int j = 0; j < code->width; j++) {
            QRCodeBlock block;
            block.x = j;
            block.y = i;

            if (code->data[i * 25 + j] & 0x01) {
                block.data = 1;

            } else {
                block.data = 0;
            }
            m_blocks << block;
        }
    }
    delete code;
    update();
}
