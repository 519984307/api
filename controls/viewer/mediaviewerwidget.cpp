#include "mediaviewerwidget.h"
#include "ui_mediaviewerwidget.h"

MediaViewerWidget::MediaViewerWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::MediaViewerWidget)
{
    ui->setupUi(this);
    m_isLight = true;
    m_selectMedia = nullptr;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(16);
    setMouseTracking(true);

}

MediaViewerWidget::~MediaViewerWidget()
{
    delete ui;
}

void MediaViewerWidget::addMediaObject(MediaViewerObject* media)
{
    m_mediaObjects << media;
    update();

}

void MediaViewerWidget::insertMediaObject(MediaViewerObject* media, int index)
{
    m_mediaObjects.insert(0, media);
    update();

}

void MediaViewerWidget::paintEvent(QPaintEvent* event)
{
    QColor backGroundColor = m_isLight == true ? Qt::white : Qt::black;
    QPoint curPt = m_helper->cursorPos();
    QRect drawClientRc = m_helper->needDrawClientRect(-height(), height() * 3);
    QPainter painter;
    painter.begin(this);
    QRect clientRc = m_helper->clientRect();
    painter.fillRect(clientRc, QBrush(backGroundColor));
    int l = 16;
    int t = m_helper->itemsTop();
    for (int i = 0; i < m_mediaObjects.count(); i++)
    {
        MediaViewerObject* media = m_mediaObjects.at(i);
        painter.setPen(Qt::black);

        QRect rc(l, t, 432, 768);
        media->setRect(rc);
        if (drawClientRc.contains(rc))
        {

            media->loadImage();
            if ((media->mediaType() == MediaImage) || (media->mediaType() == MediaText))
            {
                if (media->snapRect().height() <= 768)
                {
                    QRect imgRc(rc.left(), rc.top() + (768 - media->snapRect().height()) / 2, rc.width(), media->snapRect().height());
                    painter.drawPixmap(imgRc, media->snapImage(), media->snapRect());
                }
                else
                {
                    QRect mediaRc = QRect(0, 0, rc.width(), rc.height());
                    painter.drawPixmap(rc, media->snapImage(), mediaRc);
                }
            }
            else if (media->mediaType() == MediaUrl)
            {
                QFileInfo info(media->filePath());
                if (info.exists())
                {
                    QFileIconProvider provider;
                    QIcon icon = provider.icon(info);
                    QPixmap pix = icon.pixmap(64, 64);
                    QRect iconRc(rc.left() + 16, rc.top() + 16, 64, 64);
                    painter.drawPixmap(iconRc, pix, pix.rect());

                    QRect textRc(rc.left() + 16, rc.top() + 96, rc.width() - 32, 64);
                    painter.drawText(textRc, media->filePath(), Qt::AlignLeft | Qt::AlignTop);

                    QString suffix = info.suffix().toLower();
                    QSet<QString> suffixes;
                    suffixes << "jpg" << "png" << "jpeg" << "ico";
                    if (suffixes.contains(suffix))
                    {
                        QRect drawRc(textRc.left(), textRc.bottom() + 16, textRc.width(), rc.bottom() - textRc.bottom() - 32);
                        QPixmap drawPix;
                        if (media->fileSnapImage().isNull())
                        {
                            drawPix = QPixmap(info.absoluteFilePath());

                        }
                        else
                        {
                            drawPix = media->fileSnapImage();
                        }

                        if ((drawPix.width() < drawRc.width()) && (drawPix.height() < drawRc.height()))
                        {
                            QRect tempRc(drawRc.left(), drawRc.top(), drawPix.width(), drawPix.height());
                            painter.drawPixmap(tempRc, drawPix, drawPix.rect());
                            media->setFileSnapImage(drawPix);
                        }
                        else
                        {
                            if (media->fileSnapImage().isNull())
                            {
                                drawPix = drawPix.scaledToWidth(drawRc.width(), Qt::SmoothTransformation);
                                media->setFileSnapImage(drawPix);
                            }

                            painter.save();
                            QRect drawPixRc(0, 0, drawRc.width(), drawRc.height());
                            painter.drawPixmap(drawRc, drawPix, drawPixRc);
                            painter.restore();
                        }

                    }
                }
                else
                {
                    QRect drawRc = QRect(rc.left(), rc.top(), media->snapImage().rect().width(),
                                         media->snapImage().rect().height());
                    painter.drawPixmap(drawRc, media->snapImage(), media->snapImage().rect());
                }


            }
            QRect checkRc(rc.left() + 8, rc.top() + 8, 16, 16);
            painter.drawRect(checkRc);
            media->setCheckRect(checkRc);
            if (media->isChecked())
            {
                painter.drawText(checkRc,  Qt::AlignCenter, "√");

            }
            painter.setPen(QColor(153, 209, 255));
            painter.drawRect(rc);
        }
        else
        {
            media->freeImage();
        }

        if ((l + 880) > (width() - 16))
        {
            l = 16;
            t += 784;
        }
        else
        {
            l += 448;
        }

    }
    painter.end();

}

void MediaViewerWidget::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    y = m_helper->itemsTop() + y;
    y = y >= 16 ? 16 : y;
    m_helper->setItemsTop(y);
    update();

}

void MediaViewerWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < m_mediaObjects.count(); i++)
    {
        MediaViewerObject* media = m_mediaObjects.at(i);
        if (media->rect().contains(pt))
        {
            emit onMouseDoubleClick(media);
        }
    }

}

void MediaViewerWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < m_mediaObjects.count(); i++)
    {
        MediaViewerObject* media = m_mediaObjects.at(i);
        if (media->checkRect().contains(pt))
        {
            media->setChecked(!media->isChecked());
            break;
        }
    }
    update();

}

bool MediaViewerWidget::isLight() const
{
    return m_isLight;
}

void MediaViewerWidget::setLight(bool isLight)
{
    m_isLight = isLight;
    update();
}

QPixmap MediaViewerWidget::errorImage() const
{
    return m_errorImage;
}

void MediaViewerWidget::setErrorImage(const QPixmap& errorImage)
{
    m_errorImage = errorImage;
}

void MediaViewerWidget::checkAll()
{
    for (int i = 0; i < m_mediaObjects.count(); i++)
    {
        MediaViewerObject* media = m_mediaObjects.at(i);
        media->setChecked(true);
    }
    update();
}

void MediaViewerWidget::getCheckedMedias(QList<MediaViewerObject*>& medias)
{
    for (int i = 0; i < m_mediaObjects.count(); i++)
    {
        MediaViewerObject* media = m_mediaObjects.at(i);
        if (media->isChecked())
        {
            medias << media;
        }
    }
}

void MediaViewerWidget::reverseCheck()
{
    for (int i = 0; i < m_mediaObjects.count(); i++)
    {
        MediaViewerObject* media = m_mediaObjects.at(i);
        media->setChecked(!media->isChecked());
    }
    update();
}

void MediaViewerWidget::reverseList()
{
    std::reverse(m_mediaObjects.begin(), m_mediaObjects.end());
    m_helper->setItemsTop(16);

}

QRect MediaViewerWidget::rect() const
{
    return m_rect;
}

void MediaViewerWidget::setRect(const QRect& rect)
{
    m_rect = rect;
}

void MediaViewerWidget::clearMediaObjects()
{
    m_helper->setItemsTop(16);
    qDeleteAll(m_mediaObjects);
    m_mediaObjects.clear();
    update();
}

void MediaViewerWidget::addMenuNames(QStringList& menuNames)
{


    for (int i = 0; i < menuNames.count(); i++)
    {
        QAction* act = new QAction(this);
        act->setText(menuNames[i]);
        connect(act, &QAction::triggered, this, &MediaViewerWidget::onMenuItemClick);
        addAction(act);
    }
}

MediaViewerObject* MediaViewerWidget::getSelectedMedia()
{
    m_selectMedia = nullptr;
    QPoint curPt = m_helper->cursorPos();
    for (MediaViewerObject* media : m_mediaObjects)
    {
        if (media->rect().contains(curPt))
        {
            m_selectMedia = media;
            break;

        }
    }

    return m_selectMedia;
}

void MediaViewerWidget::removeMedia(MediaViewerObject* media)
{
    if (media == m_selectMedia)
    {
        m_selectMedia = nullptr;

    }
    m_mediaObjects.removeOne(media);
    delete media;
    update();
}

void MediaViewerWidget::removeMedia(int id)
{
    for (int i = m_mediaObjects.count() - 1; i >= 0; i--)
    {
        MediaViewerObject* media = m_mediaObjects.at(i);
        if (media->id() == id)
        {
            removeMedia(media);
        }
    }
}

void MediaViewerWidget::onMenuItemClick()
{
    QAction* act = static_cast<QAction*>(sender());
    m_selectMedia = getSelectedMedia();
    emit menuItemClick(act, m_selectMedia);
    update();
}
