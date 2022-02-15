//
// Created by matus on 15. 2. 2022.
//

#include "QtRemoveButton.h"

QtRemoveButton::QtRemoveButton(QWidget *parent) : QPushButton(parent) {
    this->setText("Remove");
    this->setObjectName("RemoveButton");
}
