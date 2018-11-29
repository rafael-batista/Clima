#include "climatempo.h"
#include "ui_climatempo.h"

ClimaTempo::ClimaTempo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClimaTempo)
{
    ui->setupUi(this);

    abrirConexao();
    select();
    configurarSerial();
    atualizaTable();
    atualizaLeitura();

    if(serial.isOpen()){
        qDebug() << "Serial está aberta";
    }

}

ClimaTempo::~ClimaTempo()
{
    delete ui;
    fecharConexao();
    atualizaTableView->stop();

    if(serial.isOpen()){
        serial.close();
        qDebug() << "Porta serial fechada pelo destrutor com sucesso!";
    }else {
        qDebug() << "Porta não estava aberta...";
    }

}

void ClimaTempo::atualizaTable(){
    atualizaTableView = new QTimer(this);
    connect(atualizaTableView,SIGNAL(timeout()),this,SLOT(select()));
    atualizaTableView->start(2000);
}

void ClimaTempo::atualizaLeitura(){
    atualizaMedicao = new QTimer(this);
    connect(atualizaMedicao,SIGNAL(timeout()),this,SLOT(lerSerial()));
    atualizaMedicao->start(3000);
}

void ClimaTempo::abrirConexao(){
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

void ClimaTempo::fecharConexao(){
    if(database.open())
        database.close();
    else
        qDebug() << "Não havia conexão estabelecida com o banco de dados";
}

void ClimaTempo::select(){
    if(!database.open()){
        abrirConexao();
    } else if (database.open()) {
        QString select = "SELECT * FROM Leituras ORDER BY Id DESC";
        QSqlQueryModel * model = new QSqlQueryModel();
        QSqlQuery * query = new QSqlQuery(database);
        query->prepare(select);
        query->exec();
        model->setQuery(*query);
        ui->tableView->setModel(model);
    }
}

void ClimaTempo::configurarSerial(){
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        qDebug() << "Name : " << info.portName();
    }

    serial.setPortName("cu.usbmodem14201");
    serial.setBaudRate(QSerialPort::Baud9600);
    if(serial.open(QIODevice::ReadWrite)){
        msg.setText("Porta serial \"cu.usbmodem14201\" aberta com sucesso!");
        msg.exec();
    } else {
        msg.setText("Erro na abertura da porta serial");
        msg.exec();
    }
}

void ClimaTempo::lerSerial(){
    char buff[1024], buffer_temperatura[10], buffer_umidade[10];
    int valor, temperatura, umidade;
    qint64 linTam = serial.readLine(buff, sizeof(buff));

    valor = atoi(buff);
    temperatura = valor/100;
    umidade = valor%100;

    itoa(temperatura,buffer_temperatura);
    itoa(umidade, buffer_umidade);

    if(linTam != 1){
        qDebug() << "Temperatura: "<< temperatura;
        qDebug() << "Umidade: "<< umidade;
    }

    if (temperatura < 70 && umidade < 101){
        qDebug() << "Deu boa, manda para o banco";
        if(database.isOpen()){
            qDebug() << "conexao aberta";

            QString strQry = "INSERT INTO Leituras (Temperatura, Umidade) VALUES (";
            strQry = strQry + buffer_temperatura + ",";
            strQry = strQry + buffer_umidade + ");";

            QSqlQuery * query = new QSqlQuery(database);
            query->prepare(strQry);
            if(query->exec()){
                qDebug() << "Registro inserido com sucesso";
            } else {
                qDebug() << strQry;
                qDebug() << "Não foi possível inserir o registro";
            }
        }
    }
}

char ClimaTempo::itoc(int i) {
     switch (i) {
            case 0: return '0';
            case 1: return '1';
            case 2: return '2';
            case 3: return '3';
            case 4: return '4';
            case 5: return '5';
            case 6: return '6';
            case 7: return '7';
            case 8: return '8';
            case 9: return '9';
     }
}

void ClimaTempo::itoa(int i, char s[]) {
    int m10 = 1;
    int qt = 0;
    int n;

    while (((int)(i/m10))>0)
        m10 *= 10;

    m10 /= 10;

    while (m10>0) {
        n = (int)(i/m10) - ((int)(i/(m10*10))*10);
        s[qt] = itoc(n);
        m10 /= 10;
        qt++;
    }
    s[qt] = '\0';
}

void ClimaTempo::retornaMenor(QString opcao){
    if(!database.open()){
        abrirConexao();
    } else if (database.open()) {
        QString select = "SELECT * FROM Leituras WHERE ";
        select = select + opcao + " = (SELECT MIN(";
        select = select + opcao + ") FROM Leituras);";

        QSqlQueryModel * model = new QSqlQueryModel();
        QSqlQuery * query = new QSqlQuery(database);
        query->prepare(select);
        query->exec();
        model->setQuery(*query);
        ui->tableView_2->setModel(model);

        ui->lbl_resultado->setText("Menor valor de "+opcao);
    }
}

void ClimaTempo::retornaMaior(QString opcao){
    if(!database.open()){
        abrirConexao();
    } else if (database.open()) {
        QString select = "SELECT * FROM Leituras WHERE ";
        select = select + opcao + " = (SELECT MAX(";
        select = select + opcao + ") FROM Leituras);";

        QSqlQueryModel * model = new QSqlQueryModel();
        QSqlQuery * query = new QSqlQuery(database);
        query->prepare(select);
        query->exec();
        model->setQuery(*query);
        ui->tableView_2->setModel(model);

        ui->lbl_resultado->setText("Maior valor de "+opcao);
    }
}

void ClimaTempo::media(QString opcao){
    if(!database.open()){
        abrirConexao();
    } else if (database.open()) {
        QString select = "SELECT AVG(";
        select = select + opcao + ") FROM Leituras;";

        QSqlQueryModel * model = new QSqlQueryModel();
        QSqlQuery * query = new QSqlQuery(database);
        query->prepare(select);
        query->exec();
        model->setQuery(*query);
        ui->tableView_2->setModel(model);

        ui->lbl_resultado->setText("Média de "+opcao);
    }
}

void ClimaTempo::on_btn_media_clicked()
{
    if(ui->comboBox->currentText() == "Temperatura"){
        media("Temperatura");
    } else {
        media("Umidade");
    }
}

void ClimaTempo::on_btn_menor_clicked()
{
    if(ui->comboBox->currentText() == "Temperatura"){
        retornaMenor("Temperatura");
    } else {
        retornaMenor("Umidade");
    }
}

void ClimaTempo::on_btn_maior_clicked()
{
    if(ui->comboBox->currentText() == "Temperatura"){
        retornaMaior("Temperatura");
    } else {
        retornaMaior("Umidade");
    }
}
