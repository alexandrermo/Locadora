#include "telaLocacao.h"
#include "ui_telaLocacao.h"


TelaLocacao::TelaLocacao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaLocacao)
{
    ui->setupUi(this);

    try {
        listarVeiculosDisponiveis();
        buscarCpfs();

        time_t timer;
        time(&timer);
        struct tm *dataLocal=localtime(&timer);

        ui->lineEditDiaDataLocacao->setText(QString::number(dataLocal->tm_mday));
        ui->lineEditMesDataLocacao->setText(QString::number(dataLocal->tm_mon+1));
        ui->lineEditAnoDataLocacao->setText(QString::number(dataLocal->tm_year+1900));

    } catch (QString & erro) {
        QMessageBox::information(this,"erro",erro);
    }
}

TelaLocacao::~TelaLocacao()
{
    delete ui;
}

bool ordenarPorMarca(ar::Veiculo objeto1,ar::Veiculo objeto2)
{
    ar::ModeloPersistencia arquivoModelo("Modelo.txt");
    ar::MarcaPersistencia arquivoMarca("Marca.txt");

    ar::Modelo modelo1=arquivoModelo.buscarPorId(objeto1.getIdModelo());
    ar::Marca marca1=arquivoMarca.buscarPorId(modelo1.getIdMarca());

    ar::Modelo modelo2=arquivoModelo.buscarPorId(objeto2.getIdModelo());
    ar::Marca marca2=arquivoMarca.buscarPorId(modelo2.getIdMarca());

    return marca1.getDescricao()<marca2.getDescricao();
}
bool ordenarPorValor(ar::Veiculo objeto1,ar::Veiculo objeto2)
{

    return objeto1.getValorLocacao()<objeto2.getValorLocacao();
}
bool ordenarPorQuilometragem(ar::Veiculo objeto1,ar::Veiculo objeto2)
{

    return objeto1.getQuilometragem()<objeto2.getQuilometragem();
}
void TelaLocacao::listarVeiculosDisponiveis(QString ordenar)
{
    ar::VeiculoPersistencia agendaVeiculo("Veiculo.txt");
    ar::ModeloPersistencia arquivoModelo("Modelo.txt");
    ar::MarcaPersistencia arquivoMarca("Marca.txt");

    std::list<ar::Veiculo>* listaVeiculos=0;
    try {
        listaVeiculos=agendaVeiculo.listagem();
    } catch (QString) {

    }

    if  (listaVeiculos!=0 && ordenar=="Marca") listaVeiculos->sort(ordenarPorMarca);
    if  (listaVeiculos!=0 && ordenar=="Valor") listaVeiculos->sort(ordenarPorValor);
    if  (listaVeiculos!=0 && ordenar=="Quilometragem") listaVeiculos->sort(ordenarPorQuilometragem);

    ui->tableWidgetListagem->setRowCount(0);

    while(listaVeiculos!=0 && !listaVeiculos->empty())
    {
        ar::Veiculo objeto=listaVeiculos->front();
        listaVeiculos->pop_front();

        if  (objeto.getSituacao()!=true)
        {
            QIcon imagemIcon(objeto.getCaminhoArquivoImagem());

            ar::Modelo modelo=arquivoModelo.buscarPorId(objeto.getIdModelo());
            ar::Marca marca=arquivoMarca.buscarPorId(modelo.getIdMarca());

            QTableWidgetItem *itemPlaca=new QTableWidgetItem(objeto.getPlaca());
            QTableWidgetItem *itemImagem=new QTableWidgetItem(imagemIcon,"");
            QTableWidgetItem *itemValorLocacao=new QTableWidgetItem(QString::number(objeto.getValorLocacao()));
            QTableWidgetItem *itemQuilometragem=new QTableWidgetItem(QString::number(objeto.getQuilometragem()));
            QTableWidgetItem *itemModelo=new QTableWidgetItem(modelo.getDescricao());
            QTableWidgetItem *itemMarca=new QTableWidgetItem(marca.getDescricao());


            int linha=ui->tableWidgetListagem->rowCount();
            ui->tableWidgetListagem->insertRow(linha);


            ui->tableWidgetListagem->setItem(linha,0,itemImagem);
            ui->tableWidgetListagem->setItem(linha,1,itemPlaca);
            ui->tableWidgetListagem->setItem(linha,2,itemModelo);
            ui->tableWidgetListagem->setItem(linha,3,itemMarca);
            ui->tableWidgetListagem->setItem(linha,4,itemValorLocacao);
            ui->tableWidgetListagem->setItem(linha,5,itemQuilometragem);

            ui->tableWidgetListagem->resizeColumnsToContents();
        }
    }

    if  (listaVeiculos!=0) delete listaVeiculos;
}

void TelaLocacao::buscarCpfs()
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

void TelaLocacao::on_pushButtonCancelar_clicked()
{
    this->close();
}

void TelaLocacao::on_pushButtonCalcularValor_clicked()
{
    try {
        int diaDataLocacao=ui->lineEditDiaDataLocacao->text().toInt();
        int mesDataLocacao=ui->lineEditMesDataLocacao->text().toInt();
        int anoDataLocacao=ui->lineEditAnoDataLocacao->text().toInt();

        int diaDataDevolucao=ui->lineEditDiaDataDevolucao->text().toInt();
        int mesDataDevolucao=ui->lineEditMesDataDevolucao->text().toInt();
        int anoDataDevolucao=ui->lineEditAnoDataDevolucao->text().toInt();

        ar::Data dataLocacao(diaDataLocacao,mesDataLocacao,anoDataLocacao);
        ar::Data dataDevolucao(diaDataDevolucao,mesDataDevolucao,anoDataDevolucao);

        int linhaTabela=ui->tableWidgetListagem->currentRow();
        if  (linhaTabela==-1) throw QString("Nenhum veículo selecionado.");

        float valorDiaria=ui->tableWidgetListagem->item(linhaTabela,4)->text().toFloat();

        ar::Locacao locacao("placa","cpf",dataLocacao,dataDevolucao,0);

        locacao.calcularValorToal(valorDiaria);

        ui->labelValor->setText(QString::number(locacao.getValorTotal()));

    } catch (QString &erro) {
        QMessageBox::information(this,"erro",erro);

    }

}

void TelaLocacao::on_pushButtonConcluirLocacao_clicked()
{
    try {
        int diaDataLocacao=ui->lineEditDiaDataLocacao->text().toInt();
        int mesDataLocacao=ui->lineEditMesDataLocacao->text().toInt();
        int anoDataLocacao=ui->lineEditAnoDataLocacao->text().toInt();

        int diaDataDevolucao=ui->lineEditDiaDataDevolucao->text().toInt();
        int mesDataDevolucao=ui->lineEditMesDataDevolucao->text().toInt();
        int anoDataDevolucao=ui->lineEditAnoDataDevolucao->text().toInt();

        QString cpf=ui->comboBoxCpf->currentText();

        ar::Data dataLocacao(diaDataLocacao,mesDataLocacao,anoDataLocacao);
        ar::Data dataDevolucao(diaDataDevolucao,mesDataDevolucao,anoDataDevolucao);

        int linhaTabela=ui->tableWidgetListagem->currentRow();
        if  (linhaTabela==-1) throw QString("Nenhum veículo selecionado.");

        float valorDiaria=ui->tableWidgetListagem->item(linhaTabela,4)->text().toFloat();
        QString placa=ui->tableWidgetListagem->item(linhaTabela,1)->text();

        ar::Locacao locacao(placa,cpf,dataLocacao,dataDevolucao,0);

        locacao.calcularValorToal(valorDiaria);

        ar::LocacaoPersistencia arquivoLocacao("Locacao.txt");

        arquivoLocacao.locar(locacao);

        this->close();

    } catch (QString &erro) {
        QMessageBox::information(this,"erro",erro);

    }
}

void TelaLocacao::on_pushButtonOrdenarPorModelo_clicked()
{
    try {
        listarVeiculosDisponiveis();

    } catch (QString &erro) {
        QMessageBox::information(this,"erro",erro);

    }

}

void TelaLocacao::on_pushButtoOrdenarPorMarca_clicked()
{
    try {
        listarVeiculosDisponiveis("Marca");

    } catch (QString &erro) {
        QMessageBox::information(this,"erro",erro);

    }
}

void TelaLocacao::on_pushButtonOrdenarPorValor_clicked()
{
    try {
        listarVeiculosDisponiveis("Valor");

    } catch (QString &erro) {
        QMessageBox::information(this,"erro",erro);

    }
}

void TelaLocacao::on_pushButtonOrdenarPorQuilometragem_clicked()
{
    try {
        listarVeiculosDisponiveis("Quilometragem");

    } catch (QString &erro) {
        QMessageBox::information(this,"erro",erro);

    }
}
