//
// Created by matus on 13. 2. 2022.
//

#include "QExitButton.h"
#include <QApplication>

QExitButton::QExitButton(QWidget *parent) : QPushButton(parent) {
    this->setText("Exit");

    connect(this, SIGNAL (clicked(bool)), QApplication::instance(), SLOT (quit()));
}

QExitButton::QExitButton() : QPushButton() {
    this->setText("Exit");

    connect(this, SIGNAL (clicked(bool)), QApplication::instance(), SLOT (quit()));
}
