#ifndef TELACADASTRARMARCA_H
#define TELACADASTRARMARCA_H

#include <QDialog>

namespace Ui {
class telaCadastrarMarca;
}

class telaCadastrarMarca : public QDialog
{
    Q_OBJECT

public:
    explicit telaCadastrarMarca(QWidget *parent = nullptr);
    ~telaCadastrarMarca();

private slots:
    void on_pushButtonCadastrar_clicked();

    void on_pushButtonIncluirFoto_clicked();

    void on_pushButtonVoltar_clicked();

private:
    QString nomeArquivo;
    Ui::telaCadastrarMarca *ui;
};

#endif // TELACADASTRARMARCA_H
