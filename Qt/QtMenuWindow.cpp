//
// Created by matus on 13. 2. 2022.
//

#include "QtMenuWindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QListWidget>
#include <iostream>
#include <QMessageBox>
#include "QtMenuWindow.h"
#include "QtExitButton.h"
#include "QtCancelButton.h"
#include "QtClearButton.h"
#include "QtRemoveButton.h"
#include "QtFileList.h"
#include "QtChooseFilesButton.h"
#include "QtFileWindow.h"
#include "QtRunButton.h"
#include "QtOutputDirectoryButton.h"
#include "QtDirectoryWindow.h"
#include "QtGraphProgramManager.h"
#include "../Enums.h"

QtMenuWindow::QtMenuWindow(QWidget *parent) {

    //Radio panel
    QLabel *formatLabel = new QLabel("Select what you want to compute:");

    QRadioButton *resistanceButton = new QRadioButton("Parallel and serial resistance values");
    QRadioButton *parallelPathButton = new QRadioButton("Parallel resistance path");
    QRadioButton *sequentialPathButton = new QRadioButton("Serial resistance path");
    QRadioButton *kaszonyiValues = new QRadioButton("Kaszonyi function values");

    QButtonGroup *formatButtonGroup = new QButtonGroup(this);
    formatButtonGroup->setObjectName("formatButtonGroup");
    formatButtonGroup->addButton(resistanceButton, 0);
    formatButtonGroup->addButton(parallelPathButton, 1);
    formatButtonGroup->addButton(sequentialPathButton, 2);
    formatButtonGroup->addButton(kaszonyiValues, 3);
    formatButtonGroup->setExclusive(true);


    //List of selected files
    QtFileList *fileList = new QtFileList();

    QtChooseFilesButton *chooseFilesButton = new QtChooseFilesButton;
    QtRemoveButton *removeButton = new QtRemoveButton();
    QtClearButton *clearButton = new QtClearButton();

    connect(chooseFilesButton, SIGNAL(clicked(bool)), this, SLOT(openFileWindow()));
    connect(removeButton, SIGNAL(clicked(bool)), fileList, SLOT(removeSelectedItems()));
    connect(clearButton, SIGNAL(clicked(bool)), fileList, SLOT(clear()));

    //Command panel
    QtRunButton *runButton = new QtRunButton();
    QtOutputDirectoryButton *outputButton = new QtOutputDirectoryButton();
    QtCancelButton *cancelButton = new QtCancelButton();
    QtExitButton *exitButton = new QtExitButton();

    connect(runButton, SIGNAL(clicked(bool)), this, SLOT(tmpPrintFileList()));
    connect(outputButton, SIGNAL(clicked(bool)), this, SLOT(pickOutputDirectory()));

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
    fileListButtonsLayout->addWidget(chooseFilesButton);
    fileListButtonsLayout->addStretch();
    fileListButtonsLayout->addWidget(removeButton);
    fileListButtonsLayout->addWidget(clearButton);

    chooseFilesButton->setMinimumWidth(120);
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

void QtMenuWindow::openFileWindow() {
    QtFileWindow *fileWindow = new QtFileWindow(nullptr);
    if (fileWindow->exec() == QDialog::Accepted) {
        QtFileList *fileList = this->findChild<QtFileList*>("FileList");
        QStringList filepathList = fileWindow->selectedFiles();

        for(auto filepath : filepathList){
            QString filename = filepath.section('/', -1);
            if(fileList->findItems(filename, Qt::MatchExactly).empty()){
                QListWidgetItem *listItem = new QListWidgetItem(filename, fileList);
                listItem->setData(1, filepath);
            }
        }
    }

    delete fileWindow;
}

void QtMenuWindow::pickOutputDirectory() {
    QtDirectoryWindow *directoryWindow = new QtDirectoryWindow(nullptr);
    if(directoryWindow->exec() == QDialog::Accepted){
        this->outputDirectory = directoryWindow->selectedFiles().front();
    }

    delete directoryWindow;
}

void QtMenuWindow::tmpPrintFileList() {
    formatType formatType = getFormatType();
    QStringList filenameList = getFilenameList();

    if(formatType == NONE){
        QMessageBox noFormatMessageBox;
        noFormatMessageBox.setWindowTitle("Information box");
        noFormatMessageBox.setText("Please select what you want to compute");
        noFormatMessageBox.exec();
        return;
    }

    if(outputDirectory == ""){
        QMessageBox noOutputDirectoryMessageBox;
        noOutputDirectoryMessageBox.setWindowTitle("Information box");
        noOutputDirectoryMessageBox.setText("Please select output directory");
        noOutputDirectoryMessageBox.exec();
        return;
    }

    if(filenameList.empty()){
        QMessageBox noFilesMessageBox;
        noFilesMessageBox.setWindowTitle("Information box");
        noFilesMessageBox.setText("Please choose some files");
        noFilesMessageBox.exec();
        return;
    }

    QtGraphProgramManager *qtGraphProgramManager = new QtGraphProgramManager();
    connect(this, SIGNAL(startGraphProgram(formatType, QStringList, QString)),
            qtGraphProgramManager, SLOT(runGraphProgram(formatType, QStringList, QString)));
    connect(qtGraphProgramManager, SIGNAL(enableMainWindow(QtGraphProgramManager*)),
            this, SLOT(enableWindow(QtGraphProgramManager*)));

    this->setDisabled(true);
    emit startGraphProgram(formatType, filenameList, outputDirectory);

}

formatType QtMenuWindow::getFormatType() {
    formatType formatType;
    QButtonGroup *formatButtonGroup = this->findChild<QButtonGroup*>("formatButtonGroup");
    switch (formatButtonGroup->checkedId()) {
        case 0:
            formatType = RESISTANCE_VALUES;
            break;
        case 1:
            formatType = PARALLEL_PATH;
            break;
        case 2:
            formatType = SEQUENTIAL_PATH;
            break;
        case 3:
            formatType = KASZONYI_FUNCTION;
            break;
        default:
            formatType = NONE;
    }
    return formatType;
}

QStringList QtMenuWindow::getFilenameList() {
    QtFileList *fileList = this->findChild<QtFileList*>("FileList");
    QStringList filenameList;

    for(int i = 0 ; i <fileList->count(); i++){
        QListWidgetItem *item =  fileList->item(i);
        QString filename = item->data(1).toString();
        filenameList.push_back(filename);
    }

    return filenameList;
}

void QtMenuWindow::enableWindow(QtGraphProgramManager* qtGraphProgramManager) {
    delete qtGraphProgramManager;
    this->setEnabled(true);
}
