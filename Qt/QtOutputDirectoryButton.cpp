//
// Created by matus on 9.5.2022.
//

#include "QtOutputDirectoryButton.h"

QtOutputDirectoryButton::QtOutputDirectoryButton(QWidget *parent) : QPushButton(parent) {
    this->setText("Output directory");
    this->setObjectName("OutputDirectoryButton");
}