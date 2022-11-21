#ifndef NOSTO_H
#define NOSTO_H

#include <QWidget>

namespace Ui {
class nosto;
}

class nosto : public QWidget
{
    Q_OBJECT

public:
    explicit nosto(QWidget *parent = nullptr);
    ~nosto();

private:
    Ui::nosto *ui;

signals:
    void PalaaKotinayttoon();

private slots:
    void on_alkuun_clicked();
};

#endif // NOSTO_H
