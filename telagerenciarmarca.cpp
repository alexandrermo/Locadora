#include "telagerenciarmarca.h"
#include "ui_telagerenciarmarca.h"
#include<marca.h>
#include<marcapersistencia.h>
#include<telaalterarmarca.h>
#include<qmessagebox.h>

telaGerenciarMarca::telaGerenciarMarca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaGerenciarMarca)
{
    ui->setupUi(this);
    listarTabela();
}

telaGerenciarMarca::~telaGerenciarMarca()
{
    delete ui;
}

void telaGerenciarMarca::on_pushButtonCadastrarMarca_clicked()
{
    telaCadastrarMarca telaCadastrarMarca;
    telaCadastrarMarca.setModal(true);
    telaCadastrarMarca.exec();

    listarTabela();
}

void telaGerenciarMarca::on_pushButtonAlterar_clicked()
{
    try {
        int linha=ui->tableWidgetListagem->currentRow();
        if  (linha==-1) throw  QString("Nenhuma linha selecionada.");

        QString id=ui->tableWidgetListagem->item(linha,1)->text();
        ar::Id idP= ar::Id(id.toInt());

        ar::MarcaPersistencia arquivoMarca("Marca.txt");
        ar::Marca objetoTemp=arquivoMarca.buscarPorId(idP);

        ar::Id id0;

        objetoTemp.setId(id0);

        arquivoMarca.incluir(objetoTemp,false);

        telaAlterarMarca telaAlterarMarca;
        telaAlterarMarca.setModal(true);
        telaAlterarMarca.exec();

        alterar(idP,linha);

    } catch (QString &erro)
    {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void telaGerenciarMarca::alterar(ar::Id id,int linha)
{
    ar::MarcaPersistencia agendaMarca("Marca.txt");
    std::list<ar::Marca>* lista=0;
    lista=agendaMarca.listagem();

    int tamanhoLista=lista->size();
    delete lista;

    if  (tamanhoLista==ui->tableWidgetListagem->rowCount()) return;

    agendaMarca.apagarPorId(id);

    ar::Id id0;

    ar::Marca objeto=agendaMarca.buscarPorId(id0);
    objeto.setId(id);
    agendaMarca.incluir(objeto,false);
    agendaMarca.apagarPorId(id0);

    ui->tableWidgetListagem->removeRow(linha);

    QIcon imagemIcon(objeto.getCaminhoArquivoImagem());

    QTableWidgetItem *itemId=new QTableWidgetItem(QString::number(objeto.getId().getNumero()));
    QTableWidgetItem *itemImagem=new QTableWidgetItem(imagemIcon,"");
    QTableWidgetItem *itemNomeCompleto=new QTableWidgetItem(objeto.getDescricao());


    ui->tableWidgetListagem->insertRow(linha);

    ui->tableWidgetListagem->setItem(linha,0,itemImagem);
    ui->tableWidgetListagem->setItem(linha,2,itemNomeCompleto);
    ui->tableWidgetListagem->setItem(linha,1,itemId);

    ui->tableWidgetListagem->resizeColumnsToContents();

}

void telaGerenciarMarca::on_pushButtonDeletar_clicked()
{
    try
    {
        int linha=ui->tableWidgetListagem->currentRow();

        if  (linha==-1) throw QString("Nenhuma linha selecionada.");

        QString id=ui->tableWidgetListagem->item(linha,1)->text();
        ar::Id idP= ar::Id(id.toInt());

        ar::MarcaPersistencia arquivoMarca("Marca.txt");

        arquivoMarca.apagarPorId(idP);

        ui->tableWidgetListagem->removeRow(linha);

    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO",erro);
    }
}

void telaGerenciarMarca::on_pushButtonVoltar_clicked()
{
    this->close();
}

void telaGerenciarMarca::listarTabela()
{
    ar::MarcaPersistencia agendaMarca("Marca.txt");

    std::list<ar::Marca>* listaMarcas=0;
    try {
        listaMarcas=agendaMarca.listagem();
    } catch (QString) {

    }
    ui->tableWidgetListagem->setRowCount(0);

    while(listaMarcas!=0 && !listaMarcas->empty())
    {
        ar::Marca objeto=listaMarcas->front();
        listaMarcas->pop_front();



        QTableWidgetItem *id=new QTableWidgetItem(QString::number(objeto.getId().getNumero()));
        QPixmap img(objeto.getCaminhoArquivoImagem());
        QTableWidgetItem *itemImagem = new QTableWidgetItem( QIcon( QPixmap(img) .scaled(144, 168)),"");
        QTableWidgetItem *itemNomeCompleto=new QTableWidgetItem(objeto.getDescricao());
        int linha=ui->tableWidgetListagem->rowCount();
        ui->tableWidgetListagem->insertRow(linha);


        ui->tableWidgetListagem->setItem(linha,0,itemImagem);
        ui->tableWidgetListagem->setItem(linha,1,id);
        ui->tableWidgetListagem->setItem(linha,2,itemNomeCompleto);


        ui->tableWidgetListagem->resizeColumnsToContents();

    }

    if  (listaMarcas!=0) delete listaMarcas;
}
