#include "saldo.h"
#include "ui_saldo.h"

saldo::saldo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::saldo)
{
    ui->setupUi(this);
    ui->asiakasnro->setText("0004"); //tähän asiakkaan tiedot, kortin numero?
    ui->tilitapahtumabox->setText("tähän tullee rajusti sitten niitä tilitapahtumia, tässä pittää sitten tarkastella sitä rivitystä varmaankin että ei tule pötköön");
    ui->tilinsaldo->setText("23 000€"); //tähän haetaan tilin saldo tietokannasta
}

saldo::~saldo()
{
    delete ui;
}

void saldo::paivitasaldo()
{

}

void saldo::on_alkuun_2_clicked()
{
    emit PalaaKotinayttoon(); //saldonäkymästä aloitusnäyttöön
}

