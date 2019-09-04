#include "telacadastrarveiculo.h"
#include "ui_telacadastrarveiculo.h"

TelaCadastrarVeiculo::TelaCadastrarVeiculo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaCadastrarVeiculo),
    caminhoArquivoImagemTeste("")
{
    try {

        ui->setupUi(this);

        buscarModelos();

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }

}

TelaCadastrarVeiculo::~TelaCadastrarVeiculo()
{
    delete ui;
}

void TelaCadastrarVeiculo::on_pushButtonIncluir_clicked()
{
    try
    {
        bool achouPlaca=true;
        QString placa=ui->lineEditPlaca->text();
        float valorLocacao=ui->lineEditValorDiaria->text().toFloat();
        int quilometragem=ui->lineEditQuilometragem->text().toInt();
        QString modeloDescricao=ui->comboBoxModelo->currentText();

        ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");
        ar::ModeloPersistencia arquivoModelo("Modelo.txt");

        ar::Modelo modelo=arquivoModelo.buscarPorDescricao(modeloDescricao);

        ar::Veiculo testeVeiculo(placa,quilometragem,valorLocacao,caminhoArquivoImagemTeste,modelo.getId());

        caminhoArquivoImagemTeste="";

        try
        {
            arquivoVeiculo.buscarPorPlaca(placa);
        } catch (QString)
        {
            achouPlaca=false;
        }

        if  (achouPlaca) throw QString("Placa já cadastrada no sistema.");
        if  (placa=="0") throw QString("Placa inválida.");

        arquivoVeiculo.incluir(testeVeiculo);

        this->close();

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }

}

void TelaCadastrarVeiculo::on_pushButtonInserirImagem_clicked()
{
    try
      {
          caminhoArquivoImagemTeste = QFileDialog::getOpenFileName(this,"Escolher Imagem","/home/puc/Downloads/Locadora/IMAGEM","Arquivos Imagens (*.jpg)");

          QPixmap imagem(caminhoArquivoImagemTeste);

          int width=ui->labelImagem->width();

          int height=ui->labelImagem->height();

          ui->labelImagem->setPixmap(imagem.scaled(width,height));

      } catch (QString &erro)
      {
          QMessageBox::information(this,"ERRO",erro);
      }
}

void TelaCadastrarVeiculo::on_pushButtonCancelar_clicked()
{
    this->close();
}


void TelaCadastrarVeiculo::buscarModelos()
{
    ar::ModeloPersistencia arquivoModelo("Modelo.txt");

    std::list<ar::Modelo>* listaModelos=0;

    ui->comboBoxModelo->clear();

    try {
        listaModelos=arquivoModelo.listagem();

    } catch (QString) {

    }

    while(listaModelos!=0 && !listaModelos->empty())
    {
        ar::Modelo modelo=listaModelos->front();
        listaModelos->pop_front();

        ui->comboBoxModelo->addItem(modelo.getDescricao());
    }

    if  (listaModelos!=0) delete listaModelos;

}
