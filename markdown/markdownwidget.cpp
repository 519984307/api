#include "markdownwidget.h"
#include "ui_markdownwidget.h"

MarkDownWidget::MarkDownWidget(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::MarkDownWidget)
{
    ui->setupUi(this);
}

MarkDownWidget::~MarkDownWidget()
{
    delete ui;
}
