#include "locacao.h"

namespace  ar
{
QString Locacao::desmaterializar()const
{
    QString saida="";
    saida+=placaVeiculo;
    saida+=";";
    saida+=cpfCliente;
    saida+=";";
    saida+=dataLocacao.desmaterializar();
    saida+=";";
    saida+=dataDevolucao.desmaterializar();
    saida+=";";
    saida+=QString::number(id.getNumero());
    saida+=";";
    saida+=QString::number(valorTotal);
    saida+=";";
    if  (situacao) saida+="1";
    else saida+="0";

    return saida;
}
void Locacao::materializar(QString str)
{
    QStringList dados=str.split(";");
    placaVeiculo=dados[0];
    cpfCliente=dados[1];
    dataLocacao.setDia(dados[2].toInt());
    dataLocacao.setMes(dados[3].toInt());
    dataLocacao.setAno(dados[4].toInt());
    dataDevolucao.setDia(dados[5].toInt());
    dataDevolucao.setMes(dados[6].toInt());
    dataDevolucao.setAno(dados[7].toInt());
    id.materializar(dados[8]);
    valorTotal=dados[9].toFloat();
    if  (dados[10]=="1") situacao=true;
    else situacao=false;
}

void Locacao::calcularValorToal(float valor)
{
    int quantidadesDias=dataDevolucao-dataLocacao;

    valorTotal=valor*quantidadesDias;
}

bool Locacao::operator<(Locacao objeto)const
{
    return (this->dataLocacao)<(objeto.dataLocacao);
}

}
