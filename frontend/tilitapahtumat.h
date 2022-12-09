#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class tilitapahtumat;
}

class tilitapahtumat : public QWidget
{
    Q_OBJECT

public:
    explicit tilitapahtumat(QWidget *parent = nullptr);
    ~tilitapahtumat();
    void paivitatilitapahtumat(QString);

    const QByteArray &getWebToken() const;
    void setWebToken(const QByteArray &newWebToken);

private slots:
    void on_alkuun_3_clicked();
    void tiliSlot(QNetworkReply *reply);

private:
    Ui::tilitapahtumat *ui;
    int asiakasnumero;
    QNetworkReply *reply;

    QNetworkAccessManager *getManager;
    QByteArray webToken;
    QString username;
    QByteArray response_data;



signals:
    void PalaaKotinayttoon();

};

#endif // TILITAPAHTUMAT_H
