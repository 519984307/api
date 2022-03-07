#include "imageprocviewer.h"
#include "ui_imageprocviewer.h"

ImageProcViewer::ImageProcViewer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ImageProcViewer)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_operation = ImageProcOperation::IpoDrag;
    m_imgLeft = 0;
    m_imgTop = 0;
    m_factor = 1.0f;
    m_selColorR = 255;
    m_selColorG = 255;
    m_selColorB = 255;
    m_drawObj = new DrawObject(this);
    m_backGroundColor = QColor(113, 113, 113);
    m_isAutoSaved = false;
    m_hasEmit = false;
    m_showState = ImageShowState::IsNone;

}

ImageProcViewer::~ImageProcViewer()
{
    delete ui;
}

void ImageProcViewer::loadFromFile(QString pathName)
{
    m_pathName = pathName;
    qDebug() << pathName;
    clear();
    QFileInfo fileInfo(pathName);
    if ((fileInfo.isDir()) || (!fileInfo.exists()))
    {

        return;
    }

    m_imgData = imread(m_pathName.toLocal8Bit().data(), IMREAD_COLOR);
    if (m_imgData.empty())
    {
        return;
    }
    cvtColor(m_imgData, m_imgData, COLOR_BGR2RGB);
    ImageProcHistoryObject* obj = new ImageProcHistoryObject(this);
    obj->setMat(m_imgData.clone());
    procHistoryList << obj;
    reloadImgData();

    //显示状态
    if (m_showState == ImageShowState::IsFitWidth)
    {
        fitToWidth();
    }
    else if (m_showState == ImageShowState::IsFitHeight)
    {
        fitToHeight();
    }
    else if (m_showState == ImageShowState::IsFit)
    {
        autoFit();
    }
    else if (m_showState == ImageShowState::IsShowOriginal)
    {
        showOriginalSzie();
    }


}

void ImageProcViewer::getImageFromMat(Mat& src)
{
    clear();

    m_imgData = src.clone();
    reloadImgData();
}

void ImageProcViewer::restoreFromMat(Mat& src)
{


    m_imgData = src.clone();
    ImageProcHistoryObject* obj = new ImageProcHistoryObject(this);
    obj->setMat(m_imgData.clone());
    procHistoryList << obj;
    reloadImgData();
}

void ImageProcViewer::pasteTo(Mat& src, int l, int t, int w, int h)
{
    Mat roi = m_imgData(Rect(l, t, w, h));
    src.copyTo(roi);
    reloadImgData();
    if (m_isAutoSaved)
    {
        save();
    }
}

const QString& ImageProcViewer::pathName() const
{
    return m_pathName;
}

void ImageProcViewer::setPathName(const QString& newPathName)
{
    m_pathName = newPathName;
}

void ImageProcViewer::paintEvent(QPaintEvent* event)
{
    QPainter painter;

    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);

    QRect clientRect = m_helper->clientRect();
    painter.fillRect(clientRect, QBrush(m_backGroundColor));


    QRect drawRc(m_imgLeft, m_imgTop, m_showPix.width(), m_showPix.height());
    painter.drawPixmap(drawRc, m_showPix, m_showPix.rect());
    m_showRect = drawRc;
    if (m_operation == ImageProcOperation::IPoDrawRect)
    {
        QPoint pt1 = m_helper->mousedownPoint();
        QPoint pt2 = m_helper->mouseMovePoint();
        m_drawObj->drawRect(painter, pt1, pt2);
    }
    else if (m_operation == ImageProcOperation::IPoDrawLine)
    {
        QPoint pt1 = m_helper->mousedownPoint();
        QPoint pt2 = m_helper->mouseMovePoint();
        painter.drawLine(pt1, pt2);
    }

    painter.end();
}

void ImageProcViewer::mousePressEvent(QMouseEvent* event)
{
    m_helper->startMouseDown();

}

void ImageProcViewer::mouseReleaseEvent(QMouseEvent* event)
{


    if (m_procName != "")
    {
        ImageProcInfo info;
        QPoint pt1 = m_helper->mousedownPoint();
        QPoint pt2 = m_helper->mouseMovePoint();
        m_drawObj->reSetPoints(pt1, pt2);


        info.selWidth = abs(pt2.x() - pt1.x()) / m_factor;
        info.selHeight = abs(pt2.y() - pt1.y()) / m_factor;
        info.selLeft = (pt1.x() - m_imgLeft) / m_factor;
        info.selTop = (pt1.y() - m_imgTop) / m_factor;
        info.imgTop = m_imgTop;
        info.factor = m_factor;
        info.startPoint = m_helper->mousedownPoint();
        info.endPoint = m_helper->mouseMovePoint();
        info.Angle = atan2(info.endPoint.y() - info.startPoint.y(), info.endPoint.x() - info.startPoint.x());
        info.Angle = m_drawObj->radianToAngle(info.Angle);
        info.colorB = m_selColorB;
        info.colorG = m_selColorG;
        info.colorR = m_selColorR;
        info.pickColorR = m_pickColorR;
        info.pickColorG = m_pickColorG;
        info.pickColorB = m_pickColorB;
        info.pointX = info.selLeft;
        info.pointY = info.selTop;
        operatorImage(m_procName, info);
    }
    if (m_operation == ImageProcOperation::IPoPickColor)
    {
        ImageProcInfo info;
        QPoint pt1 = m_helper->mousedownPoint();
        QPoint pt2 = m_helper->mouseMovePoint();
        m_drawObj->reSetPoints(pt1, pt2);


        info.selWidth = abs(pt2.x() - pt1.x()) / m_factor;
        info.selHeight = abs(pt2.y() - pt1.y()) / m_factor;
        info.selLeft = (pt1.x() - m_imgLeft) / m_factor;
        info.selTop = (pt1.y() - m_imgTop) / m_factor;
        info.imgTop = m_imgTop;
        info.factor = m_factor;
        info.startPoint = m_helper->mousedownPoint();
        info.endPoint = m_helper->mouseMovePoint();
        info.pointX = info.selLeft;
        info.pointY = info.selTop;
        getPickColor(m_imgData, info.selLeft, info.selTop, m_pickColorR, m_pickColorG, m_pickColorB);
        m_operation = ImageProcOperation::IPoNone;

    }
    m_helper->startMouseUp();
    m_operation = ImageProcOperation::IpoDrag;



}

void ImageProcViewer::mouseMoveEvent(QMouseEvent* event)
{
    if (m_helper->mousedownFlag())
    {
        QPoint mvPt = m_helper->mouseMovePoint();
        QPoint curPt = m_helper->cursorPos();
        if (m_operation == ImageProcOperation::IpoDrag)
        {
            m_imgLeft += curPt.x() - mvPt.x();
            m_imgTop += curPt.y() - mvPt.y();

        }
        else
        {

        }

        m_helper->setMouseMovePoint(curPt);
        update();

    }

}

void ImageProcViewer::wheelEvent(QWheelEvent* event)
{
    int d = event->angleDelta().y();
    QPoint curPt = m_helper->cursorPos();
    if (!m_showRect.contains(curPt))
    {
        return;
    }
    double fx = curPt.x() - m_showRect.left();
    fx = fx / m_showPix.width();

    double fy = curPt.y() - m_showRect.top();
    fy = fy / m_showPix.height();

    if (d > 0)
    {
        m_factor = m_factor * 1.1f;
    }
    else
    {
        m_factor = m_factor * 0.9f;
    }

    qDebug() << m_factor;
    double w = m_factor * m_imgPix.width();
    m_showPix = m_imgPix.scaledToWidth(w, Qt::SmoothTransformation);

    m_imgLeft = curPt.x() - m_showPix.width() * fx;
    m_imgTop = curPt.y() - m_showPix.height() * fy;
    qDebug() << m_showRect << m_imgLeft << m_imgTop;
    update();

}

ImageShowState ImageProcViewer::showState() const
{
    return m_showState;
}

void ImageProcViewer::setShowState(ImageShowState newShowState)
{
    m_showState = newShowState;
}

bool ImageProcViewer::hasEmit() const
{
    return m_hasEmit;
}

void ImageProcViewer::setHasEmit(bool newHasEmit)
{
    m_hasEmit = newHasEmit;
}

void ImageProcViewer::showProcHistoryListDialog()
{
    if (procHistoryList.count() == 0)
    {
        return;
    }
    ShowImageProcHistoryDialog* dlg = new ShowImageProcHistoryDialog();
    dlg->setProcHistoryList(procHistoryList);
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        ImageProcHistoryObject* selObj = dlg->selObj();
        Mat mat = selObj->mat();
        restoreFromMat(mat);
        if (m_isAutoSaved)
        {
            save();
        }
    }
    delete dlg;

}

bool ImageProcViewer::isAutoSaved() const
{
    return m_isAutoSaved;
}

void ImageProcViewer::setAutoSaved(bool newIsAutoSaved)
{
    m_isAutoSaved = newIsAutoSaved;
}

const QColor& ImageProcViewer::backGroundColor() const
{
    return m_backGroundColor;
}

void ImageProcViewer::setBackGroundColor(const QColor& newBackGroundColor)
{
    m_backGroundColor = newBackGroundColor;
}

int ImageProcViewer::selColorB() const
{
    return m_selColorB;
}

void ImageProcViewer::setSelColorB(int newSelColorB)
{
    m_selColorB = newSelColorB;
}

int ImageProcViewer::selColorG() const
{
    return m_selColorG;
}

void ImageProcViewer::setSelColorG(int newSelColorG)
{
    m_selColorG = newSelColorG;
}

int ImageProcViewer::selColorR() const
{
    return m_selColorR;
}

void ImageProcViewer::setSelColorR(int newSelColorR)
{
    m_selColorR = newSelColorR;
}

const QString& ImageProcViewer::procName() const
{
    return m_procName;
}

void ImageProcViewer::setProcName(const QString& newProcName)
{
    m_procName = newProcName;
}

void ImageProcViewer::setFactor(double newFactor)
{
    m_factor = newFactor;
}

double ImageProcViewer::factor() const
{
    return m_factor;
}

void ImageProcViewer::zoomIn()
{
    m_factor = m_factor * 1.1f;
    qDebug() << m_factor;
    double w = m_factor * m_imgPix.width();
    qDebug() << w;
    qDebug() << w;
    m_showPix = m_imgPix.scaledToWidth(w, Qt::SmoothTransformation);
    m_imgLeft = 0;
    m_imgTop = 0;
    update();

}

void ImageProcViewer::zoomOut()
{
    m_factor = m_factor * 0.9f;
    double w = m_factor * m_imgPix.width();

    qDebug() << w;
    m_showPix = m_imgPix.scaledToWidth(w, Qt::SmoothTransformation);
    m_imgLeft = 0;
    m_imgTop = 0;
    update();
}

void ImageProcViewer::clear()
{
    qDeleteAll(procHistoryList);
    procHistoryList.clear();
    m_imgPix = QPixmap();
    m_showPix = QPixmap();
    m_imgData.release();
    update();
}

void ImageProcViewer::save()
{
    QFileInfo fileInfo(m_pathName);
    QDir dir;
    dir.mkpath(fileInfo.absolutePath());
    Mat dest;
    cvtColor(m_imgData, dest, COLOR_RGB2BGR);
    imwrite(m_pathName.toLocal8Bit().data(), dest);

}



void ImageProcViewer::setOperation(ImageProcOperation newOperation)
{
    m_operation = newOperation;
}

void ImageProcViewer::fitToWidth()
{
    m_showPix = m_imgPix.scaledToWidth(width(), Qt::SmoothTransformation);
    m_factor = double(m_showPix.width()) / (double)m_imgPix.width();
    qDebug() << m_factor;
    m_imgLeft = 0;
    m_imgTop = 0;
    update();
}

void ImageProcViewer::fitToHeight()
{
    m_showPix = m_imgPix.scaledToHeight(height(), Qt::SmoothTransformation);
    m_factor = double(m_showPix.width()) / (double)m_imgPix.width();
    m_imgLeft = 0;
    m_imgTop = 0;
    update();
}

void ImageProcViewer::autoFit()
{
    double d1 = double(width()) / double(height());
    double d2 = double(m_imgPix.width()) / double(m_imgPix.height());
    if (d1 < d2)
    {
        fitToWidth();
    }
    else
    {
        fitToHeight();
    }
}

void ImageProcViewer::showOriginalSzie()
{
    m_showPix = m_imgPix.copy();
    m_imgLeft = 0;
    m_imgTop = 0;
    update();
}

void ImageProcViewer::operatorImage(QString name, ImageProcInfo& info)
{
    AbstractImageProcOperator* op = imgProcs.value(name, nullptr);
    if (op == nullptr)
    {
        return;
    }
    Mat dest;
    if (m_hasEmit)
    {
        op->operatorImage(m_imgData, dest, info);
        emit afterOperatorImage(m_procName, m_imgData, dest, info);
        m_hasEmit = false;
    }
    else
    {
        op->operatorImage(m_imgData, m_imgData, info);
        ImageProcHistoryObject* obj = new ImageProcHistoryObject(this);
        obj->setMat(m_imgData.clone());
        procHistoryList << obj;

    }

    m_procName = "";
    reloadImgData();
    if (m_isAutoSaved)
    {
        save();
    }


}

void ImageProcViewer::operatorImage(QString name, ImageProcInfo& info, Mat& dest)
{
    AbstractImageProcOperator* op = imgProcs.value(name, nullptr);
    if (op == nullptr)
    {
        return;
    }
    op->operatorImage(m_imgData, dest, info);
    m_procName = "";

}

void ImageProcViewer::reloadImgData()
{

    QImage image = QImage((const uchar*)(m_imgData.data),
                          m_imgData.cols, m_imgData.rows,
                          m_imgData.cols * m_imgData.channels(),
                          QImage::Format_RGB888);
    m_imgPix = QPixmap::fromImage(image);
    double w = (double)m_imgPix.width() * m_factor;
    m_showPix = m_imgPix.scaledToWidth(w, Qt::SmoothTransformation);
    update();
}

int ImageProcViewer::imgTop() const
{
    return m_imgTop;
}

void ImageProcViewer::setImgTop(int newImgTop)
{
    m_imgTop = newImgTop;
}

int ImageProcViewer::imgLeft() const
{
    return m_imgLeft;
}

void ImageProcViewer::setImgLeft(int newImgLeft)
{
    m_imgLeft = newImgLeft;
}
