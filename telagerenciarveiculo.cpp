#include "telagerenciarveiculo.h"
#include "ui_telagerenciarveiculo.h"

TelaGerenciarVeiculo::TelaGerenciarVeiculo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaGerenciarVeiculo)
{
    ui->setupUi(this);
    try {
        listarTabela();
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

TelaGerenciarVeiculo::~TelaGerenciarVeiculo()
{
    delete ui;
}

void TelaGerenciarVeiculo::listarTabela()
{
    ar::VeiculoPersistencia agendaVeiculo("Veiculo.txt");
    ar::ModeloPersistencia arquivoModelo("Modelo.txt");
    ar::MarcaPersistencia arquivoMarca("Marca.txt");

    std::list<ar::Veiculo>* listaVeiculos=0;
    try {
        listaVeiculos=agendaVeiculo.listagem();
    } catch (QString) {

    }
    ui->tableWidgetListagem->setRowCount(0);

    while(listaVeiculos!=0 && !listaVeiculos->empty())
    {
        ar::Veiculo objeto=listaVeiculos->front();
        listaVeiculos->pop_front();

        QIcon imagemIcon(objeto.getCaminhoArquivoImagem());

        ar::Modelo modelo=arquivoModelo.buscarPorId(objeto.getIdModelo());
        ar::Marca marca=arquivoMarca.buscarPorId(modelo.getIdMarca());

        QTableWidgetItem *itemPlaca=new QTableWidgetItem(objeto.getPlaca());
        QTableWidgetItem *itemImagem=new QTableWidgetItem(imagemIcon,"");
        QTableWidgetItem *itemValorLocacao=new QTableWidgetItem(QString::number(objeto.getValorLocacao()));
        QTableWidgetItem *itemQuilometragem=new QTableWidgetItem(QString::number(objeto.getQuilometragem()));
        QTableWidgetItem *itemSituacao=new QTableWidgetItem;
        if  (objeto.getSituacao()) itemSituacao->setText("ALUGADO.");
        else itemSituacao->setText("DISPONÍVEL");
        QTableWidgetItem *itemModelo=new QTableWidgetItem(modelo.getDescricao());
        QTableWidgetItem *itemMarca=new QTableWidgetItem(marca.getDescricao());


        int linha=ui->tableWidgetListagem->rowCount();
        ui->tableWidgetListagem->insertRow(linha);


        ui->tableWidgetListagem->setItem(linha,0,itemImagem);
        ui->tableWidgetListagem->setItem(linha,1,itemPlaca);
        ui->tableWidgetListagem->setItem(linha,2,itemModelo);
        ui->tableWidgetListagem->setItem(linha,3,itemMarca);
        ui->tableWidgetListagem->setItem(linha,4,itemSituacao);
        ui->tableWidgetListagem->setItem(linha,5,itemValorLocacao);
        ui->tableWidgetListagem->setItem(linha,6,itemQuilometragem);

        ui->tableWidgetListagem->resizeColumnsToContents();

    }

    if  (listaVeiculos!=0) delete listaVeiculos;
}

void TelaGerenciarVeiculo::on_pushButtonCadastrarNovoVeculo_clicked()
{
    TelaCadastrarVeiculo telaCadastrarVeiculo;
    telaCadastrarVeiculo.setModal(true);
    telaCadastrarVeiculo.exec();

    listarTabela();
}

void TelaGerenciarVeiculo::on_pushButtonApagar_clicked()
{
    try
    {
        int linha=ui->tableWidgetListagem->currentRow();

        if  (linha==-1) throw QString("Nenhuma linha selecionada.");

        QString placa=ui->tableWidgetListagem->item(linha,1)->text();

        ar::VeiculoPersistencia arquivoCliente("Veiculo.txt");

        arquivoCliente.apagarPorPlaca(placa);

        ui->tableWidgetListagem->removeRow(linha);

    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void TelaGerenciarVeiculo::on_pushButtonAlterar_clicked()
{
    try {
        int linha=ui->tableWidgetListagem->currentRow();
        if  (linha==-1) throw  QString("Nenhuma linha selecionada.");

        QString placa=ui->tableWidgetListagem->item(linha,1)->text();


        ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");
        ar::Veiculo objetoTemp=arquivoVeiculo.buscarPorPlaca(placa);

        objetoTemp.setPlaca("0");

        arquivoVeiculo.incluir(objetoTemp,false);

        std::ofstream arquivoTemp;
        arquivoTemp.open("Temporario.txt");
        if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em Botão Alterar em TelaGerenciarVeiculo.");
        arquivoTemp<<placa.toStdString();
        arquivoTemp.close();

        TelaAlterarVeiculo TelaAlterarVeiculo;
        TelaAlterarVeiculo.setModal(true);
        TelaAlterarVeiculo.exec();

        alterar(placa,linha);

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void TelaGerenciarVeiculo::alterar(QString placa,int linha)
{
    ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");
    ar::ModeloPersistencia arquivoModelo("Modelo.txt");
    ar::MarcaPersistencia arquivoMarca("Marca.txt");

    std::list<ar::Veiculo>* lista=0;
    lista=arquivoVeiculo.listagem();

    int tamanhoLista=lista->size();
    delete lista;

    if  (tamanhoLista==ui->tableWidgetListagem->rowCount()) return;

    arquivoVeiculo.apagarPorPlaca(placa);

    std::string placaString="";
    std::ifstream arquivoTemp;
    arquivoTemp.open("Temporario.txt");
    if  (!arquivoTemp.is_open()) throw QString("Arquivo Temporário não aberto em alterar em TelaGerenciarVeiculo.");
    getline(arquivoTemp,placaString);
    arquivoTemp.close();

    ar::Veiculo objeto=arquivoVeiculo.buscarPorPlaca("0");
    objeto.setPlaca(QString::fromStdString(placaString));
    arquivoVeiculo.incluir(objeto,false);
    arquivoVeiculo.apagarPorPlaca("0");

    ui->tableWidgetListagem->removeRow(linha);

    ar::Modelo modelo=arquivoModelo.buscarPorId(objeto.getIdModelo());
    ar::Marca marca=arquivoMarca.buscarPorId(modelo.getIdMarca());

    QIcon imagemIcon(objeto.getCaminhoArquivoImagem());

    QTableWidgetItem *itemPlaca=new QTableWidgetItem(objeto.getPlaca());
    QTableWidgetItem *itemImagem=new QTableWidgetItem(imagemIcon,"");
    QTableWidgetItem *itemValorLocacao=new QTableWidgetItem(QString::number(objeto.getValorLocacao()));
    QTableWidgetItem *itemQuilometragem=new QTableWidgetItem(QString::number(objeto.getQuilometragem()));
    QTableWidgetItem *itemSituacao=new QTableWidgetItem;
    if  (objeto.getSituacao()) itemSituacao->setText("ALUGADO.");
    else itemSituacao->setText("DISPONÍVEL");
    QTableWidgetItem *itemModelo=new QTableWidgetItem(modelo.getDescricao());
    QTableWidgetItem *itemMarca=new QTableWidgetItem(marca.getDescricao());

    ui->tableWidgetListagem->insertRow(linha);

    ui->tableWidgetListagem->setItem(linha,0,itemImagem);
    ui->tableWidgetListagem->setItem(linha,1,itemPlaca);
    ui->tableWidgetListagem->setItem(linha,2,itemModelo);
    ui->tableWidgetListagem->setItem(linha,3,itemMarca);
    ui->tableWidgetListagem->setItem(linha,4,itemSituacao);
    ui->tableWidgetListagem->setItem(linha,5,itemValorLocacao);
    ui->tableWidgetListagem->setItem(linha,6,itemQuilometragem);

    ui->tableWidgetListagem->resizeColumnsToContents();

}

void TelaGerenciarVeiculo::on_pushButtonVoltar_clicked()
{
    this->close();
}
