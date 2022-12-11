#include "saldo.h"
#include "ui_saldo.h"
#include "myurl.h"

saldo::saldo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::saldo)
{
    ui->setupUi(this);
}

saldo::~saldo()
{
    delete ui;
}

void saldo::paivitasaldo(QString user)
{
    username=user;
    ui->asiakasnro->setText(username);

    QString site_url=myUrl::getBaseUrl()+"/account/"+username;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),("Bearer "+webtoken));
    //WEBTOKEN LOPPU
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(saldoSlot(QNetworkReply*)));

    reply = getManager->get(request);

}

void saldo::paivitatilitapahtumat(QString user)
{
    username=user;
    QString site_url=myUrl::getBaseUrl()+"/action/"+username;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),("Bearer "+webtoken));
    //WEBTOKEN LOPPU
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(tilitapahtumaSlot(QNetworkReply*)));

    reply = getManager->get(request);
}

void saldo::on_alkuun_2_clicked()
{
    emit PalaaKotinayttoon(); //saldonäkymästä aloitusnäyttöön
}

void saldo::saldoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();


    foreach (const QJsonValue &value, json_array) { //vääntää json:in QStringiksi
        QJsonObject json_obj = value.toObject();
        tilinsaldo+=QString::number(json_obj["saldo"].toInt());
    }

    //qDebug()<<saldo;
    ui->tilinsaldo->clear();
    ui->tilinsaldo->setText(tilinsaldo);

    reply->deleteLater();
    getManager->deleteLater();
}

void saldo::tilitapahtumaSlot(QNetworkReply *reply)
{
    qDebug() << "is this being ran";
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tapahtumat;
    foreach (const QJsonValue &value, json_array) { //vääntää json:it textiksi
        QJsonObject json_obj = value.toObject();
        tapahtumat+="card: "+QString::number(json_obj["idaccount"].toInt())+", date: "+json_obj["action_time"].toString()+",\r amount: "+QString::number(json_obj["amount"].toInt())+"\r\r";
    }

    //qDebug()<<tapahtumat;

    ui->tilitapahtumabox->setText(tapahtumat);

    reply->deleteLater();
    getManager->deleteLater();
}

const QByteArray &saldo::getWebtoken() const
{
    return webtoken;
}

void saldo::setWebtoken(const QByteArray &newWebtoken)
{
    webtoken = newWebtoken;
}
