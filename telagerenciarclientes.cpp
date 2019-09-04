#include "telagerenciarclientes.h"
#include "ui_telagerenciarclientes.h"

TelaGerenciarClientes::TelaGerenciarClientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaGerenciarClientes)
{

    ui->setupUi(this);

    try {
        listarTabela();
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }

}

TelaGerenciarClientes::~TelaGerenciarClientes()
{
    delete ui;
}



bool ordenarPorRelacionamento(ar::Cliente objeto1, ar::Cliente objeto2)
{
    if  (objeto1.getTipoRelacionamentoEnum()==objeto2.getTipoRelacionamentoEnum()) return objeto1.getNomeCompleto()<objeto2.getNomeCompleto();
    return objeto1.getTipoRelacionamentoEnum()<objeto2.getTipoRelacionamentoEnum();
}
void TelaGerenciarClientes::listarTabela(QString ordenar)
{
    ar::ClientePersistencia agendaCliente("Cliente.txt");

    std::list<ar::Cliente>* listaClientes=0;
    try {
        listaClientes=agendaCliente.listagem();
    } catch (QString) {

    }

    if  (listaClientes!=0 && ordenar=="Tipo Relacionamento") listaClientes->sort(ordenarPorRelacionamento);

    ui->tableWidgetListagem->setRowCount(0);

    while(listaClientes!=0 && !listaClientes->empty())
    {
        ar::Cliente objeto=listaClientes->front();
        listaClientes->pop_front();

        QIcon imagemIcon(objeto.getCaminhoArquivoImagem());

        QTableWidgetItem *itemCpfCliente=new QTableWidgetItem(objeto.getCpf());
        QTableWidgetItem *itemImagem=new QTableWidgetItem(imagemIcon,"");
        QTableWidgetItem *itemNomeCompleto=new QTableWidgetItem(objeto.getNomeCompleto());
        QTableWidgetItem *itemTelefone=new QTableWidgetItem(objeto.getTelefone());
        QTableWidgetItem *itemEmail=new QTableWidgetItem(objeto.getEmail());
        QTableWidgetItem *itemCnh=new QTableWidgetItem(objeto.getCnh());
        QTableWidgetItem *itemTipoRelacionamento=new QTableWidgetItem(objeto.getTipoRelacionamentoQString());


        int linha=ui->tableWidgetListagem->rowCount();
        ui->tableWidgetListagem->insertRow(linha);


        ui->tableWidgetListagem->setItem(linha,0,itemImagem);
        ui->tableWidgetListagem->setItem(linha,1,itemNomeCompleto);
        ui->tableWidgetListagem->setItem(linha,2,itemCpfCliente);
        ui->tableWidgetListagem->setItem(linha,3,itemTipoRelacionamento);
        ui->tableWidgetListagem->setItem(linha,4,itemTelefone);
        ui->tableWidgetListagem->setItem(linha,5,itemEmail);
        ui->tableWidgetListagem->setItem(linha,6,itemCnh);

        ui->tableWidgetListagem->resizeColumnsToContents();

    }

    if  (listaClientes!=0) delete listaClientes;
}
void TelaGerenciarClientes::on_pushButtonCadastrarNovoCliente_clicked()
{
    try {
        TelaCadastrarCliente TelaCadastrarCliente;
        TelaCadastrarCliente.setModal(true);
        TelaCadastrarCliente.exec();

        listarTabela();

    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }



}

void TelaGerenciarClientes::on_pushButtonApagar_clicked()
{
    try
    {
        int linha=ui->tableWidgetListagem->currentRow();

        if  (linha==-1) throw QString("Nenhuma linha selecionada.");

        QString cpf=ui->tableWidgetListagem->item(linha,2)->text();

        ar::ClientePersistencia arquivoCliente("Cliente.txt");

        arquivoCliente.apagarPorCpf(cpf);

        ui->tableWidgetListagem->removeRow(linha);

    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void TelaGerenciarClientes::on_pushButtonAlterar_clicked()
{
    try {
        int linha=ui->tableWidgetListagem->currentRow();
        if  (linha==-1) throw  QString("Nenhuma linha selecionada.");

        QString cpf=ui->tableWidgetListagem->item(linha,2)->text();


        ar::ClientePersistencia arquivoCliente("Cliente.txt");
        ar::Cliente objetoTemp=arquivoCliente.buscarPorCpf(cpf);

        objetoTemp.setCpf("0");

        arquivoCliente.incluir(objetoTemp,false);

        std::ofstream arquivoTemp;
        arquivoTemp.open("Temporario.txt");
        if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em Botão Alterar em TelaGerenciarCLiente.");
        arquivoTemp<<cpf.toStdString();
        arquivoTemp.close();

        TelaAlterarCliente telaAlterarCliente;
        telaAlterarCliente.setModal(true);
        telaAlterarCliente.exec();

        alterar(cpf,linha);

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void TelaGerenciarClientes::alterar(QString cpf,int linha)
{
    ar::ClientePersistencia agendaCliente("Cliente.txt");
    std::list<ar::Cliente>* lista=0;
    lista=agendaCliente.listagem();

    int tamanhoLista=lista->size();
    delete lista;

    if  (tamanhoLista==ui->tableWidgetListagem->rowCount()) return;

    agendaCliente.apagarPorCpf(cpf);

    std::string cpfString="";
    std::ifstream arquivoTemp;
    arquivoTemp.open("Temporario.txt");
    if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em alterar em TelaGerenciarCLiente.");
    getline(arquivoTemp,cpfString);
    arquivoTemp.close();

    ar::Cliente objeto=agendaCliente.buscarPorCpf("0");
    objeto.setCpf(QString::fromStdString(cpfString));
    agendaCliente.incluir(objeto,false);
    agendaCliente.apagarPorCpf("0");

    ui->tableWidgetListagem->removeRow(linha);

    QIcon imagemIcon(objeto.getCaminhoArquivoImagem());

    QTableWidgetItem *itemCpfCliente=new QTableWidgetItem(objeto.getCpf());
    QTableWidgetItem *itemImagem=new QTableWidgetItem(imagemIcon,"");
    QTableWidgetItem *itemNomeCompleto=new QTableWidgetItem(objeto.getNomeCompleto());
    QTableWidgetItem *itemTelefone=new QTableWidgetItem(objeto.getTelefone());
    QTableWidgetItem *itemEmail=new QTableWidgetItem(objeto.getEmail());
    QTableWidgetItem *itemCnh=new QTableWidgetItem(objeto.getCnh());
    QTableWidgetItem *itemRelacionamento=new QTableWidgetItem(objeto.getTipoRelacionamentoQString());

    ui->tableWidgetListagem->insertRow(linha);

    ui->tableWidgetListagem->setItem(linha,0,itemImagem);
    ui->tableWidgetListagem->setItem(linha,1,itemNomeCompleto);
    ui->tableWidgetListagem->setItem(linha,2,itemCpfCliente);
    ui->tableWidgetListagem->setItem(linha,3,itemRelacionamento);
    ui->tableWidgetListagem->setItem(linha,4,itemTelefone);
    ui->tableWidgetListagem->setItem(linha,5,itemEmail);
    ui->tableWidgetListagem->setItem(linha,6,itemCnh);

    ui->tableWidgetListagem->resizeColumnsToContents();

}

void TelaGerenciarClientes::on_pushButtonVoltar_clicked()
{
    this->close();
}

void TelaGerenciarClientes::on_pushButtonOrdenarPorNome_clicked()
{
    try {
        listarTabela();

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }

}

void TelaGerenciarClientes::on_pushButtonOrdenarPorRelacionamento_clicked()
{
    try {
        listarTabela("Tipo Relacionamento");

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}
