#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<telagerenciarclientes.h>
#include <QMainWindow>
#include<telagerenciarveiculo.h>
#include<telaLocacao.h>
#include<telaDevolucao.h>
#include<TelaHistoricooLocacoes.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonGerenciarClientes_clicked();

    void on_pushButtonGerenciarVeiculos_clicked();

    void on_pushButtonGerenciarMarcas_clicked();

    void on_pushButtonGerenciarModelos_clicked();

    void on_pushButtonAlocacao_clicked();

    void on_pushButtonDevolucao_clicked();

    void on_pushButtonHistoricooDeLocacoes_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
