#ifndef BANCODEDADOS_H
#define BANCODEDADOS_H

#include <QMessageBox>
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <string>
#include "climatempo.h"

class BancoDeDados
{
public:
    BancoDeDados();
    void abrirConexao();
    void fecharConexao();
    void select();
private:
    QSqlDatabase database;
};

#endif // BANCODEDADOS_H

