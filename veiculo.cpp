#include "veiculo.h"

namespace ar {
Veiculo::Veiculo():
    placa(""),
    quilometragem(0),
    situacao(false),
    valorLocacao(0),
    caminhoArquivoImagem(""),
    idModelo()
{}

Veiculo::Veiculo(QString placa,int quilometragem,float valorLocacao,QString caminhoArquivoImagem,Id idModelo):
    placa(placa),
    quilometragem(quilometragem),
    situacao(false),
    valorLocacao(valorLocacao),
    caminhoArquivoImagem(caminhoArquivoImagem),
    idModelo(idModelo)
{

}

void Veiculo::materializar(QString str)
{
    QStringList dados=str.split(";");
    placa=dados[0];
    quilometragem=dados[1].toInt();
    if  (dados[2]=="true") situacao=true;
    else situacao=false;
    valorLocacao=dados[3].toFloat();
    caminhoArquivoImagem=dados[4];
    idModelo=ar::Id(dados[5].toInt());
}


QString Veiculo::desmaterializar()const{
    QString saida="";
    saida+=placa;
    saida+=";";
    saida+=QString::number(quilometragem);
    saida+=";";
    if  (situacao) saida+="true";
    else saida+="false";
    saida+=";";
    saida+=QString::number(valorLocacao);
    saida+=";";
    saida+=caminhoArquivoImagem;
    saida+=";";
    saida+=QString::number(idModelo.getNumero());
    return saida;
}

bool Veiculo::operator<(Veiculo objeto) const
{
    ModeloPersistencia arquivoModelo("Modelo.txt");

    Modelo modelo1=arquivoModelo.buscarPorId(this->idModelo);
    Modelo modelo2=arquivoModelo.buscarPorId(objeto.idModelo);

    return (modelo1.getDescricao()<modelo2.getDescricao());
}

}
