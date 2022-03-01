#ifndef QRCODEWIDGET_H
#define QRCODEWIDGET_H

#include "qrencode.h"
#include <QList>
#include <QPainter>
#include <QWidget>

struct QRCodeBlock {
    int x;
    int y;
    int data;
};

class QRCodeWidget : public QWidget {
    Q_OBJECT

public:
    explicit QRCodeWidget(QWidget* parent = nullptr);
    ~QRCodeWidget();

    QString qrcode() const;
    void setQrcode(const QString& qrcode);

    int qrcodeVersion() const;
    void setQrcodeVersion(int qrcodeVersion);

protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);

private:
    QString m_qrcode;
    int m_qrcodeWidth;
    int m_qrcodeVersion;
    QList<QRCodeBlock> m_blocks;
};

#endif // QRCODEWIDGET_H
