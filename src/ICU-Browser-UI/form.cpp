#include "form.h"
#include "ui_form.h"
#include <QQuickView>

Form::Form(QWidget *parent) : QWidget(parent),
                              ui(new Ui::Form)
{
    ui->setupUi(this);

    ui->label->setStyleSheet("background: red");
}

void Form::resizeCEFWindow(int x, int y, int width, int height)
{
    this->resize(width, height);
    //    qDebug() << this->size();
    qDebug() << this->pos();
}

Form::~Form()
{
    delete ui;
}
