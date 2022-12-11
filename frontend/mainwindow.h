#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <nosto.h>
#include <saldo.h>
#include <tilitapahtumat.h>
#include <QTimer>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    const QByteArray &getWebToken() const;
    void setWebToken(const QByteArray &newWebToken);
    void tilityyppi(QString);
    int valinta;


private slots:

    void on_seuraava_clicked();

    void on_seuraava_2_clicked();

    void on_nostarahaa_clicked();

    void on_kirjaudu_ulos_clicked();

    void palaaAlkuun();

    void on_tilitapahtumat_clicked();

    void on_naytasaldo_clicked();
    void loginSlot (QNetworkReply *reply);
    void tilityyppiSlot(QNetworkReply *reply2);

public slots:
    void ajastin();


private:
    Ui::MainWindow *ui;
    nosto Nostoikkuna;
    saldo Saldoikkuna;
    tilitapahtumat Tilitapahtumaikkuna;
    int asiakasnumero;
    QTimer *timer;
    int aika;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *getType;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QByteArray response_data;
    QByteArray response_data2;
    QString username;
    int amount;
    QString valitsetili;
    QByteArray token;

};
#endif // MAINWINDOW_H
