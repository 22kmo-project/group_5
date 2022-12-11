#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myurl.h"
#include <QStackedWidget>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    valinta=0;
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(3, &Nostoikkuna); //tässä asetan nostotapahtumien index numeroksi 3
    ui->stackedWidget->insertWidget(4, &Saldoikkuna); //saldolle index 4
    ui->stackedWidget->insertWidget(5, &Tilitapahtumaikkuna); //tilitapahtumille index 5
    //ui->stackedWidget->addWidget()

    ui->stackedWidget->setCurrentIndex(0); //tällä alustan ohjelman aloittamaan aina alusta asti
    connect(&Nostoikkuna, SIGNAL(PalaaKotinayttoon()), this, SLOT(palaaAlkuun())); //yhdistää palaa napin nostotapahtumien näkymässä
    connect(&Saldoikkuna, SIGNAL(PalaaKotinayttoon()), this, SLOT(palaaAlkuun())); //yhdistää palaa napin saldotapahtumien näkymässä
    connect(&Tilitapahtumaikkuna, SIGNAL(PalaaKotinayttoon()), this, SLOT(palaaAlkuun())); //yhdistää palaa napin tilitapahtumien näkymässä

    timer = new QTimer(this); //luodaan tässä se ajastin että heittää ulos jos ei tietyn ajan sisään tee jotain
    connect(timer, SIGNAL(timeout()), this, SLOT(ajastin())); //timerin yhistäminen




}

MainWindow::~MainWindow()
{
    delete ui;
}

const QByteArray &MainWindow::getWebToken() const
{
    return token;
}


void MainWindow::tilityyppi(QString user2)
{
    //tilityypin valintaa hahmoteltu seuraavaan
    username=user2;
    token=getWebToken();
    QString site_url=myUrl::getBaseUrl()+"/account/"+username;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    getType = new QNetworkAccessManager(this);

    connect(getType, SIGNAL(finished (QNetworkReply*)), this, SLOT(tilityyppiSlot(QNetworkReply*)));

    reply2 = getType->get(request);

}


void MainWindow::on_seuraava_clicked()
{
    username = ui->korttinro->text(); //line edittiin laitettu korttinumero syötetään username muuttujaan
    if(username.length() == 1){
    ui->stackedWidget->setCurrentIndex(1); //jos kortin numero on oikein siirrytään seuraavaan näkymään
    aika = 0; //nollataan kulunut aika
    timer->start(1000); //startataan timer
}
    else{
        ui->virheviesti1->setText("Kortin numero virheellinen"); //jos kortin numero oli väärin niin tulee yläpuolelle virheviesti
        ui->korttinro->clear(); //line edit kohta tyhjennetään
    }
//ui->asiakasnimi->setText(username); //asiakkaan nimi aloitusnäytölle
}


void MainWindow::on_seuraava_2_clicked()
{
    QString password = ui->korttinro_2->text();

    QJsonObject jsonObj;
        jsonObj.insert("idcard",username);
        jsonObj.insert("password",password);

        QString site_url="http://localhost:3000/login";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


        loginManager = new QNetworkAccessManager(this);
        connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

        reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());


        ui->asiakasnimi->setText(username); //asiakkaan nimi aloitusnäytölle






}


void MainWindow::on_nostarahaa_clicked()
{
    amount=0;
    Nostoikkuna.setWebtoken(response_data);
    Nostoikkuna.paivitasaldo(username);
    Nostoikkuna.timer2->start(1000); //starttaa nostoikkunalle oman timerin
    ui->stackedWidget->setCurrentIndex(3); //aloitusnäytöstä nostotapahtumanäkymään
    timer->stop(); //tällä rimpsulla saadaan joka näkymälle aloittamaan 30 sekunnin aika alusta(aikakatkaisu)
    aika = 0;
    //timer->start();
}


void MainWindow::on_kirjaudu_ulos_clicked()
{
    timer->stop();
    if(ui->stackedWidget->currentIndex()== 0){
       this->close();
    }
    else {
    ui->stackedWidget->setCurrentIndex(0); /*tässä vaiheessa kirjaudu ulos napista ohjelma siirtyy kirjautumisnäkymään muissa näkymissä
                                            ja kirjautumisnäkymässä sulkee ohjelman, lisätään myöhemmin tietokannan sulkemiset jne */
    }
}

void MainWindow::palaaAlkuun()
{
    ui->stackedWidget->setCurrentIndex(2); //palauttaa aloitusnäyttöön kaikilta näkymiltä
    timer->stop();
    aika = 0;
    timer->start();
}


void MainWindow::on_tilitapahtumat_clicked()
{
    Tilitapahtumaikkuna.setWebToken(response_data); //homma webtokenin
    Tilitapahtumaikkuna.paivitatilitapahtumat(username); //päivittää tilitapahtumat ettei näytä jotain vanhaa tietoa esim ohjelman käynnistykseltä saakka

    ui->stackedWidget->setCurrentIndex(5); //aloitusnäytöstä tilitapahtumien näkymään
    timer->stop();
    aika = 0;
    timer->start();
}


void MainWindow::on_naytasaldo_clicked()
{
    Saldoikkuna.setWebtoken(response_data); //homma webtokenin saldoon sisälle
    Saldoikkuna.paivitasaldo(username); //päivittää saldonäkymän napauttaessa
    Saldoikkuna.paivitatilitapahtumat(username); //päivittää tilitapahtumat

    ui->stackedWidget->setCurrentIndex(4); //aloitusnäytöstä saldon näkymään
    timer->stop();
    aika = 0;
    timer->start();
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
response_data=reply->readAll();
qDebug()<<response_data;
int test=QString::compare(response_data,"false");
    qDebug()<<test;

if(response_data.length()==0){
        ui->virheviesti2->setText("Palvelin ei vastaa");
    }
    else {
        if(QString::compare(response_data,"-4078")==0){
            ui->virheviesti2->setText("Virhe tietokanta yhteydessä");
        }
        else {
            if(test==0){
                ui->korttinro_2->clear();
                ui->virheviesti2->setText("Tunnus ja salasana eivät täsmää");
            }
            else {
                setWebToken("Bearer "+response_data);
                 tilityyppi(username);
                 //qDebug()<<valitsetili;
                 //if(valitsetili>0){
                     //QMessageBox::question(this, "Valitse tilityyppi", "Valitse käytettävä tilityyppi" );
                 //}

                //ui->stackedWidget->setCurrentIndex(2); // jos tunnusluku oli oikein niin siirrytään aloitusnäyttöön
                aika = 0; //nollataan kulunut aika
                timer->start(1000); //startataan timer
            }
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

void MainWindow::tilityyppiSlot(QNetworkReply *reply2)
{
    response_data2=reply2->readAll();
    //qDebug()<<response_data2;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data2);
    QJsonArray json_array = json_doc.array();

    QString tilityyppi;
    foreach (const QJsonValue &value, json_array) { //vääntää json:in QStringiksi
        QJsonObject json_obj = value.toObject();
        tilityyppi=QString::number(json_obj["accounttype"].toInt());
    }
    valitsetili=tilityyppi;
    //qDebug()<<"tilin tyyppi on";
    qDebug()<<valitsetili;
    if(valitsetili>"0"){
        QMessageBox *msgBox;
        msgBox = new QMessageBox(this);
        msgBox->setText("Valitse tilityyppi");
        msgBox->setIcon(QMessageBox::Question);
        msgBox->setWindowTitle("Valitse tilityyppi");
        msgBox->setStyleSheet("background-color:#48b76a;");
        QPushButton *creditButton = msgBox->addButton(tr("Credit"), QMessageBox::ActionRole);
        QPushButton *debitButton = msgBox->addButton(tr("Debit"), QMessageBox::ActionRole);
        creditButton->setObjectName("crd");

        msgBox->exec();

        if (msgBox->clickedButton() == creditButton) {
            valinta=1;
            ui->stackedWidget->setCurrentIndex(2);
                Nostoikkuna.tilintyyppi(valinta);
        } else if (msgBox->clickedButton() == debitButton) {
            valinta=2;
            ui->stackedWidget->setCurrentIndex(2);
                Nostoikkuna.tilintyyppi(valinta);
        }
        //QMessageBox::information(this, "Valitse tilityyppi","Valitse käytettävä tilityyppi");
    }
    else{
        valinta=2;
        ui->stackedWidget->setCurrentIndex(2);
            Nostoikkuna.tilintyyppi(valinta);
    }
}


void MainWindow::ajastin()
{
   // qDebug() <<"update..";
    aika ++; //lisätään kuluvaa aikaa
   // qDebug() <<aika;

    if(ui->stackedWidget->currentIndex()== 1 && aika > 10){
        ui->stackedWidget->setCurrentIndex(0);
    timer->stop(); //kun oot ollu kirjautumisnäkymässä määrätyn ajan painamatta mitään niin nakataan alkuun ja timer nollataan
    }
    if (ui->stackedWidget->currentIndex()==1 && aika > 30){
        ui->stackedWidget->setCurrentIndex(0);
        timer->stop(); //kun oot ollu aloitusnäytössä määrätyn ajan painamatta mitään niin nakataan kirjautumisnäkymään ja timer nollataan
    }
    if(ui->stackedWidget->currentIndex()>2 && aika > 10){
        ui->stackedWidget->setCurrentIndex(2);
        timer->stop();
        aika = 0;
        timer->start();//kun oot ollu saldo, tilitapahtuma tai nostonäkymässä määrätyn ajan niin nakataa aloitusnäyttöön
    }
}


void MainWindow::setWebToken(const QByteArray &newWebToken)
{
    token = newWebToken;
}
