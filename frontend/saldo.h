#ifndef SALDO_H
#define SALDO_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class saldo;
}

class saldo : public QWidget
{
    Q_OBJECT

public:
    explicit saldo(QWidget *parent = nullptr);
    ~saldo();
    void paivitasaldo(QString);
    void paivitatilitapahtumat(QString);
    void tuoTiedot(QString, QString);
    QString tilinsaldo;
    const QByteArray &getWebtoken() const;
    void setWebtoken(const QByteArray &newWebtoken);

private slots:
    void on_alkuun_2_clicked();
    void saldoSlot (QNetworkReply *reply);
    void tilitapahtumaSlot(QNetworkReply *reply);

private:
    Ui::saldo *ui;
    int asiakasnumero;
    QByteArray webtoken;
    QString username;

    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_Data;

signals:
    void PalaaKotinayttoon();
};

#endif // SALDO_H
