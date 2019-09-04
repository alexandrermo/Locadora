#include "telaalterarcliente.h"
#include "ui_telaalterarcliente.h"

TelaAlterarCliente::TelaAlterarCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaAlterarCliente),
    caminhoArquivoImagemTeste(""),
    cancelou(true)
{
    ui->setupUi(this);
    colocarDados();
}

TelaAlterarCliente::~TelaAlterarCliente()
{
    delete ui;

    ar::ClientePersistencia arquivoCliente("Cliente.txt");

    if  (cancelou) arquivoCliente.apagarPorCpf("0");
}

void TelaAlterarCliente::on_pushButtonAlterar_clicked()
{
    try
    {
        bool achouCpf=true;
        QString nome=ui->lineEditNome->text();
        int ddd=ui->lineEditDDD->text().toInt();
        int ddi=ui->lineEditDDI->text().toInt();
        int numero=ui->lineEditNumero->text().toInt();
        QString email=ui->lineEditEmail->text();
        QString cnh=ui->lineEditCnh->text();
        QString cpf=ui->lineEditCpf->text();
        QString tipoRelacionamento=ui->comboBoxTipoRelacionamento->currentText();

        ar::Telefone testeTelefone(ddi,ddd,numero);
        ar::ClientePersistencia arquivoCliente("Cliente.txt");

        ar::Cliente testeCliente(nome,testeTelefone,email,caminhoArquivoImagemTeste,cnh,cpf);

        std::string cpfAlterar="";
        std::fstream arquivoTemp;
        arquivoTemp.open("Temporario.txt",std::ios::in);
        if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em colocarDados em TelaAlterarVeiculo.");
        getline(arquivoTemp,cpfAlterar);
        arquivoTemp.close();


        caminhoArquivoImagemTeste="";
        try
        {
            arquivoCliente.buscarPorCpf(cpf);
        } catch (QString)
        {
            achouCpf=false;
        }

        if  (achouCpf && cpf!=QString::fromStdString(cpfAlterar)) throw QString("Número de CPF já cadastrado no sistema.");
        if  (cpf=="0") throw QString("Número de CPF inválido.");

        arquivoCliente.apagarPorCpf("0");
        testeCliente.setCpf("0");
        testeCliente.setTipoRelacionamento(tipoRelacionamento);
        arquivoCliente.incluir(testeCliente,false);

        arquivoTemp.open("Temporario.txt",std::ios::out);
        if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em Botão Alterar em TelaAlterarCLiente.");
        arquivoTemp<<cpf.toStdString();
        arquivoTemp.close();

        cancelou=false;
        this->close();

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void TelaAlterarCliente::on_pushButtonInserirImagem_clicked()
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

void TelaAlterarCliente::colocarDados()
{
    ar::ClientePersistencia arquivoCliente("Cliente.txt");
    ar::Cliente clienteTemp=arquivoCliente.buscarPorCpf("0");

    QPixmap imagem(clienteTemp.getCaminhoArquivoImagem());

    int height=ui->labelImagem->height();
    int width=ui->labelImagem->width();

    caminhoArquivoImagemTeste=clienteTemp.getCaminhoArquivoImagem();

    std::string cpf="";

    std::ifstream arquivoTemp;
    arquivoTemp.open("Temporario.txt");
    if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em colocarDados em TelaAlterarCLiente.");
    getline(arquivoTemp,cpf);
    arquivoTemp.close();

    ui->lineEditNome->setText(clienteTemp.getNomeCompleto());
    ui->lineEditCnh->setText(clienteTemp.getCnh());
    ui->lineEditCpf->setText(QString::fromStdString(cpf));
    ui->lineEditDDD->setText(clienteTemp.getDDD());
    ui->lineEditDDI->setText(clienteTemp.getDDI());
    ui->lineEditNumero->setText(clienteTemp.getNumero());
    ui->labelImagem->setPixmap(imagem.scaled(height,width));
    ui->lineEditEmail->setText(clienteTemp.getEmail());
    ui->comboBoxTipoRelacionamento->setCurrentText(clienteTemp.getTipoRelacionamentoQString());

}

void TelaAlterarCliente::on_pushButtonCancelar_clicked()
{
    this->close();
}

