#ifndef TELAGERENCIARVEICULO_H
#define TELAGERENCIARVEICULO_H

#include <QDialog>
#include<QMessageBox>
#include<veiculopersistencia.h>
#include<telacadastrarveiculo.h>
#include<telaAlterarVeiculo.h>
#include<marcapersistencia.h>

namespace Ui {
class TelaGerenciarVeiculo;
}

class TelaGerenciarVeiculo : public QDialog
{
    Q_OBJECT

public:
    explicit TelaGerenciarVeiculo(QWidget *parent = nullptr);
    ~TelaGerenciarVeiculo();

private slots:
    void on_pushButtonCadastrarNovoVeculo_clicked();

    void on_pushButtonApagar_clicked();

    void on_pushButtonAlterar_clicked();

    void on_pushButtonVoltar_clicked();

private:
    Ui::TelaGerenciarVeiculo *ui;

    void listarTabela();

    void alterar(QString placa,int linha);

};

#endif // TELAGERENCIARVEICULO_H
