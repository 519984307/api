#include "fnwebpage.h"
#include "ui_fnwebpage.h"

FnWebPage::FnWebPage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnWebPage)
{
    ui->setupUi(this);
    m_view = new MyWebEngineView(this);
    m_view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    m_view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    connect(m_view, &MyWebEngineView::openNewWebWindow, this, &FnWebPage::onOpenNewWebWindow);
    addWidgetToPage(this, m_view);

}

FnWebPage::~FnWebPage()
{
    delete ui;
}

MyWebEngineView* FnWebPage::view() const
{
    return m_view;
}

void FnWebPage::setView(MyWebEngineView* view)
{

    m_view = view;

}

QString FnWebPage::url() const
{
    return m_url;
}

void FnWebPage::setUrl(const QString& url)
{
    m_url = url;
    m_view->load(QUrl(url));
}

MyWebEngineView* FnWebPage::onOpenNewWebWindow(QWebEnginePage::WebWindowType type)
{
    MyWebEngineView* w;
    emit w = openNewWebWindow(type);
    return w;


}
