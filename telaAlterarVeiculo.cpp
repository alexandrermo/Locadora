#include "telaAlterarVeiculo.h"
#include "ui_telaAlterarVeiculo.h"

TelaAlterarVeiculo::TelaAlterarVeiculo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaAlterarVeiculo),
    cancelou(true),
    caminhoArquivoImagem("")
{
    ui->setupUi(this);

    try {

        buscarModelos();
        colocarDados();

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }

}

TelaAlterarVeiculo::~TelaAlterarVeiculo()
{
    delete ui;

    ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");

    if  (cancelou)  arquivoVeiculo.apagarPorPlaca("0");
}

void TelaAlterarVeiculo::on_pushButtonInserirImagem_clicked()
{
    try
      {
          caminhoArquivoImagem = QFileDialog::getOpenFileName(this,"Escolher Imagem","/home/puc/Downloads/Locadora/IMAGEM","Arquivos Imagens (*.jpg)");

          QPixmap imagem(caminhoArquivoImagem);

          int width=ui->labelImagem->width();

          int height=ui->labelImagem->height();

          ui->labelImagem->setPixmap(imagem.scaled(width,height));

      } catch (QString &erro)
      {
          QMessageBox::information(this,"ERRO",erro);
      }
}

void TelaAlterarVeiculo::on_pushButtonCancelar_clicked()
{
    this->close();
}

void TelaAlterarVeiculo::on_pushButtonAlterar_clicked()
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

        ar::Veiculo testeVeiculo(placa,quilometragem,valorLocacao,caminhoArquivoImagem,modelo.getId());

        caminhoArquivoImagem="";

        std::string placaAlterar="";
        std::fstream arquivoTemp;
        arquivoTemp.open("Temporario.txt",std::ios::in);
        if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em colocarDados em TelaAlterarVeiculo.");
        getline(arquivoTemp,placaAlterar);
        arquivoTemp.close();

        try
        {
            arquivoVeiculo.buscarPorPlaca(placa);
        } catch (QString)
        {
            achouPlaca=false;
        }

        if  (achouPlaca && placa!=QString::fromStdString(placaAlterar)) throw QString("Placa já cadastrada no sistema.");
        if  (placa=="0") throw QString("Placa inválida.");

        arquivoVeiculo.apagarPorPlaca("0");
        testeVeiculo.setPlaca("0");
        arquivoVeiculo.incluir(testeVeiculo);

        arquivoTemp.open("Temporario.txt",std::ios::out);
        if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em colocarDados em TelaAlterarVeiculo.");
        arquivoTemp<<placa.toStdString();
        arquivoTemp.close();

        cancelou=false;

        this->close();

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void TelaAlterarVeiculo::colocarDados()
{
    ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");
    ar::Veiculo veiculoTemp=arquivoVeiculo.buscarPorPlaca("0");
    ar::ModeloPersistencia arquivoModelo("Modelo.txt");


    QPixmap imagem(veiculoTemp.getCaminhoArquivoImagem());

    int height=ui->labelImagem->height();
    int width=ui->labelImagem->width();

    caminhoArquivoImagem=veiculoTemp.getCaminhoArquivoImagem();

    std::string placa="";

    std::ifstream arquivoTemp;
    arquivoTemp.open("Temporario.txt");
    if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em colocarDados em TelaAlterarVeiculo.");
    getline(arquivoTemp,placa);
    arquivoTemp.close();

    ar::Modelo modelo;
    try {
        modelo=arquivoModelo.buscarPorId(veiculoTemp.getIdModelo());
    } catch (QString &msg) {
        if  (msg!="Número de ID inválido em buscarPorId(ModeloPesistencia).") throw QString(msg);
    }


    ui->lineEditPlaca->setText(QString::fromStdString(placa));
    ui->lineEditValorDiaria->setText(QString::number(veiculoTemp.getValorLocacao()));
    ui->lineEditQuilometragem->setText(QString::number(veiculoTemp.getQuilometragem()));
    ui->labelImagem->setPixmap(imagem.scaled(height,width));
    if  (modelo.getDescricao()!="") ui->comboBoxModelo->setCurrentText(modelo.getDescricao());
}

void TelaAlterarVeiculo::buscarModelos()
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
