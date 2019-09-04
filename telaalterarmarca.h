#ifndef TELAALTERARMARCA_H
#define TELAALTERARMARCA_H

#include <QDialog>

namespace Ui {
class telaAlterarMarca;
}

class telaAlterarMarca : public QDialog
{
    Q_OBJECT

public:
    explicit telaAlterarMarca(QWidget *parent = nullptr);
    ~telaAlterarMarca();

private slots:
    void on_pushButtonAlterar_clicked();

    void on_pushButtonIncluirFoto_clicked();

    void on_pushButtonVoltar_clicked();

private:
    Ui::telaAlterarMarca *ui;
    QString caminhoArquivoImagemTeste;
    void colocarDados();

    bool cancelou;
};

#endif // TELAALTERARMARCA_H
