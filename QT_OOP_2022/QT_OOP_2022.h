#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QT_OOP_2022.h"

class QT_OOP_2022 : public QMainWindow
{
    Q_OBJECT

public:
    QT_OOP_2022(QWidget *parent = Q_NULLPTR);

private:
    Ui::QT_OOP_2022Class ui;
};
