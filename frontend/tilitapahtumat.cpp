#include "tilitapahtumat.h"
#include "ui_tilitapahtumat.h"
#include "myurl.h"

tilitapahtumat::tilitapahtumat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tilitapahtumat)
{
    ui->setupUi(this);
    //ui->asiakasnro->setText("0004"); //tähän asiakkaan tiedot, kortin numero
    //ui->tilitapahtumabox->setText("tähän tullee rajusti sitten niitä tilitapahtumia, tässä pittää sitten tarkastella sitä rivitystä varmaankin että ei tule pötköön");
}

tilitapahtumat::~tilitapahtumat()
{
    delete ui;
}

void tilitapahtumat::paivitatilitapahtumat(QString user)
{

    QString wb=this->getWebToken();
    //qDebug()<<"tilitapahtumat" + wb;
    username = user;
    ui->asiakasnro->setText(username); //asiakkaan kortin numro näytölle

    QString site_url=myUrl::getBaseUrl()+"/action/"+username;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),("Bearer "+webToken));
    //WEBTOKEN LOPPU
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(tiliSlot(QNetworkReply*)));

    reply = getManager->get(request);
}

void tilitapahtumat::on_alkuun_3_clicked()
{
    emit PalaaKotinayttoon(); //tilitapahtumanäkymästä aloitusnäyttöön
}

void tilitapahtumat::tiliSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tapahtumat;
    foreach (const QJsonValue &value, json_array) { //vääntää json:it textiksi
        QJsonObject json_obj = value.toObject();
        tapahtumat+="card: "+QString::number(json_obj["idaccount"].toInt())+", date: "+json_obj["action_time"].toString()+", amount: "+QString::number(json_obj["amount"].toInt())+"\r";
    }

    qDebug()<<tapahtumat;

    ui->tilitapahtumabox->setText(tapahtumat);

    reply->deleteLater();
    getManager->deleteLater();
}

const QByteArray &tilitapahtumat::getWebToken() const
{
    return webToken;
}

void tilitapahtumat::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}
