#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <nosto.h>
#include <saldo.h>
#include <tilitapahtumat.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_seuraava_clicked();

    void on_seuraava_2_clicked();

    void on_nostarahaa_clicked();

    void on_kirjaudu_ulos_clicked();

    void palaaAlkuun();

    void on_tilitapahtumat_clicked();

    void on_naytasaldo_clicked();

private:
    Ui::MainWindow *ui;
    nosto Nostoikkuna;//tällä pääsee nostotapahtumien ikkunaan
    saldo Saldoikkuna;
    tilitapahtumat Tilitapahtumaikkuna;
};
#endif // MAINWINDOW_H
