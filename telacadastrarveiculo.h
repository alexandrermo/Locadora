#ifndef TELACADASTRARVEICULO_H
#define TELACADASTRARVEICULO_H

#include <QDialog>
#include<QFileDialog>
#include<QMessageBox>
#include<veiculopersistencia.h>
#include<modelopersistencia.h>

namespace Ui {
class TelaCadastrarVeiculo;
}

class TelaCadastrarVeiculo : public QDialog
{
    Q_OBJECT

public:
    explicit TelaCadastrarVeiculo(QWidget *parent = nullptr);
    ~TelaCadastrarVeiculo();

private slots:
    void on_pushButtonIncluir_clicked();

    void on_pushButtonInserirImagem_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::TelaCadastrarVeiculo *ui;

    QString caminhoArquivoImagemTeste;

    void buscarModelos();
};

#endif // TELACADASTRARVEICULO_H
