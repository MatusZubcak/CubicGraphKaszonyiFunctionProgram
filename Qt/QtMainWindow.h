//
// Created by matus on 12. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMAINWINDOW_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMAINWINDOW_H

#include <QWidget>
#include <QLayout>
#include "QtMenuWindow.h"

class QtMainWindow : public QWidget {
    Q_OBJECT
public:
    explicit QtMainWindow(QWidget *parent = nullptr);

private:
    QLayout *wrapperLayout{};
    QWidget *activeWindow{};

    void initialiseMenuWindow();

private slots:
    void loadMenuWindow();
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTMAINWINDOW_H
