#include "TelaHistoricooLocacoes.h"
#include "ui_TelaHistoricooLocacoes.h"

TelaHistoricooLocacoes::TelaHistoricooLocacoes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaHistoricooLocacoes)
{
    ui->setupUi(this);
    try {
        buscarCpfs();
        listarTabela();
    } catch (QString &erro) {
        QMessageBox::information(this,"erro",erro);
    }
}

TelaHistoricooLocacoes::~TelaHistoricooLocacoes()
{
    delete ui;
}

void TelaHistoricooLocacoes::buscarCpfs()
{
    ar::ClientePersistencia arquivoCliente("Cliente.txt");

    std::list<ar::Cliente>* listaCliente=0;

    ui->comboBoxcPF->clear();

    try {
        listaCliente=arquivoCliente.listagem();

    } catch (QString) {

    }

    while(listaCliente!=0 && !listaCliente->empty())
    {
        ar::Cliente cliente=listaCliente->front();
        listaCliente->pop_front();

        ui->comboBoxcPF->addItem(cliente.getCpf());
    }

    if  (listaCliente!=0) delete listaCliente;
}

void TelaHistoricooLocacoes::listarTabela(QString cpf)
{
    try
    {
        std::list<ar::Locacao>* ptListaLocacao=0;

        ar::LocacaoPersistencia arquivoLocacao("Locacao.txt");

        try {
            if  (cpf!="0") ptListaLocacao=arquivoLocacao.listagem(cpf);
            else ptListaLocacao=arquivoLocacao.listagem("",true);

        } catch (...) {

        }

        ui->tableWidgetListagem->setRowCount(0);

        while(ptListaLocacao!=0 && !ptListaLocacao->empty())
        {
            ar::Locacao locacao=ptListaLocacao->front();
            ptListaLocacao->pop_front();



                QTableWidgetItem *itemPlaca=new QTableWidgetItem(locacao.getPlacaVeiculo());
                QTableWidgetItem *itemValorLocacao=new QTableWidgetItem(QString::number(locacao.getValorTotal()));
                QTableWidgetItem *itemDataLocacao=new QTableWidgetItem(locacao.getDataLocao().getDataQString());
                QTableWidgetItem *itemDataDevolucao=new QTableWidgetItem(locacao.getDataDevolucao().getDataQString());
                QTableWidgetItem *itemId=new QTableWidgetItem(QString::number(locacao.getId().getNumero()));
                QTableWidgetItem *itemCpf=new QTableWidgetItem(locacao.getCpfCliente());
                QTableWidgetItem *itemSituacao=new QTableWidgetItem;
                if  (locacao.getSitucao()) itemSituacao->setText("EM ABERTO");
                else itemSituacao->setText("RESOLVIDA");

                int linha=ui->tableWidgetListagem->rowCount();
                ui->tableWidgetListagem->insertRow(linha);


                ui->tableWidgetListagem->setItem(linha,0,itemId);
                ui->tableWidgetListagem->setItem(linha,1,itemCpf);
                ui->tableWidgetListagem->setItem(linha,2,itemPlaca);
                ui->tableWidgetListagem->setItem(linha,3,itemSituacao);
                ui->tableWidgetListagem->setItem(linha,4,itemDataLocacao);
                ui->tableWidgetListagem->setItem(linha,5,itemDataDevolucao);
                ui->tableWidgetListagem->setItem(linha,6,itemValorLocacao);

                ui->tableWidgetListagem->resizeColumnsToContents();

        }

        if  (ptListaLocacao!=0) delete ptListaLocacao;
    } catch (QString & erro)
    {
        QMessageBox::information(this,"erro",erro);
    }
}

void TelaHistoricooLocacoes::on_pushButtonVoltar_clicked()
{
    this->close();
}

void TelaHistoricooLocacoes::on_pushButtonFiltrar_clicked()
{
    try {
        QString cpf=ui->comboBoxcPF->currentText();
        ui->labelCliente->setText("CPF "+cpf+":");
        listarTabela(cpf);

    } catch (QString & erro)
    {
        QMessageBox::information(this,"erro",erro);
    }

}

void TelaHistoricooLocacoes::on_pushButtonRetirarFiltro_clicked()
{
    try {
        ui->labelCliente->setText("TODOS CLIENTES:");
        listarTabela();

    } catch (QString & erro)
    {
        QMessageBox::information(this,"erro",erro);
    }
}
