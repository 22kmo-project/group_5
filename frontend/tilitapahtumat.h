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

private slots:
    void on_alkuun_3_clicked();

private:
    Ui::tilitapahtumat *ui;
    int asiakasnumero;

signals:
    void PalaaKotinayttoon();
};

#endif // TILITAPAHTUMAT_H