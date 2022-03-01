#include "newselectcardwidgetwindow.h"
#include "ui_newselectcardwidgetwindow.h"

NewSelectCardWidgetWindow::NewSelectCardWidgetWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::NewSelectCardWidgetWindow)
{
    ui->setupUi(this);
}

NewSelectCardWidgetWindow::~NewSelectCardWidgetWindow()
{
    delete ui;
}

QWidget* NewSelectCardWidgetWindow::widget() const
{
    return m_widget;
}

void NewSelectCardWidgetWindow::setWidget(QWidget* widget)
{
    m_widget = widget;
    m_widget->setParent(this);
    setCentralWidget(m_widget);
    m_widget->show();

}
