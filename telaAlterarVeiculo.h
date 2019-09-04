#ifndef TELAALTERARVEICULO_H
#define TELAALTERARVEICULO_H

#include <QDialog>
#include<veiculopersistencia.h>
#include<QFileDialog>
#include<QMessageBox>
#include<modelopersistencia.h>
#include<marcapersistencia.h>

namespace Ui {
class TelaAlterarVeiculo;
}

class TelaAlterarVeiculo : public QDialog
{
    Q_OBJECT

public:
    explicit TelaAlterarVeiculo(QWidget *parent = nullptr);
    ~TelaAlterarVeiculo();

private slots:
    void on_pushButtonInserirImagem_clicked();

    void on_pushButtonCancelar_clicked();

    void on_pushButtonAlterar_clicked();

private:
    Ui::TelaAlterarVeiculo *ui;

    bool cancelou;

    QString caminhoArquivoImagem;

    void colocarDados();

    void buscarModelos();
};

#endif // TELAALTERARVEICULO_H
