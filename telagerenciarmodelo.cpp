#include "telagerenciarmodelo.h"
#include "ui_telagerenciarmodelo.h"
#include<telacadastrarmodelo.h>
#include<telaalterarmodelo.h>
telagerenciarmodelo::telagerenciarmodelo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telagerenciarmodelo)
{
    ui->setupUi(this);
    listarTabela();

}

QString telagerenciarmodelo::pesquisaMarcaPorId(int id){
    std::ifstream arquivoAgenda;
    arquivoAgenda.open("Marca.txt");
    std::string linha2;
    QString final="";
    getline(arquivoAgenda,linha2);

    if  (arquivoAgenda.is_open())
    {
        while(!arquivoAgenda.eof()){
            QString str = QString::fromStdString(linha2);
            QStringList dados=str.split(";");
            if(id==dados[2].toInt())  final=dados[1];
            getline(arquivoAgenda,linha2);
        }

        arquivoAgenda.close();
    }


    return final;
}

telagerenciarmodelo::~telagerenciarmodelo()
{
    delete ui;
}

void telagerenciarmodelo::on_pushButtonIrCadastro_clicked()
{
    telacadastrarModelo telacadastrarModelo;
    telacadastrarModelo.setModal(true);
    telacadastrarModelo.exec();

    listarTabela();
}



void telagerenciarmodelo::on_pushButtonAlterar_clicked()
{
    try {
        int linha=ui->tableWidgetListagem->currentRow();
        if  (linha==-1) throw  QString("Nenhuma linha selecionada.");

        QString id=ui->tableWidgetListagem->item(linha,1)->text();
        ar::Id idP= ar::Id(id.toInt());

        ar::ModeloPersistencia arquivoMarca("Modelo.txt");
        ar::Modelo objetoTemp=arquivoMarca.buscarPorId(idP);

        ar::Id id0;

        objetoTemp.setId(id0);

        arquivoMarca.incluir(objetoTemp,false);

        telaAlterarModelo telaAlterarModelo;
        telaAlterarModelo.setModal(true);
        telaAlterarModelo.exec();

        alterar(idP,linha);

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void telagerenciarmodelo::alterar(ar::Id id,int linha)
    {
    ar::ModeloPersistencia agendaMarca("Modelo.txt");
    std::list<ar::Modelo>* lista=0;
    lista=agendaMarca.listagem();

    int tamanhoLista=lista->size();
    delete lista;

    if  (tamanhoLista==ui->tableWidgetListagem->rowCount()) return;
    ar::Id id0;
    agendaMarca.apagarPorId(id);

    ar::Modelo objeto=agendaMarca.buscarPorId(id0);
    objeto.setId(id);
    agendaMarca.incluir(objeto,false);
    agendaMarca.apagarPorId(id0);

    ui->tableWidgetListagem->removeRow(linha);

    QIcon imagemIcon(objeto.getCaminhoArquivoImagem());

    QTableWidgetItem *itemId=new QTableWidgetItem(QString::number(objeto.getId().getNumero()));
    QTableWidgetItem *itemImagem=new QTableWidgetItem(imagemIcon,"");
    QTableWidgetItem *itemNomeCompleto=new QTableWidgetItem(objeto.getDescricao());
     QTableWidgetItem *itemMarca=new QTableWidgetItem(pesquisaMarcaPorId(objeto.getIdMarca().getNumero()));

    ui->tableWidgetListagem->insertRow(linha);

    ui->tableWidgetListagem->setItem(linha,0,itemImagem);
    ui->tableWidgetListagem->setItem(linha,2,itemNomeCompleto);
    ui->tableWidgetListagem->setItem(linha,1,itemId);
    ui->tableWidgetListagem->setItem(linha,3,itemMarca);
    ui->tableWidgetListagem->resizeColumnsToContents();

    }



void telagerenciarmodelo::on_pushButtonDeletar_clicked()
{
    try
    {
        int linha=ui->tableWidgetListagem->currentRow();

        if  (linha==-1) throw QString("Nenhuma linha selecionada.");

        QString id=ui->tableWidgetListagem->item(linha,1)->text();
        ar::Id idP= ar::Id(id.toInt());

        ar::ModeloPersistencia arquivoModelo("Modelo.txt");

        arquivoModelo.apagarPorId(idP);

        ui->tableWidgetListagem->removeRow(linha);

    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void telagerenciarmodelo::on_pushButtonVoltar_clicked()
{
    this->close();
}

void telagerenciarmodelo::listarTabela()
{
    ar::ModeloPersistencia agendaModelo("Modelo.txt");

    std::list<ar::Modelo>* listaModelos=0;
    try {
        listaModelos=agendaModelo.listagem();
    } catch (QString) {

    }
    ui->tableWidgetListagem->setRowCount(0);

    while(listaModelos!=0 && !listaModelos->empty())
    {
        ar::Modelo objeto=listaModelos->front();
        listaModelos->pop_front();

        QString marca=pesquisaMarcaPorId( objeto.getIdMarca().getNumero());


        QTableWidgetItem *id=new QTableWidgetItem(QString::number(objeto.getId().getNumero()));
        QPixmap img(objeto.getCaminhoArquivoImagem());
        QTableWidgetItem *itemImagem = new QTableWidgetItem( QIcon( QPixmap(img) .scaled(144, 168)),"");
        QTableWidgetItem *itemNomeCompleto=new QTableWidgetItem(objeto.getDescricao());
        QTableWidgetItem *itemMarca=new QTableWidgetItem(marca);

        int linha=ui->tableWidgetListagem->rowCount();
        ui->tableWidgetListagem->insertRow(linha);


        ui->tableWidgetListagem->setItem(linha,0,itemImagem);
        ui->tableWidgetListagem->setItem(linha,1,id);
        ui->tableWidgetListagem->setItem(linha,2,itemNomeCompleto);
        ui->tableWidgetListagem->setItem(linha,3,itemMarca);

        ui->tableWidgetListagem->resizeColumnsToContents();

    }

    if  (listaModelos!=0) delete listaModelos;
}
