#include "telaalterarmarca.h"
#include "ui_telaalterarmarca.h"
#include<marcapersistencia.h>
#include<qfiledialog.h>
#include<qmessagebox.h>
#include<telagerenciarmarca.h>
telaAlterarMarca::telaAlterarMarca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaAlterarMarca),
    caminhoArquivoImagemTeste(""),
    cancelou(true)
{
     ui->setupUi(this);
     colocarDados();
}

telaAlterarMarca::~telaAlterarMarca()
{
    delete ui;
    ar::MarcaPersistencia arquivoMarca("Marca.txt");
    if  (cancelou) arquivoMarca.apagarPorId(0);
}

void telaAlterarMarca::on_pushButtonAlterar_clicked()
{
    try
    {

        QString nome=ui->lineEditDescricao->text();

        ar::MarcaPersistencia arquivoMarca("Marca.txt");

        ar::Marca testeMarca = ar::Marca();

        testeMarca.setCaminhoArquivoImagem( caminhoArquivoImagemTeste);
        testeMarca.setDescricao(nome);

        caminhoArquivoImagemTeste="";

        ar::Id id0;

        arquivoMarca.apagarPorId(id0);
        testeMarca.setId(id0);
        arquivoMarca.incluir(testeMarca,false);
        cancelou=false;
        this->close();

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }

}

void telaAlterarMarca::on_pushButtonIncluirFoto_clicked()
{
    try
      {

        caminhoArquivoImagemTeste = QFileDialog::getOpenFileName(this,"Escolher Imagem","/home/puc/Downloads/Locadora/IMAGEM","Arquivos Imagens (*.jpg)");

        QPixmap imagem(caminhoArquivoImagemTeste);

        int width=ui->labelFoto->width();

        int height=ui->labelFoto->height();

        ui->labelFoto->setPixmap(imagem.scaled(width,height));
      } catch (QString &erro)
      {
          QMessageBox::information(this,"ERRO",erro);
      }
}

void telaAlterarMarca::colocarDados()
{
    ar::MarcaPersistencia arquivoMarca("Marca.txt");
    ar::Marca MarcaTemp=arquivoMarca.buscarPorId(0);

    QPixmap imagem(MarcaTemp.getCaminhoArquivoImagem());

    int height=ui->labelFoto->height();
    int width=ui->labelFoto->width();

    caminhoArquivoImagemTeste=MarcaTemp.getCaminhoArquivoImagem();

    ui->lineEditDescricao->setText(MarcaTemp.getDescricao());
     ui->labelFoto->setPixmap(imagem.scaled(height,width));

}

void telaAlterarMarca::on_pushButtonVoltar_clicked()
{
    this->close();
}
