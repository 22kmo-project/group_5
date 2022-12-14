#ifndef NOSTO_H
#define NOSTO_H

#include <QWidget>
#include <QTimer>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "saldo.h"

namespace Ui {
class nosto;
}

class nosto : public QWidget
{
    Q_OBJECT

public:
    explicit nosto(QWidget *parent = nullptr);
    ~nosto();
    QTimer *timer2;
    void paivitanosto(int, QString);
    const QByteArray &getWebtoken() const;
    void setWebtoken(const QByteArray &newWebtoken);
    void tilintyyppi(int);
    void muutasaldo(QString);
    void paivitasaldo(QString);


private:
    Ui::nosto *ui;
    int asiakasnumero;
    int aika;
    int amount;
    int balance;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *updateManager;
    QNetworkReply *reply;
    QByteArray webtoken;
    //void withdraw(int amount);
    QByteArray response_data;
    QString username;
    QString muusumma;
    saldo Saldoikkuna;
    QString accounttype;
    int saldo;
    QNetworkAccessManager *getManager;
    QString tilinsaldo;

signals:
    void PalaaKotinayttoon();

public slots:
    void ajastin2();
    void nostoSlot(QNetworkReply *reply);

private slots:
    void on_alkuun_clicked();
    void on_kakskyt_clicked();
    void on_nelkyt_clicked();
    void on_kuuskyt_clicked();
    void on_sata_clicked();
    void on_kakssata_clicked();
    void on_viissata_clicked();
    void on_muusumma_clicked();
    void saldoslot(QNetworkReply *reply);
};

#endif // NOSTO_H
