//
// Created by matus on 26. 2. 2022.
//

#include "QtChooseFilesButton.h"

QtChooseFilesButton::QtChooseFilesButton(QWidget *parent) : QPushButton(parent) {
    this->setText("Choose files");
    this->setObjectName("ChooseFilesButton");
}