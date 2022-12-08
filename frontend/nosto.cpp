#include "nosto.h"
#include "ui_nosto.h"
#include <QMessageBox>
#include <QDebug>

nosto::nosto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nosto)
{
    ui->setupUi(this);
    ui->asiakasnro->setText("0004"); //tähän asiakastiedot, kortin numero?
    timer2 = new QTimer(this); //luodaan tässä se ajastin että heittää ulos jos ei tietyn ajan sisään tee jotain
    connect(timer2, SIGNAL(timeout()), this, SLOT(ajastin2())); //timerin yhistäminen
            //timer2->start(1000);

    ui->muusummaedit->setPlaceholderText("Syötä summa esim. 45");
}

nosto::~nosto()
{
    delete ui;
}

void nosto::paivitanosto()
{
    aika=0;

   /* QString site_url="http://localhost:3000/card/"; tässä kötösteltyn' jo sitä miten se ottaa sen webtokenin mutta en tienny osotetta
    QNetworkRequest request((site_url));

    //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU*/
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
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 20 euroa"); //näyttöön tulee ilmoitus noston onnistumisesta/epäonnistumisesta
}


void nosto::on_nelkyt_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 40 euroa");
}


void nosto::on_kuuskyt_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 60 euroa");
}


void nosto::on_sata_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 100 euroa");
}


void nosto::on_kakssata_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 200 euroa");
}


void nosto::on_viissata_clicked()
{
    timer2->stop();
    aika = 0;
    timer2->start();
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 500 euroa");
}

void nosto::ajastin2()
{
    qDebug() <<"update2..";
    aika ++; //lisätään kuluvaa aikaa
    qDebug() <<aika;
    if(aika == 30){
        emit PalaaKotinayttoon();
    }
   }

void nosto::on_muusumma_clicked()
{
//lue line editin summa
    //poista line editin määräämä summa tililtä
}

