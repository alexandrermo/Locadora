#ifndef TELAHISTORICOLOCACOES_H
#define TELAHISTORICOLOCACOES_H

#include <QDialog>
#include<clientepersistencia.h>
#include<locacaoPersistencia.h>
#include<QMessageBox>

namespace Ui {
class telaHistoricoLocacoes;
}

class telaHistoricoLocacoes : public QDialog
{
    Q_OBJECT

public:
    explicit telaHistoricoLocacoes(QWidget *parent = nullptr);
    ~telaHistoricoLocacoes();

private:
    Ui::telaHistoricoLocacoes *ui;

    void listarTabela(QString cpf="0");
    void buscarCpfs();
};

#endif // TELAHISTORICOLOCACOES_H
