//
// Created by matus on 9.5.2022.
//

#include "QtDirectoryWindow.h"

QtDirectoryWindow::QtDirectoryWindow(QWidget *parent) {
    this->setObjectName("DirectoryWindow");
    this->setFileMode(QFileDialog::Directory);
    this->setOption(ShowDirsOnly, true);
}