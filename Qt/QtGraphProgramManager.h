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
    explicit QtGraphProgramManager(QObject *parent = nullptr);

private slots:
    void runGraphProgram(int formatType, QStringList filePaths, QString outputDirectory);

signals:
    void enableMainWindow();
    void castException(QString fileName);
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTGRAPHPROGRAMMANAGER_H
