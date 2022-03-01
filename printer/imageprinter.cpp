#include "imageprinter.h"


ImagePrinter::ImagePrinter(QObject* parent) : QObject(parent)
{


}

const QStringList& ImagePrinter::printFiles() const
{
    return m_printFiles;
}

void ImagePrinter::setPrintFiles(const QStringList& newPrintFiles)
{
    m_printFiles = newPrintFiles;
}

void ImagePrinter::loadFromFolder(QString folderPath)
{
    QDir dir(folderPath);
    QFileInfoList fileInfos = dir.entryInfoList();
    for (const QFileInfo& info : qAsConst(fileInfos))
    {
        if (info.suffix().toLower() == "jpg")
        {
            m_printFiles << info.absoluteFilePath();
        }
    }
}

void ImagePrinter::print()
{
    QPrinter printer(QPrinter::HighResolution);
    QPainter painter;
    painter.begin(&printer);
    for (int i = 0; i < m_printFiles.count(); i++)
    {

        QRect pageRect = painter.viewport();
        QPixmap pix(m_printFiles[i]);


        QPixmap printPix = pix;
        double f1 = pageRect.width();
        f1 = f1 / pageRect.height();
        double f2 = pix.width();
        f2 = f2 / pix.height();

        if (f1 > f2)
        {
            printPix = printPix.scaledToHeight(pageRect.height());
            pageRect = QRect((pageRect.width() - printPix.width()) / 2, 0, printPix.width(), printPix.height());
        }
        else
        {
            printPix = printPix.scaledToWidth(pageRect.width());
            pageRect = QRect(0, (pageRect.height() - printPix.height()) / 2, printPix.width(), printPix.height());

        }

        painter.drawPixmap(pageRect, printPix, printPix.rect());
        if (i != (m_printFiles.count() - 1))
        {
            printer.newPage();
        }
        QApplication::processEvents();

    }

    painter.end();

}
