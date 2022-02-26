//
// Created by matus on 13. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMENUWINDOW_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMENUWINDOW_H


#include <QWidget>

class QtMenuWindow : public QWidget {
Q_OBJECT
private:

public:
    explicit QtMenuWindow(QWidget *parent = nullptr);

private slots:
    void openFileWindow();
    void tmpPrintFileList();
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMENUWINDOW_H
