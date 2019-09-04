#include "telacadastrarcliente.h"
#include "ui_telacadastrarcliente.h"

TelaCadastrarCliente::TelaCadastrarCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaCadastrarCliente),
    caminhoArquivoImagemTeste("")
{
    ui->setupUi(this);
}

TelaCadastrarCliente::~TelaCadastrarCliente()
{
    delete ui;
}

void TelaCadastrarCliente::on_pushButtonInserirImagem_clicked()
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

void TelaCadastrarCliente::on_pushButtonIncluir_clicked()
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

        caminhoArquivoImagemTeste="";

        try
        {
            arquivoCliente.buscarPorCpf(cpf);
        } catch (QString)
        {
            achouCpf=false;
        }

        if  (achouCpf) throw QString("Número de CPF já cadastrado no sistema.");
        if  (cpf=="0") throw QString("Número de CPF inválido.");

        testeCliente.setTipoRelacionamento(tipoRelacionamento);

        arquivoCliente.incluir(testeCliente);

        limparTela();

        this->close();

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void TelaCadastrarCliente::limparTela()
{
    ui->lineEditNome->clear();
    ui->lineEditDDD->clear();
    ui->lineEditDDI->clear();
    ui->lineEditNumero->clear();
    ui->labelImagem->clear();
    ui->lineEditEmail->clear();
    ui->lineEditCnh->clear();
    ui->lineEditCpf->clear();
}

void TelaCadastrarCliente::on_pushButtonVoltar_clicked()
{
    this->close();
}
