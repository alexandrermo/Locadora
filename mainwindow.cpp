#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<telagerenciarmarca.h>
#include<telagerenciarmodelo.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonGerenciarClientes_clicked()
{
    TelaGerenciarClientes TelaGerenciarClientes;

    TelaGerenciarClientes.setModal(true);
    TelaGerenciarClientes.exec();
}


void MainWindow::on_pushButtonGerenciarVeiculos_clicked()
{
    TelaGerenciarVeiculo TelaGerenciarVeiculo;

    TelaGerenciarVeiculo.setModal(true);
    TelaGerenciarVeiculo.exec();
}

void MainWindow::on_pushButtonGerenciarMarcas_clicked()
{
    telaGerenciarMarca telaGerenciarMarca;

    telaGerenciarMarca.setModal(true);
    telaGerenciarMarca.exec();
}

void MainWindow::on_pushButtonGerenciarModelos_clicked()
{
    telagerenciarmodelo telagerenciarModelo;
    telagerenciarModelo.setModal(true);
    telagerenciarModelo.exec();
}

void MainWindow::on_pushButtonAlocacao_clicked()
{
    TelaLocacao telaLocacao;
    telaLocacao.setModal(true);
    telaLocacao.exec();
}

void MainWindow::on_pushButtonDevolucao_clicked()
{
    TelaDevolucao telaDevolucao;
    telaDevolucao.setModal(true);
    telaDevolucao.exec();
}


void MainWindow::on_pushButtonHistoricooDeLocacoes_clicked()
{
    TelaHistoricooLocacoes telaHistoricoLocacoes;
    telaHistoricoLocacoes.setModal(true);
    telaHistoricoLocacoes.exec();
}
