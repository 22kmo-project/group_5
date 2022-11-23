#ifndef NOSTO_H
#define NOSTO_H

#include <QWidget>
#include <QTimer>

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
    int asiakasnumero;
    QTimer *timer2;
    int aika;

signals:
    void PalaaKotinayttoon();

public slots:
    void ajastin2();

private slots:
    void on_alkuun_clicked();
    void on_kakskyt_clicked();
    void on_nelkyt_clicked();
    void on_kuuskyt_clicked();
    void on_sata_clicked();
    void on_kakssata_clicked();
    void on_viissata_clicked();
};

#endif // NOSTO_H
