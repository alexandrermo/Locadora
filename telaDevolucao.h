#ifndef TELADEVOLUCAO_H
#define TELADEVOLUCAO_H

#include <QDialog>
#include<clientepersistencia.h>
#include<veiculopersistencia.h>
#include<locacaoPersistencia.h>
#include<modelopersistencia.h>
#include<marcapersistencia.h>
#include<QMessageBox>

namespace Ui {
class TelaDevolucao;
}

class TelaDevolucao : public QDialog
{
    Q_OBJECT

public:
    explicit TelaDevolucao(QWidget *parent = nullptr);
    ~TelaDevolucao();

private slots:
    void on_pushButtonCancelar_clicked();

    void on_pushButtonMostrarLocacoesEmAberto_clicked();

    void on_pushButtonCalcularValorReal_clicked();

    void on_pushButtonConcluirDevolucao_clicked();

private:
    Ui::TelaDevolucao *ui;

    void buscarCpfs();
    void listarLocacoesEmAberto();
};

#endif // TELADEVOLUCAO_H
