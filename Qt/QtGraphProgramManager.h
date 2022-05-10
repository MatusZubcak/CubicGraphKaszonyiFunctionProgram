//
// Created by matus on 9.5.2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTGRAPHPROGRAMMANAGER_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTGRAPHPROGRAMMANAGER_H


#include <QObject>
#include "../Enums.h"

class QtGraphProgramManager : public QObject {
    Q_OBJECT

public:
    explicit QtGraphProgramManager(QWidget *parent = nullptr);

private slots:
    void runGraphProgram(formatType formatType, QStringList filePaths, QString outputDirectory);

signals:
    void enableMainWindow(QtGraphProgramManager*);
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTGRAPHPROGRAMMANAGER_H
