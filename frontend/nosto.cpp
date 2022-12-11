#include "nosto.h"
#include "ui_nosto.h"
#include "myurl.h"
#include <QMessageBox>
#include <QDebug>
#include <QValidator>

nosto::nosto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nosto)
{


    ui->setupUi(this);
    ui->asiakasnro->setText(username); //tähän asiakastiedot, kortin numero?
    timer2 = new QTimer(this); //luodaan tässä se ajastin että heittää ulos jos ei tietyn ajan sisään tee jotain
    connect(timer2, SIGNAL(timeout()), this, SLOT(ajastin2())); //timerin yhistäminen
            //timer2->start(1000);
    ui->muusummaedit->setPlaceholderText("Syötä muu summa esim. 45");
}

nosto::~nosto()
{
    delete ui;
}

void nosto::paivitanosto(int, QString user)
{
    //aika=0;
    username=user;
    ui->asiakasnro->setText(username);

    QJsonObject jsonObj;
       jsonObj.insert("amount",amount);


       QString site_url=myUrl::getBaseUrl()+"/account/withdraw/"+username;
       QNetworkRequest request((site_url));
       request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

       qDebug()<<site_url;
       //WEBTOKEN ALKU

       request.setRawHeader(QByteArray("Authorization"),("Bearer "+webtoken));
       //WEBTOKEN LOPPU

       updateManager = new QNetworkAccessManager(this);
       connect(updateManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(nostoSlot(QNetworkReply*)));

       reply = updateManager->put(request, QJsonDocument(jsonObj).toJson());

}

const QByteArray &nosto::getWebtoken() const
{
    return webtoken;
}

void nosto::setWebtoken(const QByteArray &newWebtoken)
{
    webtoken = newWebtoken;
}

void nosto::tilintyyppi(int valinta)
{
    accounttype=valinta;
}

void nosto::paivitasaldo(QString user)
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
    //bool ok;
    //saldo=Saldoikkuna.tilinsaldo.toInt(&ok, 10);

}

void nosto::on_alkuun_clicked()
{
    timer2->stop();
    emit PalaaKotinayttoon(); //nostotapahtumien ikkunasta takaisin aloitusnäyttöön
}


void nosto::on_kakskyt_clicked()
{   //tarkista onko automaatissa rahhaa
    //tarkista tililtä onko rahhaa
    timer2->stop();
    aika = 0;
    timer2->start();
    amount = 20;
    qDebug()<< saldo;
    if(saldo<amount && accounttype=="2") //jos tilin saldo on pienempi kuin nostettava raha ja tilin tyyppi on debit
    {QMessageBox::critical(this, "Nosto ei onnistu", "Tili ei voi mennä miinukselle");
    }
    else{
        QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 20 euroa");
        this->paivitanosto(amount,username);
        amount=0;
    }
}


void nosto::on_nelkyt_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    amount = 40;
    if(saldo<amount && accounttype=="2") //jos tilin saldo on pienempi kuin nostettava raha ja tilin tyyppi on debit
    {QMessageBox::critical(this, "Nosto ei onnistu", "Tili ei voi mennä miinukselle");
    }
    else{
        QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 40 euroa");
        this->paivitanosto(amount,username);
        amount=0;
    }
}


void nosto::on_kuuskyt_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    amount = 60;
    if(saldo<amount && accounttype=="2") //jos tilin saldo on pienempi kuin nostettava raha ja tilin tyyppi on debit
    {QMessageBox::critical(this, "Nosto ei onnistu", "Tili ei voi mennä miinukselle");
    }
    else{
        QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 60 euroa");
        this->paivitanosto(amount,username);
        amount=0;
    }

}


void nosto::on_sata_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    amount = 100;
    if(saldo<amount && accounttype=="2") //jos tilin saldo on pienempi kuin nostettava raha ja tilin tyyppi on debit
    {QMessageBox::critical(this, "Nosto ei onnistu", "Tili ei voi mennä miinukselle");
    }
    else{
        QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 100 euroa");
        this->paivitanosto(amount,username);
         amount=0;
    }
}


void nosto::on_kakssata_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    //QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 200 euroa");
    amount = 200;
    if(saldo<amount && accounttype=="2") //jos tilin saldo on pienempi kuin nostettava raha ja tilin tyyppi on debit
    {QMessageBox::critical(this, "Nosto ei onnistu", "Tili ei voi mennä miinukselle");
    }
    else{
        QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 200 euroa");
        this->paivitanosto(amount,username);
         amount=0;
    }
}


void nosto::on_viissata_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    //QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 500 euroa");
    amount = 500;
    if(saldo<amount && accounttype=="2") //jos tilin saldo on pienempi kuin nostettava raha ja tilin tyyppi on debit
    {QMessageBox::critical(this, "Nosto ei onnistu", "Tili ei voi mennä miinukselle");
    }
    else{
        QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 500 euroa");
        this->paivitanosto(amount,username);
        amount=0;
    }
}

void nosto::ajastin2()
{
    aika ++; //lisätään kuluvaa aikaa
    if(aika == 30){
        emit PalaaKotinayttoon();
    }
}

void nosto::nostoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    //if(response_data== "true" && amount!=0){
     // QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin euroa");
   // }
//if(response_data=="false"){
    //QMessageBox::information(this, "Nosto epäonnistui", "Tililtäsi nostettiin 0 euroa");
//}
//else{
   // amount=0;
    reply->deleteLater();
    updateManager->deleteLater();
//}
}

void nosto::on_muusumma_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QValidator *validator = new QIntValidator(0, 999, this);
    QLineEdit *edit = new QLineEdit(this);

    // the edit lineedit will only accept integers between 0 and 999
    edit->setValidator(validator);
    muusumma=ui->muusummaedit->text();
    bool ok;
    amount=muusumma.toInt(&ok, 10);
    if(saldo<amount && accounttype==2) //jos tilin saldo on pienempi kuin nostettava raha ja tilin tyyppi on debit
    {QMessageBox::critical(this, "Nosto ei onnistu", "Tili ei voi mennä miinukselle");
    }
    else{
        QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin massit");
        this->paivitanosto(amount,username);
    }

}

void nosto::saldoslot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();


    foreach (const QJsonValue &value, json_array) { //vääntää json:in QStringiksi
        QJsonObject json_obj = value.toObject();
        tilinsaldo+=QString::number(json_obj["saldo"].toInt());
    }
    bool ok;
    saldo=tilinsaldo.toInt(&ok, 10);

    reply->deleteLater();
    getManager->deleteLater();
}

