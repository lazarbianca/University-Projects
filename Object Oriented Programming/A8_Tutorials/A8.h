#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_A8.h"

class A8 : public QMainWindow
{
    Q_OBJECT

public:
    A8(QWidget *parent = nullptr);
    ~A8();

private:
    Ui::A8Class ui;
};
