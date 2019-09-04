#ifndef TELAGERENCIARCLIENTES_H
#define TELAGERENCIARCLIENTES_H

#include <QDialog>
#include<clientepersistencia.h>
#include<list>
#include<telacadastrarcliente.h>
#include<telaalterarcliente.h>

namespace Ui {
class TelaGerenciarClientes;
}

class TelaGerenciarClientes : public QDialog
{
    Q_OBJECT

public:
    explicit TelaGerenciarClientes(QWidget *parent = nullptr);
    ~TelaGerenciarClientes();

private slots:
    void on_pushButtonCadastrarNovoCliente_clicked();

    void on_pushButtonApagar_clicked();

    void on_pushButtonAlterar_clicked();

    void on_pushButtonVoltar_clicked();

    void on_pushButtonOrdenarPorNome_clicked();

    void on_pushButtonOrdenarPorRelacionamento_clicked();

private:
    Ui::TelaGerenciarClientes *ui;

    void listarTabela(QString ordernar="nome");

    void alterar(QString cpf, int linha);
};

#endif // TELAGERENCIARCLIENTES_H
