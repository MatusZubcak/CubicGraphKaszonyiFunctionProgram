//
// Created by matus on 13. 2. 2022.
//

#include "QtExitButton.h"
#include <QApplication>

QtExitButton::QtExitButton(QWidget *parent) : QPushButton(parent) {
    this->setText("Exit");
    this->setObjectName("ExitButton");

    connect(this, SIGNAL (clicked(bool)), QApplication::instance(), SLOT (quit()));
}
