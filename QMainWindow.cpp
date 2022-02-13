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
#include <QListWidgetItem>

#include "QMainWindow.h"
#include "QExitButton.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

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

    QPushButton *inputButton = new QPushButton("Choose files");
    QPushButton *outputButton = new QPushButton ("Output directory");

    //List of selected files
    QListWidget *selectedFilesList = new QListWidget();
    new QListWidgetItem(tr("16g3e.txt"), selectedFilesList);
    new QListWidgetItem(tr("Blanusa.26"), selectedFilesList);
    new QListWidgetItem(tr("Snarks.92"), selectedFilesList);

    QPushButton *removeFileButton = new QPushButton("Remove");
    QPushButton *removeAllFilesButton = new QPushButton("Clear");

    //Command panel
    QPushButton *runButton = new QPushButton("Run");
    QPushButton *cancelButton = new QPushButton("Cancel");
    QExitButton *exitButton = new QExitButton();


    //Layouts
    //Radio group layout
    QVBoxLayout *formatButtonsLayout = new QVBoxLayout();
    formatButtonsLayout->addWidget(formatLabel);
    formatButtonsLayout->addWidget(resistanceButton);
    formatButtonsLayout->addWidget(parallelPathButton);
    formatButtonsLayout->addWidget(sequentialPathButton);
    formatButtonsLayout->addWidget(kaszonyiValues);
    formatButtonsLayout->addStretch();
    //formatButtonsLayout->addWidget(inputButton);
    //formatButtonsLayout->addWidget(outputButton);

    //FileList command buttons layout
    QHBoxLayout *fileListButtonsLayout = new QHBoxLayout();
    fileListButtonsLayout->addWidget(inputButton);
    fileListButtonsLayout->addStretch();
    fileListButtonsLayout->addWidget(removeFileButton);
    fileListButtonsLayout->addWidget(removeAllFilesButton);

    inputButton->setMinimumWidth(120);
    removeFileButton->setMinimumWidth(80);
    removeAllFilesButton->setMinimumWidth(80);

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
    mainLayout->addWidget(selectedFilesList, 0, 1);
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
