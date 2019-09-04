#include "telacadastrarmarca.h"
#include "ui_telacadastrarmarca.h"
#include<marca.h>
#include<marcapersistencia.h>
#include<qmessagebox.h>
#include<qfiledialog.h>
#include<telagerenciarmarca.h>
telaCadastrarMarca::telaCadastrarMarca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaCadastrarMarca)
{
    ui->setupUi(this);
}

telaCadastrarMarca::~telaCadastrarMarca()
{
    delete ui;
}

void telaCadastrarMarca::on_pushButtonCadastrar_clicked()
{
    try
    {
        QString nome=ui->lineEditDescricao->text();

        ar::MarcaPersistencia arquivoCliente("Marca.txt");

        ar::Marca testeMarca = ar::Marca();

        testeMarca.setCaminhoArquivoImagem(nomeArquivo);
        testeMarca.setDescricao(nome);

        arquivoCliente.incluir(testeMarca);

        this->close();
    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void telaCadastrarMarca::on_pushButtonIncluirFoto_clicked()
{
    try
      {

        nomeArquivo = QFileDialog::getOpenFileName(this,"Escolher Imagem","/home/puc/Downloads/Locadora/IMAGEM","Arquivos Imagens (*.jpg)");

        QPixmap imagem(nomeArquivo);

        int width=ui->labelFoto->width();

        int height=ui->labelFoto->height();

        ui->labelFoto->setPixmap(imagem.scaled(width,height));
      } catch (QString &erro)
      {
          QMessageBox::information(this,"ERRO",erro);
      }
}

void telaCadastrarMarca::on_pushButtonVoltar_clicked()
{
    this->close();
}
