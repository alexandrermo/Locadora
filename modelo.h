#ifndef MODELO_H
#define MODELO_H
#include<id.h>
#include<itransformardados.h>
#include<QStringList>
namespace ar {



class Modelo
{
private:
    QString caminhoArquivoImagem;
    QString descricao;
    Id id;
    Id idMarca;
public:
    Modelo():caminhoArquivoImagem(""),descricao(""),id(),idMarca(){}
    Modelo(QString caminhoArquivoImagem,QString descricao,Id idMarca);

    QString getCaminhoArquivoImagem(){return caminhoArquivoImagem;}
    void setCaminhoArquivoImagem(QString caminhoArquivoImagem)
    {this->caminhoArquivoImagem=caminhoArquivoImagem;}

    QString getDescricao(){return descricao;}
    void setDescricao(QString descricao){this->descricao=descricao;}

    Id getId()const{return id;}
    void setId(Id id){this->id=id;}
    void definirId(){id.definirId();}

    Id getIdMarca()const{return idMarca;}
    void setIdMarca(Id id){this->idMarca=id;}
    void setNumeroIdMarca(int n){idMarca.setNumero(n);}

    QString desmaterializar()const;
    void materializar(QString str);

    bool operator<(Modelo objeto)const{return (this->descricao<objeto.descricao);}
};
}
#endif // MODELO_H
