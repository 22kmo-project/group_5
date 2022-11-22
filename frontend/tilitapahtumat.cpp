#include "tilitapahtumat.h"
#include "ui_tilitapahtumat.h"

tilitapahtumat::tilitapahtumat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tilitapahtumat)
{
    ui->setupUi(this);
    ui->asiakasnro->setText("0004"); //tähän asiakkaan tiedot, kortin numero?
    ui->tilitapahtumabox->setText("tähän tullee rajusti sitten niitä tilitapahtumia, tässä pittää sitten tarkastella sitä rivitystä varmaankin että ei tule pötköön");
}

tilitapahtumat::~tilitapahtumat()
{
    delete ui;
}

void tilitapahtumat::on_alkuun_3_clicked()
{
    emit PalaaKotinayttoon(); //tilitapahtumanäkymästä aloitusnäyttöön
}

