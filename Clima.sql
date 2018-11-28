#Criando o banco de dados
CREATE DATABASE Clima;

#Selecionando database
USE Clima;

#Criando as tabelas e os campos do banco de dados ESTOQUE
CREATE TABLE Leituras (
	Id INT AUTO_INCREMENT PRIMARY KEY,
	Temperatura DECIMAL(5,2) NOT NULL,
	Umidade DECIMAL(4,2) NOT NULL,
	Data DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

#Testando a tabela
INSERT INTO
	Leituras (Temperatura, Umidade)
VALUES
	(43, 41),
	(29, 71),
	(32, 31);