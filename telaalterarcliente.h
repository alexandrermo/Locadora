#ifndef TELAALTERARCLIENTE_H
#define TELAALTERARCLIENTE_H

#include <QDialog>
#include<clientepersistencia.h>
#include<QMessageBox>
#include<QFileDialog>

namespace Ui {
class TelaAlterarCliente;
}

class TelaAlterarCliente : public QDialog
{
    Q_OBJECT

public:
    explicit TelaAlterarCliente(QWidget *parent = nullptr);
    ~TelaAlterarCliente();

private slots:
    void on_pushButtonAlterar_clicked();

    void on_pushButtonInserirImagem_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::TelaAlterarCliente *ui;

    QString caminhoArquivoImagemTeste;
    void colocarDados();

    bool cancelou;
};

#endif // TELAALTERARCLIENTE_H
