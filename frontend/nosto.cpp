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

   /* QString site_url="http://localhost:3000/card/"; tässä kötösteltyn' jo sitä miten se ottaa sen webtokenin mutta en tienny osotetta
    QNetworkRequest request((site_url));

    //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU*/
}

const QByteArray &nosto::getWebtoken() const
{
    return webtoken;
}

void nosto::setWebtoken(const QByteArray &newWebtoken)
{
 webtoken = newWebtoken;
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
    QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 20 euroa"); //näyttöön tulee ilmoitus noston onnistumisesta/epäonnistumisesta
    amount = 20;
        this->paivitanosto(amount,username);
}


void nosto::on_nelkyt_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 40 euroa");
    amount = 40;
        this->paivitanosto(amount,username);
}


void nosto::on_kuuskyt_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 60 euroa");
    amount = 60;
        this->paivitanosto(amount,username);
}


void nosto::on_sata_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 100 euroa");
    amount = 100;
        this->paivitanosto(amount,username);
}


void nosto::on_kakssata_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 200 euroa");
    amount = 200;
        this->paivitanosto(amount,username);
}


void nosto::on_viissata_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin 500 euroa");
    amount = 500;
        this->paivitanosto(amount,username);
}

void nosto::ajastin2()
{
    qDebug() <<"update2..";
    aika ++; //lisätään kuluvaa aikaa
   // qDebug() <<aika;
    if(aika == 30){
        emit PalaaKotinayttoon();
    }
}

void nosto::nostoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();


    reply->deleteLater();
    updateManager->deleteLater();

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
    this->paivitanosto(amount, username);
    qDebug()<<amount;
    QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin euroa"); //tuohon väliin vielä amount muuttujan arvo

}

