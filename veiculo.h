#ifndef VEICULO_H
#define VEICULO_H
#include<QString>
#include<itransformardados.h>
#include<QStringList>
#include<id.h>
#include<modelopersistencia.h>

namespace ar {
class Veiculo:public ITransformarDados
{
private:
    QString placa;
    int quilometragem;
    bool situacao;
    float valorLocacao;
    QString caminhoArquivoImagem;
    Id idModelo;

public:
    Veiculo();
    Veiculo(QString placa,int quilometragem, float valorLocacao, QString caminhoArquivoImagem,Id idModelo);

    QString getPlaca()const{return placa;}
    void setPlaca(QString placa){this->placa=placa;}

    int getQuilometragem()const{return quilometragem;}
    void setQuilometragem(int quilometragem){this->quilometragem=quilometragem;}

    bool getSituacao()const{return situacao;}
    void setSituacao(bool situacao){this->situacao=situacao;}

    float getValorLocacao()const{return valorLocacao;}
    void setValorLocacao(float valorLocacao){this->valorLocacao=valorLocacao;}

    QString getCaminhoArquivoImagem()const{return caminhoArquivoImagem;}
    void setCaminhoArquivoImagem(QString caminhoArquivoImagem){this->caminhoArquivoImagem=caminhoArquivoImagem;}

    Id getIdModelo()const{return idModelo;}
    void setIdModelo(Id idModelo){this->idModelo=idModelo;}

    void materializar(QString str);
    QString desmaterializar()const;

    bool operator<(Veiculo objeto)const;
};
}


#endif // VEICULO_H
