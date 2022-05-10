//
// Created by matus on 13. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMENUWINDOW_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMENUWINDOW_H


#include <QWidget>
#include "QtFileList.h"
#include "../Enums.h"
#include "QtGraphProgramManager.h"

class QtMenuWindow : public QWidget {
Q_OBJECT
private:
    QString outputDirectory = "";

    QStringList getFilenameList();
    formatType getFormatType();

public:
    explicit QtMenuWindow(QWidget *parent = nullptr);

private slots:
    void enableWindow(QtGraphProgramManager* qtGraphProgramManager);
    void openFileWindow();
    void tmpPrintFileList();
    void pickOutputDirectory();

signals:
    void startGraphProgram(formatType formatType, QStringList filenames, QString outputDirector);
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMENUWINDOW_H
