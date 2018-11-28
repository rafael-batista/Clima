#include "bancodedados.h"

BancoDeDados::BancoDeDados()
{
    abrirConexao();
}

void BancoDeDados::abrirConexao(){
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setDatabaseName("Clima");
    database.setHostName("localhost");
    database.setPort(3306);
    database.setUserName("root");
    database.setPassword("rootroot");

    if(database.open())
        qDebug() << "deu certo";
    else
        qDebug() << "deu errado";
}

void BancoDeDados::fecharConexao(){
    if(database.open())
        database.close();
    else
        qDebug() << "Não havia conexão estabelecida com o banco de dados";
}

void BancoDeDados::select(){
    if(!database.open()){
        abrirConexao();
    } else if (database.open()) {
        QString select = "SELECT * FROM Leituras";
        QSqlQueryModel * model = new QSqlQueryModel();
        QSqlQuery * query = new QSqlQuery(database);
        query->prepare(select);
        query->exec();
        model->setQuery(*query);
        ui->tableView->setModel(model);
    }
}


