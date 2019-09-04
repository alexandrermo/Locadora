#include "telaalterarmodelo.h"
#include "ui_telaalterarmodelo.h"
#include<modelopersistencia.h>
#include<qfiledialog.h>
#include<qmessagebox.h>
telaAlterarModelo::telaAlterarModelo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaAlterarModelo),
    caminhoArquivoImagemTeste(""),
    cancelou(true)
{
     ui->setupUi(this);
     colocarDados();
}
telaAlterarModelo::~telaAlterarModelo()
{
    delete ui;
    ar::ModeloPersistencia arquivoModelo("Modelo.txt");
    ar::Id id0;
    if  (cancelou) arquivoModelo.apagarPorId(id0);
}

void telaAlterarModelo::on_pushButtonAlterar_clicked()
{
    try
    {

        QString nome=ui->lineEditDescricao->text();

        ar::ModeloPersistencia arquivoCliente("Modelo.txt");
        ar::Id id;
        ar::Modelo testeModelo;

        ar::Id id0;

        testeModelo.setCaminhoArquivoImagem(caminhoArquivoImagemTeste);
        testeModelo.setDescricao(nome);
        testeModelo.setNumeroIdMarca(pesquisarNumeroIdporMarca(ui->comboBoxMarca->currentText()));

        testeModelo.setId(id0);
        arquivoCliente.apagarPorId(id0);

        arquivoCliente.incluir(testeModelo,false);

        this->close();
    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void telaAlterarModelo::colocarDados()
{
    ar::Id id0;
    ar::ModeloPersistencia arquivoModelo("Modelo.txt");
    ar::Modelo ModeloTemp=arquivoModelo.buscarPorId(id0);

    QPixmap imagem(ModeloTemp.getCaminhoArquivoImagem());

    int height=ui->labelFoto->height();
    int width=ui->labelFoto->width();
    QString marca=pesquisaMarcaPorId(ModeloTemp.getIdMarca().getNumero());
    caminhoArquivoImagemTeste=ModeloTemp.getCaminhoArquivoImagem();

    ui->lineEditDescricao->setText(ModeloTemp.getDescricao());
    ui->labelFoto->setPixmap(imagem.scaled(height,width));
    try {
        std::ifstream arquivoAgenda;
                arquivoAgenda.open("Marca.txt");
                if  (!arquivoAgenda.is_open()) throw QString("Arquivo não abriu.");
                std::string linha;
                getline(arquivoAgenda,linha);
                while(!arquivoAgenda.eof()){
                    QString str = QString::fromStdString(linha);
                    QStringList dados=str.split(";");
                    ui->comboBoxMarca->addItem(dados[1]);
                    getline(arquivoAgenda,linha);
                }
    } catch (QString) {

    }

    ui->comboBoxMarca->setCurrentText(marca);
}

QString telaAlterarModelo::pesquisaMarcaPorId(int id){
    std::ifstream arquivoAgenda;
    arquivoAgenda.open("Marca.txt");
    std::string linha2;
    QString final;
    getline(arquivoAgenda,linha2);
    if  (arquivoAgenda.is_open())
    {
        while(!arquivoAgenda.eof()){
            QString str = QString::fromStdString(linha2);
            QStringList dados=str.split(";");
            if(id==dados[2].toInt())  final=dados[1];
            getline(arquivoAgenda,linha2);
        }
        arquivoAgenda.close();

    }

    return final;
}

void telaAlterarModelo::on_pushButtonIncluirFoto_clicked()
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

void telaAlterarModelo::on_pushButtonVoltar_clicked()
{
    this->close();
}

int telaAlterarModelo:: pesquisarNumeroIdporMarca(QString marca){
    std::ifstream arquivoAgenda;
    arquivoAgenda.open("Marca.txt");
    std::string linha2;
    int  final=0;
    getline(arquivoAgenda,linha2);
    if  (arquivoAgenda.is_open())
    {
        while(!arquivoAgenda.eof()){
            QString str = QString::fromStdString(linha2);
            QStringList dados=str.split(";");
            if(marca==dados[1]) final =dados[2].toInt();
            getline(arquivoAgenda,linha2);
        }
        arquivoAgenda.close();

    }

    return final;
}
