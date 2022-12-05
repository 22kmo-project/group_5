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
    void paivitatilitapahtumat();

private slots:
    void on_alkuun_3_clicked();

private:
    Ui::tilitapahtumat *ui;
    int asiakasnumero;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray token;
    //QByteArray response_data;



signals:
    void PalaaKotinayttoon();

};

#endif // TILITAPAHTUMAT_H
