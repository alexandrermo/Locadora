#ifndef TELACADASTRARCLIENTE_H
#define TELACADASTRARCLIENTE_H

#include <QDialog>
#include<QFileDialog>
#include<clientepersistencia.h>
#include<QMessageBox>

namespace Ui {
class TelaCadastrarCliente;
}

class TelaCadastrarCliente : public QDialog
{
    Q_OBJECT

public:
    explicit TelaCadastrarCliente(QWidget *parent = nullptr);
    ~TelaCadastrarCliente();

private slots:
    void on_pushButtonInserirImagem_clicked();

    void on_pushButtonIncluir_clicked();

    void on_pushButtonVoltar_clicked();

private:
    Ui::TelaCadastrarCliente *ui;

    QString caminhoArquivoImagemTeste;

    void limparTela();
};

#endif // TELACADASTRARCLIENTE_H
