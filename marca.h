#ifndef MARCA_H
#define MARCA_H

#include<QString>
#include<id.h>
#include<QStringList>

namespace ar {

class Marca
{
    QString caminhoArquivoImagem;
    QString descricao;
    Id id;
public:
    Marca():caminhoArquivoImagem(""),descricao(""),id(){}
    Marca(QString caminhoArquivoImagem,QString descricao);

    QString getCaminhoArquivoImagem(){return caminhoArquivoImagem;}
    void setCaminhoArquivoImagem(QString caminhoArquivoImagem)
    {this->caminhoArquivoImagem=caminhoArquivoImagem;}

    QString getDescricao(){return descricao;}
    void setDescricao(QString descricao){this->descricao=descricao;}

    Id getId()const{return id;}
    void setId(Id id){this->id=id;}
    void definirId(){id.definirId();}

    QString desmaterializar()const;
    void materializar(QString str);

    bool operator<(Marca objeto)const{return (this->descricao<objeto.descricao);}

};
}
#endif // MARCA_H
