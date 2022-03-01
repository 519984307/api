#include "mywebengineview.h"
#include "ui_mywebengineview.h"

MyWebEngineView::MyWebEngineView(QWidget* parent) :
    QWebEngineView(parent),
    ui(new Ui::MyWebEngineView)
{
    ui->setupUi(this);
    connect(this, &MyWebEngineView::urlChanged, this, &MyWebEngineView::onUrlChanged);


}

MyWebEngineView::~MyWebEngineView()
{
    delete ui;
}

void MyWebEngineView::onUrlChanged(const QUrl& url)
{
    qDebug() << "change" << url;
    setUrl(url);






}

QWebEngineView* MyWebEngineView::createWindow(QWebEnginePage::WebWindowType type)
{


    MyWebEngineView* w = nullptr;
    emit w = openNewWebWindow(type);
    connect(w, &MyWebEngineView::urlChanged, this, &MyWebEngineView::onUrlChanged);

    return w;
}

QString MyWebEngineView::uuid() const
{
    return m_uuid;
}

void MyWebEngineView::setUuid(const QString &uuid)
{
    m_uuid = uuid;
}
