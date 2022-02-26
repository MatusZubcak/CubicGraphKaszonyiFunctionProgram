//
// Created by matus on 26. 2. 2022.
//

#include "QtFileWindow.h"

QtFileWindow::QtFileWindow(QWidget *parent) {
    this->setObjectName("FileWindow");
    this->setFileMode(QFileDialog::ExistingFiles);
}