//
// Created by matus on 13. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMENUWINDOW_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMENUWINDOW_H


#include <QWidget>
#include <QThread>
#include <QMutex>
#include "QtFileList.h"
#include "../Enums.h"
#include "QtGraphProgramManager.h"

class QtMenuWindow : public QWidget {
Q_OBJECT
private:
    QString outputDirectory = "";
    QThread programThread;
    QMutex mutex;
    QStringList invalidFiles;
    QStringList getFilenameList();

public:
    explicit QtMenuWindow(QWidget *parent = nullptr);

private slots:
    void enableWindow();
    void openFileWindow();
    void computeGraphs();
    void pickOutputDirectory();
    void popException(QString fileName);

signals:
    void startGraphProgram(int formatType, QStringList filenames, QString outputDirector);
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMENUWINDOW_H
