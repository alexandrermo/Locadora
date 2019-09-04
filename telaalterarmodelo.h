#ifndef TELAALTERARMODELO_H
#define TELAALTERARMODELO_H

#include <QDialog>

namespace Ui {
class telaAlterarModelo;
}

class telaAlterarModelo : public QDialog
{
    Q_OBJECT

public:
    explicit telaAlterarModelo(QWidget *parent = nullptr);
    ~telaAlterarModelo();

private slots:
    void on_pushButtonAlterar_clicked();
    QString pesquisaMarcaPorId(int id);
    void on_pushButtonIncluirFoto_clicked();

    void on_pushButtonVoltar_clicked();

private:
    Ui::telaAlterarModelo *ui;
    QString caminhoArquivoImagemTeste;
    bool cancelou;
    void colocarDados();
    int pesquisarNumeroIdporMarca(QString marca);
};

#endif // TELAALTERARMODELO_H
