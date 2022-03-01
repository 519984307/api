#include "parentimageviewer.h"

ParentImageViewer::ParentImageViewer(QWidget* parent) : QWidget(parent)
{
    setMouseTracking(true);
    m_isEncryptionMode = false;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(16);
    m_maxImgSize = 8192;
    m_backGroundColor = Qt::white;
    m_columnCount = 5;
    m_isShowPopuMenu = true;
    setMouseTracking(true);

}
void ParentImageViewer::appendFile(QString filePath)
{
    QFileInfo info(filePath);
    ImageObject* cell = new ImageObject(this);
    cell->setPath(info.absoluteFilePath());
    cell->setFolderPath(info.absolutePath()) ;
    images << cell;
    recalCellIndexes();
    update();
}

void ParentImageViewer::recalCellIndexes()
{

}

int ParentImageViewer::columnCount() const
{
    return m_columnCount;
}

void ParentImageViewer::setColumnCount(int columnCount)
{
    m_columnCount = columnCount;
}
void ParentImageViewer::loadPictureFromFolder(QString path)
{
    m_currentFolderPath = path;
    QDir dir(path);
    QFileInfoList infos = dir.entryInfoList();
    images.clear();
    int i = 0;
    m_helper->setItemsTop(16);
    QSet<QString> suffixs;
    suffixs << "jpg" << "jpeg" << "png" << "ico";
    for (QFileInfo& info : infos)
    {
        if ((info.fileName() == ".") || (info.fileName() == ".."))
        {
            continue;
        }
        if (info.isDir())
        {
            continue;
        }
        QString suffix = info.suffix().toLower();
        if (!suffixs.contains(suffix))
        {
            qDebug() << info.absoluteFilePath();
            continue;
        }
        QSize imgSize;
        int imgWidth;
        int imgHeight;
        if (m_isEncryptionMode)
        {
            QString configFile = info.absoluteFilePath() + ".json";
            QFileInfo cfgInfo(configFile);
            if (cfgInfo.exists())
            {
                QFile jdocFile(configFile);
                jdocFile.open(QIODevice::ReadOnly);
                QByteArray data = jdocFile.readAll();
                QJsonDocument jdoc = QJsonDocument::fromJson(data);
                QJsonObject jobj = jdoc.object();
                imgSize = QSize(jobj["width"].toInt(), jobj["height"].toInt());
                imgWidth = imgSize.width();
                imgHeight = imgSize.height();

                jdocFile.close();

            }
            else
            {
                AesFile* file = new AesFile(nullptr);
                QPixmap pix;
                file->decryptAsPixmap(info.absoluteFilePath(), pix);

                imgSize = QSize(pix.width(), pix.height());
                imgWidth = pix.width();
                imgHeight = pix.height();

                delete file;
            }

        }
        else
        {
            QImageReader imgReader(info.absoluteFilePath());
            imgSize = imgReader.size();
            imgWidth = imgSize.width();
            imgHeight = imgSize.height();
        }


        if ((imgWidth > 0) && (imgHeight > 0))
        {
            qDebug() << info.absoluteFilePath() << imgSize << m_columnCount;


            ImageObject* cell = new ImageObject(this);
            cell->setColIndex(i % m_columnCount);
            cell->setPath(info.absoluteFilePath());
            cell->setFolderPath(path);



            cell->setPicWidth(imgWidth);
            cell->setPicHeight(imgHeight);
            double aspactRatio = imgWidth;
            aspactRatio = aspactRatio / imgHeight;
            cell->setAspectRatio(aspactRatio);
            cell->setFileName(info.fileName());
            images << cell;

            i++;

        }
        QApplication::processEvents();




    }

    update();


}

int ParentImageViewer::maxImgSize() const
{
    return m_maxImgSize;
}

void ParentImageViewer::setMaxImgSize(int maxImgSize)
{
    m_maxImgSize = maxImgSize;
}

QColor ParentImageViewer::backGroundColor() const
{
    return m_backGroundColor;
}

void ParentImageViewer::setBackGroundColor(const QColor& backGroundColor)
{
    m_backGroundColor = backGroundColor;
    update();
}

void ParentImageViewer::getScaledPixmap(QPixmap& pix, QString path)
{
    pix = QPixmap(path);
    if (pix.width() > pix.height())
    {
        if (pix.width() > m_maxImgSize)
        {
            pix = pix.scaledToWidth(m_maxImgSize, Qt::SmoothTransformation);
        }

    }
    else
    {
        if (pix.height() > m_maxImgSize)
        {
            pix = pix.scaledToWidth(m_maxImgSize, Qt::SmoothTransformation);
        }
    }

}
void ParentImageViewer::resizeEvent(QResizeEvent* event)
{

    recalCellIndexes();
    update();

}

void ParentImageViewer::reLoadPictures()
{
    for (int i = 0; i < images.count(); i++)
    {
        ImageObject* cell = images.at(i);
        cell->setHasLoad(false);

    }
}

void ParentImageViewer::loadImageToMemory()
{
    QTimer* t = new QTimer(this);
    t->setSingleShot(true);
    connect(t, &QTimer::timeout, this, [this]()
    {
        for (int i = 0; i < images.count(); i++)
        {
            ImageObject*  cell = images.at(i);
            if (cell->hasLoad() == false)
            {
                QPixmap pix;
                getScaledPixmap(pix, cell->path());

                cell->setPix(pix);
                cell->setHasLoad(true);


                QApplication::processEvents();



            }
        }
    });
    t->start(50);


}

bool ParentImageViewer::isShowPopuMenu() const
{
    return m_isShowPopuMenu;
}

void ParentImageViewer::setIsShowPopuMenu(bool newIsShowPopuMenu)
{
    m_isShowPopuMenu = newIsShowPopuMenu;
    if (m_isShowPopuMenu)
    {
        setContextMenuPolicy(Qt::ActionsContextMenu);
    }
    else
    {
        setContextMenuPolicy(Qt::NoContextMenu);
    }
}

bool ParentImageViewer::isEncryptionMode() const
{
    return m_isEncryptionMode;
}

void ParentImageViewer::setIsEncryptionMode(bool newIsEncryptionMode)
{
    m_isEncryptionMode = newIsEncryptionMode;
}
void ParentImageViewer::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    if (QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (y < 0)
        {
            m_columnCount++;
        }
        else
        {
            m_columnCount--;
            if (m_columnCount < 1)
            {
                m_columnCount = 1;
            }
        }
        recalCellIndexes();
        m_helper->setItemsTop(16);


    }
    else
    {
        int topValue = m_helper->itemsTop();
        topValue += y ;
        if (topValue > m_helper->maxTop())
        {
            topValue = m_helper->maxTop();
        }
        m_helper->setItemsTop(topValue);
    }



    update();

}

void ParentImageViewer::appendPictureFromFolder(QString path)
{
    m_currentFolderPath = path;
    QDir dir(path);
    QFileInfoList infos = dir.entryInfoList();

    int i = 0;
    m_helper->setItemsTop(16);
    QSet<QString> suffixs;
    suffixs << "jpg" << "jpeg" << "png" << "ico";
    for (QFileInfo& info : infos)
    {
        if ((info.fileName() == ".") || (info.fileName() == ".."))
        {
            continue;
        }
        if (info.isDir())
        {
            continue;
        }
        QString suffix = info.suffix().toLower();
        if (!suffixs.contains(suffix))
        {
            qDebug() << info.absoluteFilePath();
            continue;
        }

        QImageReader imgReader(info.absoluteFilePath());
        QSize imgSize = imgReader.size();
        int imgWidth = imgSize.width();
        int imgHeight = imgSize.height();

        if ((imgWidth > 0) && (imgHeight > 0))
        {
            qDebug() << info.absoluteFilePath();


            ImageObject* cell = new ImageObject(this);
            cell->setColIndex(i % m_columnCount);
            cell->setPath(info.absoluteFilePath());
            cell->setFolderPath(path);



            cell->setPicWidth(imgWidth);
            cell->setPicHeight(imgHeight);
            double aspactRatio = imgWidth;
            aspactRatio = aspactRatio / imgHeight;
            cell->setAspectRatio(aspactRatio);

            images << cell;

            i++;

        }
        QApplication::processEvents();




    }
    recalCellIndexes();
    update();
}
