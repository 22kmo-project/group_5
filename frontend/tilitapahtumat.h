#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H

#include <QWidget>

namespace Ui {
class tilitapahtumat;
}

class tilitapahtumat : public QWidget
{
    Q_OBJECT

public:
    explicit tilitapahtumat(QWidget *parent = nullptr);
    ~tilitapahtumat();

private:
    Ui::tilitapahtumat *ui;
};

#endif // TILITAPAHTUMAT_H
