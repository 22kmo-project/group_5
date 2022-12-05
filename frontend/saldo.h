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
    void paivitasaldo();

private slots:
    void on_alkuun_2_clicked();

private:
    Ui::saldo *ui;
    int asiakasnumero;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray token;

signals:
    void PalaaKotinayttoon();
};

#endif // SALDO_H
