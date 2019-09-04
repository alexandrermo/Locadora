#include "telacadastrarmodelo.h"
#include "ui_telacadastrarmodelo.h"
#include<marcapersistencia.h>
#include<qstringlist.h>
telacadastrarModelo::telacadastrarModelo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telacadastrarModelo)
{
    ui->setupUi(this);
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

}

telacadastrarModelo::~telacadastrarModelo()
{
    delete ui;
}

void telacadastrarModelo::on_pushButtonCadastrar_clicked()
{
    try
    {

        QString nome=ui->lineEditDescricao->text();

        ar::ModeloPersistencia arquivoCliente("Modelo.txt");
        ar::Id id;
        ar::Modelo testeModelo;

        testeModelo.setCaminhoArquivoImagem(nomeArquivo);
        testeModelo.setDescricao(nome);
        testeModelo.setNumeroIdMarca(pesquisarNumeroIdporMarca(ui->comboBoxMarca->currentText()));
        arquivoCliente.incluir(testeModelo);

        this->close();
    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

int telacadastrarModelo:: pesquisarNumeroIdporMarca(QString marca){
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

void telacadastrarModelo::on_pushButtonIncluirFoto_clicked()
{
    try
      {

        nomeArquivo = QFileDialog::getOpenFileName(this,"Escolher Imagem","/home/puc/Downloads/Locadora/IMAGEM","Arquivos Imagens (*.jpg)");

        QPixmap imagem(nomeArquivo);

        int width=ui->labelFoto->width();

        int height=ui->labelFoto->height();

        ui->labelFoto->setPixmap(imagem.scaled(width,height));
          if(nomeArquivo!="") ui->pushButtonCadastrar->setEnabled(1);
      } catch (QString &erro)
      {
          QMessageBox::information(this,"ERRO",erro);
      }
}

void telacadastrarModelo::on_pushButtonVoltar_clicked()
{
    this->close();
}
