#ifndef TELALOCACAO_H
#define TELALOCACAO_H

#include <QDialog>
#include<clientepersistencia.h>
#include<modelopersistencia.h>
#include<veiculopersistencia.h>
#include<marcapersistencia.h>
#include<QMessageBox>
#include<time.h>
#include<data.h>
#include<locacaoPersistencia.h>


namespace Ui {
class TelaLocacao;
}

class TelaLocacao : public QDialog
{
    Q_OBJECT

public:
    explicit TelaLocacao(QWidget *parent = nullptr);
    ~TelaLocacao();

private slots:
    void on_pushButtonCancelar_clicked();

    void on_pushButtonCalcularValor_clicked();

    void on_pushButtonConcluirLocacao_clicked();

    void on_pushButtonOrdenarPorModelo_clicked();

    void on_pushButtoOrdenarPorMarca_clicked();

    void on_pushButtonOrdenarPorValor_clicked();

    void on_pushButtonOrdenarPorQuilometragem_clicked();

private:
    Ui::TelaLocacao *ui;

    void listarVeiculosDisponiveis(QString ordenar="Modelo");
    void buscarCpfs();
};

#endif // TELALOCACAO_H
