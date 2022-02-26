//
// Created by matus on 26. 2. 2022.
//

#include "QtRunButton.h"

QtRunButton::QtRunButton(QWidget *parent) : QPushButton(parent) {
    this->setText("Run");
    this->setObjectName("RunButton");
}
