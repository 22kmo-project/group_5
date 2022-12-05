#include "saldo.h"
#include "ui_saldo.h"
#include "myurl.h"

saldo::saldo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::saldo)
{
    ui->setupUi(this);
    //ui->asiakasnro->setText("0004");
    ui->tilitapahtumabox->setText("tähän tullee rajusti sitten niitä tilitapahtumia, tässä pittää sitten tarkastella sitä rivitystä varmaankin että ei tule pötköön");
    //ui->tilinsaldo->setText("23 000€"); //tähän haetaan tilin saldo tietokannasta
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

void saldo::on_alkuun_2_clicked()
{
    emit PalaaKotinayttoon(); //saldonäkymästä aloitusnäyttöön
}

void saldo::saldoSlot(QNetworkReply *reply)
{
    //response_Data=reply->readAll();
    //qDebug() << response_Data;
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    QString saldo;
    foreach (const QJsonValue &value, json_array) { //vääntää json:in QStringiksi
        QJsonObject json_obj = value.toObject();
        saldo+=QString::number(json_obj["saldo"].toInt());
    }

    qDebug()<<saldo;

    ui->tilinsaldo->setText(saldo);

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
