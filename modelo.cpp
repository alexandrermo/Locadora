#include "modelo.h"

namespace ar {



Modelo::Modelo(QString caminhoArquivoImagem,QString descricao,Id idMarca):
    caminhoArquivoImagem(caminhoArquivoImagem),
    descricao(descricao),
    id(),
    idMarca(idMarca)
{
}

QString Modelo::desmaterializar()const{
    QString saida="";
    saida+=caminhoArquivoImagem;
    saida+=";";
    saida+=descricao;
    saida+=";";
    saida+=QString::number(id.getNumero());
    saida+=";";
    saida+=QString::number(idMarca.getNumero());
    return saida;
}
void Modelo::materializar(QString str)
  {
   QStringList dados=str.split(";");
   caminhoArquivoImagem=dados[0];
   descricao=dados[1];
   id.materializar(dados[2]);
   idMarca.materializar(dados[3]);
}

}
