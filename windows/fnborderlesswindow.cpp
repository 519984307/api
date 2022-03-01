#include "fnborderlesswindow.h"

FnBorderLessWindow::FnBorderLessWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    m_titleBar = new FnTitleBar(this);
    m_titleBar->setParentWindow(this);
    boundaryWidth = 4;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);

}

bool FnBorderLessWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    MSG* msg = (MSG*)message;
    QPoint curPt = m_helper->cursorPos();
    int xPos = curPt.x();
    int yPos = curPt.y();
    switch (msg->message)
    {
    case WM_NCHITTEST:


        if (xPos < boundaryWidth && yPos < boundaryWidth)                 //左上角
            *result = HTTOPLEFT;
        else if (curPt.x() >= width() - boundaryWidth && yPos < boundaryWidth) //右上角
            *result = HTTOPRIGHT;
        else if (xPos < boundaryWidth && yPos >= height() - boundaryWidth) //左下角
            *result = HTBOTTOMLEFT;
        else if (xPos >= width() - boundaryWidth && yPos >= height() - boundaryWidth) //右下角
            *result = HTBOTTOMRIGHT;
        else if (xPos < boundaryWidth)                                    //左边
            *result =  HTLEFT;
        else if (xPos >= width() - boundaryWidth)                         //右边
            *result = HTRIGHT;
        else if (yPos < boundaryWidth)                                    //上边
            *result = HTTOP;
        else if (yPos >= height() - boundaryWidth)                        //下边
            *result = HTBOTTOM;
        else              //其他部分不做处理，返回false，留给其他事件处理器处理
            return false;
        return true;
    }
    return false;         //此处返回false，留给其他事件处理器处理

}

void FnBorderLessWindow::mousePressEvent(QMouseEvent* e)
{
//    if (e->button() == Qt::LeftButton)
//        clickPos = e->pos();

}

void FnBorderLessWindow::mouseMoveEvent(QMouseEvent* e)
{
//    if (e->buttons()&Qt::LeftButton)
//        move(e->pos() + pos() - clickPos);

}


