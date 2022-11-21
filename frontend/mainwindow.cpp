#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(3, &Nostoikkuna); //tässä asetan nostotapahtumien index numeroksi 3
    ui->stackedWidget->insertWidget(4, &Saldoikkuna); //saldolle index 4
    ui->stackedWidget->insertWidget(5, &Tilitapahtumaikkuna); //tilitapahtumille index 5
    //ui->stackedWidget->addWidget()

    ui->stackedWidget->setCurrentIndex(0); //tällä alustan ohjelman aloittamaan aina alusta asti
    connect(&Nostoikkuna, SIGNAL(PalaaKotinayttoon()), this, SLOT(palaaAlkuun())); //yhdistää palaa napin nostotapahtumien ikkunassa
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_seuraava_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_seuraava_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_nostarahaa_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_kirjaudu_ulos_clicked()
{
    this->close(); //tässä vaiheessa tämä vasta sulkee ohjelman, myöhemmin lisätään uloskirjaamisen toiminnot
}

void MainWindow::palaaAlkuun()
{
ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_tilitapahtumat_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_naytasaldo_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

