//
// Created by matus on 15. 2. 2022.
//

#include <iostream>
#include "QtFileList.h"

QtFileList::QtFileList(QWidget *parent) : QListWidget(parent) {
    this->setObjectName("FileList");
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void QtFileList::removeSelectedItems() {
    qDeleteAll(this->selectedItems());
}