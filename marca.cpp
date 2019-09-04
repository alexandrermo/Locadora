#include "marca.h"

namespace ar {



Marca::Marca(QString caminhoArquivoImagem,QString descricao):
    caminhoArquivoImagem(caminhoArquivoImagem),
    descricao(descricao)
{
}

QString Marca::desmaterializar()const{
    QString saida="";
    saida+=caminhoArquivoImagem;
    saida+=";";
    saida+=descricao;
    saida+=";";
    saida+=QString::number(id.getNumero());
    return saida;
}
void Marca::materializar(QString str)
  {
   QStringList dados=str.split(";");
   caminhoArquivoImagem=dados[0];
   descricao=dados[1];
   id.materializar(dados[2]);
}

}
