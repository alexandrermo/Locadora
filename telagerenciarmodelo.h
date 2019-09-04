#ifndef TELAGERENCIARMODELO_H
#define TELAGERENCIARMODELO_H
#include<id.h>
#include <QDialog>

namespace Ui {
class telagerenciarmodelo;
}

class telagerenciarmodelo : public QDialog
{
    Q_OBJECT

public:
    explicit telagerenciarmodelo(QWidget *parent = nullptr);
    ~telagerenciarmodelo();

private slots:
    void on_pushButtonIrCadastro_clicked();

    QString pesquisaMarcaPorId(int id);

    void on_pushButtonAlterar_clicked();

    void on_pushButtonDeletar_clicked();

    void alterar(ar::Id id,int linha);

    void on_pushButtonVoltar_clicked();

private:
    Ui::telagerenciarmodelo *ui;

    void listarTabela();
};

#endif // TELAGERENCIARMODELO_H
