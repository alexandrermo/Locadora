#ifndef TELACADASTRARMODELO_H
#define TELACADASTRARMODELO_H
#include<modelopersistencia.h>
#include<telagerenciarmodelo.h>
#include<qmessagebox.h>
#include<qfiledialog.h>
#include <QDialog>

namespace Ui {
class telacadastrarModelo;
}

class telacadastrarModelo : public QDialog
{
    Q_OBJECT

public:
    explicit telacadastrarModelo(QWidget *parent = nullptr);
    ~telacadastrarModelo();

private slots:
    void on_pushButtonCadastrar_clicked();

    void on_pushButtonIncluirFoto_clicked();

    int pesquisarNumeroIdporMarca(QString marca);
    void on_pushButtonVoltar_clicked();

private:
    Ui::telacadastrarModelo *ui;
    QString nomeArquivo;
};

#endif // TELACADASTRARMODELO_H
