//
// Created by matus on 15. 2. 2022.
//

#include <iostream>
#include "QtFileList.h"

QtFileList::QtFileList(QWidget *parent) : QListWidget(parent) {
    this->setObjectName("FileList");
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //TODO remove eventually
    new QListWidgetItem(tr("16g3e.txt"), this);
    new QListWidgetItem(tr("Blanusa.26"), this);
    new QListWidgetItem(tr("Snarksx.92"), this);
}

void QtFileList::removeSelectedItems() {
    qDeleteAll(this->selectedItems());
}