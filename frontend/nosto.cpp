#include "nosto.h"
#include "ui_nosto.h"
#include <QMessageBox>

nosto::nosto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nosto)
{
    ui->setupUi(this);
    ui->asiakasnro->setText("0004"); //tähän asiakastiedot, kortin numero?
}

nosto::~nosto()
{
    delete ui;
}

void nosto::on_alkuun_clicked()
{
  emit PalaaKotinayttoon(); //nostotapahtumien ikkunasta takaisin aloitusnäyttöön
}


void nosto::on_kakskyt_clicked()
{
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 20 euroa"); //näyttöön tulee ilmoitus noston onnistumisesta/epäonnistumisesta
}


void nosto::on_nelkyt_clicked()
{
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 40 euroa");
}


void nosto::on_kuuskyt_clicked()
{
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 60 euroa");
}


void nosto::on_sata_clicked()
{
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 100 euroa");
}


void nosto::on_kakssata_clicked()
{
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 200 euroa");
}


void nosto::on_viissata_clicked()
{
    QMessageBox::about(this, "Nosto onnistui", "Tililtäsi nostettiin 500 euroa");
}

