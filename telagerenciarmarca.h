#ifndef TELAGERENCIARMARCA_H
#define TELAGERENCIARMARCA_H
#include<telacadastrarmarca.h>
#include <QDialog>
#include<id.h>
namespace Ui {
class telaGerenciarMarca;
}

class telaGerenciarMarca : public QDialog
{
    Q_OBJECT

public:
    explicit telaGerenciarMarca(QWidget *parent = nullptr);
    ~telaGerenciarMarca();

private slots:
    void on_pushButtonCadastrarMarca_clicked();

    void on_pushButtonAlterar_clicked();

     void alterar(ar::Id id, int linha);
     void on_pushButtonDeletar_clicked();

     void on_pushButtonVoltar_clicked();

private:
    Ui::telaGerenciarMarca *ui;

    void listarTabela();
};

#endif // TELAGERENCIARMARCA_H
