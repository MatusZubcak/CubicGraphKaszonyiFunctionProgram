//
// Created by matus on 15. 2. 2022.
//

#ifndef CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTFILELIST_H
#define CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTFILELIST_H

#include <QListWidget>

class QtFileList : public QListWidget {
Q_OBJECT
public:
    explicit QtFileList(QWidget *parent = nullptr);

private slots:
    void removeSelectedItems();
};


#endif //CUBICGRAPHKASZONYIFUNCTIONPROGRAM_QTFILELIST_H
