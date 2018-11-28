#ifndef CLIMATEMPO_H
#define CLIMATEMPO_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

namespace Ui {
class ClimaTempo;
}

class ClimaTempo : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClimaTempo(QWidget *parent = nullptr);
    ~ClimaTempo();

public slots:
    void atualizaTable();
    void abrirConexao();
    void fecharConexao();
    void select();
    void configurarSerial();
    void lerSerial();
    void atualizaLeitura();
    char itoc(int i);
    void itoa(int i, char s[]);
    void retornaMenor(QString opcao);
    void retornaMaior(QString opcao);
    void media(QString opcao);

private slots:
    void on_btn_media_clicked();

    void on_btn_menor_clicked();

    void on_btn_maior_clicked();

private:
    Ui::ClimaTempo *ui;
    QSqlDatabase database;
    QTimer *atualizaTableView, *atualizaMedicao;
    QSerialPort serial;
    QMessageBox msg;
    QString serialBuffer;
    QString parsed_data;
    QByteArray serialData;
    double valor;
};

#endif // CLIMATEMPO_H
