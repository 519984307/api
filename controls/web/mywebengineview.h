#ifndef MYWEBENGINEVIEW_H
#define MYWEBENGINEVIEW_H

#include <QWidget>
#include <QWebEngineView>
#include <QDesktopServices>

namespace Ui
{
class MyWebEngineView;
}
class MainWindow;
class MyWebEngineView : public QWebEngineView
{
    Q_OBJECT

public:
    explicit MyWebEngineView(QWidget* parent = nullptr);
    ~MyWebEngineView();
    QString uuid() const;
    void setUuid(const QString& uuid);

signals:
    MyWebEngineView* openNewWebWindow(QWebEnginePage::WebWindowType type);

protected:
    virtual QWebEngineView* createWindow(QWebEnginePage::WebWindowType type);
private:
    Ui::MyWebEngineView* ui;
    QString m_uuid;
public slots:
    void onUrlChanged(const QUrl& url);
};

#endif // MYWEBENGINEVIEW_H
