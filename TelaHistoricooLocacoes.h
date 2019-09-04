#ifndef TELAHISTORICOOLOCACOES_H
#define TELAHISTORICOOLOCACOES_H

#include <QDialog>
#include<clientepersistencia.h>
#include<locacaoPersistencia.h>
#include<QMessageBox>

namespace Ui {
class TelaHistoricooLocacoes;
}

class TelaHistoricooLocacoes : public QDialog
{
    Q_OBJECT

public:
    explicit TelaHistoricooLocacoes(QWidget *parent = nullptr);
    ~TelaHistoricooLocacoes();

private slots:
    void on_pushButtonVoltar_clicked();

    void on_pushButtonFiltrar_clicked();

    void on_pushButtonRetirarFiltro_clicked();

private:
    Ui::TelaHistoricooLocacoes *ui;

    void listarTabela(QString cpf="0");
    void buscarCpfs();
};

#endif // TELAHISTORICOOLOCACOES_H
