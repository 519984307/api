#ifndef FNWEBPAGE_H
#define FNWEBPAGE_H

#include <QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEngineSettings>
#include "../base/fnwidgetapi.h"
#include "mywebengineview.h"

namespace Ui
{
class FnWebPage;
}

class FnWebPage : public QWidget
{
    Q_OBJECT

public:
    explicit FnWebPage(QWidget* parent = nullptr);
    ~FnWebPage();

    MyWebEngineView* view() const;
    void setView(MyWebEngineView* view);

    QString url() const;
    void setUrl(const QString& url);
signals:
    MyWebEngineView* openNewWebWindow(QWebEnginePage::WebWindowType type);
public slots:
    MyWebEngineView*  onOpenNewWebWindow(QWebEnginePage::WebWindowType type);
private:
    Ui::FnWebPage* ui;
    MyWebEngineView* m_view;
    QString m_url;
};

#endif // FNWEBPAGE_H
