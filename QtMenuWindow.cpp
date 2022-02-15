//
// Created by matus on 13. 2. 2022.
//

#include "QtMenuWindow.h"

//
// Created by matus on 12. 2. 2022.
//

#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QListWidget>

#include "QtMenuWindow.h"
#include "QtExitButton.h"
#include "QtCancelButton.h"
#include "QtClearButton.h"
#include "QtRemoveButton.h"
#include "QtFileList.h"

QtMenuWindow::QtMenuWindow(QWidget *parent) {


    //Radio panel
    QLabel *formatLabel = new QLabel("Pick what you want to compute:");

    QRadioButton *resistanceButton = new QRadioButton("Resistance values");
    QRadioButton *parallelPathButton = new QRadioButton("Parallel path");
    QRadioButton *sequentialPathButton = new QRadioButton("Sequential path");
    QRadioButton *kaszonyiValues = new QRadioButton("Kaszonyi values");

    QButtonGroup *formatButtonGroup = new QButtonGroup(this);
    formatButtonGroup->addButton(resistanceButton, 0);
    formatButtonGroup->addButton(parallelPathButton, 1);
    formatButtonGroup->addButton(sequentialPathButton, 2);
    formatButtonGroup->addButton(kaszonyiValues, 3);
    formatButtonGroup->setExclusive(true);


    //List of selected files
    QtFileList *fileList = new QtFileList();

    QPushButton *inputButton = new QPushButton("Choose files");
    QtRemoveButton *removeButton = new QtRemoveButton();
    QtClearButton *clearButton = new QtClearButton();

    connect(removeButton, SIGNAL(clicked(bool)), fileList, SLOT(removeSelectedItems()));
    connect(clearButton, SIGNAL(clicked(bool)), fileList, SLOT(clear()));

    //Command panel
    QPushButton *runButton = new QPushButton("Run");
    QPushButton *outputButton = new QPushButton ("Output directory");
    QtCancelButton *cancelButton = new QtCancelButton();
    QtExitButton *exitButton = new QtExitButton();


    //Layouts
    //Radio group layout
    QVBoxLayout *formatButtonsLayout = new QVBoxLayout();
    formatButtonsLayout->addWidget(formatLabel);
    formatButtonsLayout->addWidget(resistanceButton);
    formatButtonsLayout->addWidget(parallelPathButton);
    formatButtonsLayout->addWidget(sequentialPathButton);
    formatButtonsLayout->addWidget(kaszonyiValues);
    formatButtonsLayout->addStretch();

    //FileList command buttons layout
    QHBoxLayout *fileListButtonsLayout = new QHBoxLayout();
    fileListButtonsLayout->addWidget(inputButton);
    fileListButtonsLayout->addStretch();
    fileListButtonsLayout->addWidget(removeButton);
    fileListButtonsLayout->addWidget(clearButton);

    inputButton->setMinimumWidth(120);
    removeButton->setMinimumWidth(80);
    clearButton->setMinimumWidth(80);

    //Command buttons layout
    QHBoxLayout *commandButtonsLayout = new QHBoxLayout();
    commandButtonsLayout->addWidget(runButton);
    commandButtonsLayout->addWidget(outputButton);
    commandButtonsLayout->addStretch();
    commandButtonsLayout->addWidget(cancelButton);
    commandButtonsLayout->addWidget(exitButton);

    runButton->setMinimumWidth(100);
    outputButton->setMinimumWidth(150);
    cancelButton->setMinimumWidth(100);
    exitButton->setMinimumWidth(100);

    //Main grid
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addLayout(formatButtonsLayout, 0, 0);
    mainLayout->addWidget(fileList, 0, 1);
    mainLayout->addLayout(fileListButtonsLayout, 1, 1);
    mainLayout->addLayout(commandButtonsLayout, 3, 0, 1, 2);

    //Resizing and spacing
    mainLayout->setHorizontalSpacing(100);
    mainLayout->setVerticalSpacing(6);
    mainLayout->setRowMinimumHeight(3, 50);
    mainLayout->setAlignment(commandButtonsLayout, Qt::AlignBottom);
    formatButtonsLayout->setSpacing(6);
    fileListButtonsLayout->setSpacing(6);
    commandButtonsLayout->setSpacing(6);
}
