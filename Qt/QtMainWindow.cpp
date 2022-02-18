//
// Created by matus on 12. 2. 2022.
//

#include <QHBoxLayout>

#include "QtMainWindow.h"
#include "QtMenuWindow.h"
#include "QtCancelButton.h"

QtMainWindow::QtMainWindow(QWidget *parent) : QWidget(parent) {
    initialiseMenuWindow();
}

void QtMainWindow::initialiseMenuWindow(){
    delete wrapperLayout;
    delete activeWindow;

    activeWindow = new QtMenuWindow();
    wrapperLayout = new QHBoxLayout(this);

    wrapperLayout->setSpacing(0);
    wrapperLayout->addWidget(activeWindow);

    connect(activeWindow->findChild<QtCancelButton*>("CancelButton"), SIGNAL (clicked()), this, SLOT (loadMenuWindow()));
}

void QtMainWindow::loadMenuWindow(){
    initialiseMenuWindow();
}
