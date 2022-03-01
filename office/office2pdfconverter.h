#ifndef OFFICE2PDFCONVERTER_H
#define OFFICE2PDFCONVERTER_H

#include <QObject>
#include <QAxWidget>
#include <QAxObject>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>

class Office2PdfConverter : public QObject
{
    Q_OBJECT
public:
    explicit Office2PdfConverter(QObject* parent = nullptr);

    QString srcPath() const;
    void setSrcPath(const QString& srcPath);

    QString destPath() const;
    void setDestPath(const QString& destPath);
    void convert();

    bool showOffice() const;
    void setShowOffice(bool showOffice);
    void taskkill();

    bool skipExist() const;
    void setSkipExist(bool skipExist);

signals:
private:
    QString m_srcPath;
    QString m_destPath;
    QString m_suffix;
    bool m_showOffice;
    bool m_skipExist;


};

#endif // OFFICE2PDFCONVERTER_H
