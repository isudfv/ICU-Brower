//
// Created by isudfv on 2022/03/24.
//

#ifndef MOVIE_DISPLAYWIDGET_H
#define MOVIE_DISPLAYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DisplayWidget; }
QT_END_NAMESPACE

class DisplayWidget : public QWidget {
//Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    void on_btnPlay_clicked();
    ~DisplayWidget() override;

private:
    Ui::DisplayWidget *ui;
};

#endif //MOVIE_DISPLAYWIDGET_H
