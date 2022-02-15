//
// Created by matus on 15. 2. 2022.
//

#include "QtClearButton.h"

QtClearButton::QtClearButton(QWidget *parent) : QPushButton(parent){
    this->setText("Clear");
    this->setObjectName("ClearButton");
}
