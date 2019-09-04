#include "telaDevolucao.h"
#include "ui_telaDevolucao.h"

TelaDevolucao::TelaDevolucao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaDevolucao)
{
    ui->setupUi(this);

    try {
        buscarCpfs();
    } catch (QString &erro) {
        QMessageBox::information(this,"erro",erro);
    }
}

TelaDevolucao::~TelaDevolucao()
{
    delete ui;

}

void TelaDevolucao::on_pushButtonCancelar_clicked()
{
    this->close();
}

void TelaDevolucao::buscarCpfs()
{
    ar::ClientePersistencia arquivoCliente("Cliente.txt");

    std::list<ar::Cliente>* listaCliente=0;

    ui->comboBoxCpf->clear();

    try {
        listaCliente=arquivoCliente.listagem();

    } catch (QString) {

    }

    while(listaCliente!=0 && !listaCliente->empty())
    {
        ar::Cliente cliente=listaCliente->front();
        listaCliente->pop_front();

        ui->comboBoxCpf->addItem(cliente.getCpf());
    }

    if  (listaCliente!=0) delete listaCliente;
}

void TelaDevolucao::on_pushButtonMostrarLocacoesEmAberto_clicked()
{
    listarLocacoesEmAberto();
}

void TelaDevolucao::on_pushButtonCalcularValorReal_clicked()
{
    try
    {

        ar::LocacaoPersistencia arquivoLocacao("Locacao.txt");
        ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");

        int linhaSelecionada=ui->tableWidgetListagem->currentRow();

        if  (linhaSelecionada==-1) throw QString("Nenhuma locação selecionada.");

        ar::Id idLocacao(ui->tableWidgetListagem->item(linhaSelecionada,0)->text().toInt());
        ar::Locacao locacao=arquivoLocacao.buscarPorId(idLocacao);
        ar::Veiculo veiculo=arquivoVeiculo.buscarPorPlaca(ui->tableWidgetListagem->item(linhaSelecionada,2)->text());

        float valorDiaria=veiculo.getValorLocacao();

        int diaDataLocacao=locacao.getDataLocao().getDia();
        int mesDataLocacao=locacao.getDataLocao().getMes();
        int anoDataLocacao=locacao.getDataLocao().getAno();

        ar::Data dataLocacao(diaDataLocacao,mesDataLocacao,anoDataLocacao);

        int diaDataDevolucao=ui->lineEditDiaDataDevolucao->text().toInt();
        int mesDataDevolucao=ui->lineEditMesDataDevolucao->text().toInt();
        int anoDataDevolucao=ui->lineEditAnoDataDevolucao->text().toInt();

        ar::Data dataDevolucao(diaDataDevolucao,mesDataDevolucao,anoDataDevolucao);

        ar::Locacao locacaoCalcular("placa","cpf",dataLocacao,dataDevolucao,0);

        locacaoCalcular.calcularValorToal(valorDiaria);

        ui->labelValor->setText(QString::number(locacaoCalcular.getValorTotal()));

    } catch (QString & erro)
    {
        QMessageBox::information(this,"erro",erro);
    }

}

void TelaDevolucao::on_pushButtonConcluirDevolucao_clicked()
{
    try
    {

        ar::LocacaoPersistencia arquivoLocacao("Locacao.txt");
        ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");

        int linhaSelecionada=ui->tableWidgetListagem->currentRow();

        if  (linhaSelecionada==-1) throw QString("Nenhuma locação selecionada.");

        ar::Id idLocacao(ui->tableWidgetListagem->item(linhaSelecionada,0)->text().toInt());
        ar::Locacao locacao=arquivoLocacao.buscarPorId(idLocacao);
        ar::Veiculo veiculo=arquivoVeiculo.buscarPorPlaca(ui->tableWidgetListagem->item(linhaSelecionada,2)->text());

        float valorDiaria=veiculo.getValorLocacao();

        int diaDataLocacao=locacao.getDataLocao().getDia();
        int mesDataLocacao=locacao.getDataLocao().getMes();
        int anoDataLocacao=locacao.getDataLocao().getAno();

        ar::Data dataLocacao(diaDataLocacao,mesDataLocacao,anoDataLocacao);

        int diaDataDevolucao=ui->lineEditDiaDataDevolucao->text().toInt();
        int mesDataDevolucao=ui->lineEditMesDataDevolucao->text().toInt();
        int anoDataDevolucao=ui->lineEditAnoDataDevolucao->text().toInt();

        ar::Data dataDevolucao(diaDataDevolucao,mesDataDevolucao,anoDataDevolucao);

        ar::Locacao locacaoCalcular("placa","cpf",dataLocacao,dataDevolucao,0);

        locacaoCalcular.calcularValorToal(valorDiaria);

        locacao.setValorTotal(locacaoCalcular.getValorTotal());
        locacao.setDataDevolucao(dataDevolucao);

        arquivoLocacao.devolver(locacao);

        listarLocacoesEmAberto();

    } catch (QString & erro)
    {
        QMessageBox::information(this,"erro",erro);
    }
}

void TelaDevolucao::listarLocacoesEmAberto()
{
    try
    {
        QString cpf="";
        cpf=ui->comboBoxCpf->currentText();


        std::list<ar::Locacao>* ptListaLocacao=0;

        ar::LocacaoPersistencia arquivoLocacao("Locacao.txt");
        ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");
        ar::ModeloPersistencia arquivoModelo("Modelo.txt");
        ar::MarcaPersistencia arquivoMarca("Marca.txt");

        try {
            ptListaLocacao=arquivoLocacao.listagem(cpf);
        } catch (...) {

        }

        ui->tableWidgetListagem->setRowCount(0);

        while(ptListaLocacao!=0 && !ptListaLocacao->empty())
        {
            ar::Locacao locacao=ptListaLocacao->front();
            ptListaLocacao->pop_front();
            if  (locacao.getSitucao())
            {
                ar::Veiculo veiculo=arquivoVeiculo.buscarPorPlaca(locacao.getPlacaVeiculo());
                ar::Modelo modelo=arquivoModelo.buscarPorId(veiculo.getIdModelo());
                ar::Marca marca=arquivoMarca.buscarPorId(modelo.getIdMarca());

                QIcon imagemIcon(veiculo.getCaminhoArquivoImagem());

                QTableWidgetItem *itemPlaca=new QTableWidgetItem(veiculo.getPlaca());
                QTableWidgetItem *itemImagem=new QTableWidgetItem(imagemIcon,"");
                QTableWidgetItem *itemValorLocacao=new QTableWidgetItem(QString::number(locacao.getValorTotal()));
                QTableWidgetItem *itemModelo=new QTableWidgetItem(modelo.getDescricao());
                QTableWidgetItem *itemMarca=new QTableWidgetItem(marca.getDescricao());
                QTableWidgetItem *itemDataLocacao=new QTableWidgetItem(locacao.getDataLocao().getDataQString());
                QTableWidgetItem *itemDataDevolucao=new QTableWidgetItem(locacao.getDataDevolucao().getDataQString());
                QTableWidgetItem *itemId=new QTableWidgetItem(QString::number(locacao.getId().getNumero()));

                int linha=ui->tableWidgetListagem->rowCount();
                ui->tableWidgetListagem->insertRow(linha);


                ui->tableWidgetListagem->setItem(linha,0,itemId);
                ui->tableWidgetListagem->setItem(linha,1,itemImagem);
                ui->tableWidgetListagem->setItem(linha,2,itemPlaca);
                ui->tableWidgetListagem->setItem(linha,3,itemModelo);
                ui->tableWidgetListagem->setItem(linha,4,itemMarca);
                ui->tableWidgetListagem->setItem(linha,5,itemDataLocacao);
                ui->tableWidgetListagem->setItem(linha,6,itemDataDevolucao);
                ui->tableWidgetListagem->setItem(linha,7,itemValorLocacao);

                ui->tableWidgetListagem->resizeColumnsToContents();
            }

        }

        if  (ptListaLocacao!=0) delete ptListaLocacao;
    } catch (QString & erro)
    {
        QMessageBox::information(this,"erro",erro);
    }
}
