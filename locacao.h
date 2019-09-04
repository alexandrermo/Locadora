#ifndef LOCACAO_H
#define LOCACAO_H

#include<id.h>
#include<QString>
#include<data.h>

namespace ar
{

class Locacao
{
private:
    QString placaVeiculo;
    QString cpfCliente;
    Data dataLocacao;
    Data dataDevolucao;
    Id id;
    float valorTotal;
    bool situacao;

public:
    Locacao():placaVeiculo(""),cpfCliente(""),dataLocacao(),dataDevolucao(),id(),valorTotal(0),situacao(false){}
    Locacao(QString placaVeiculo,QString cpfCliente,Data dataLocacao,Data dataDevolucao,float valorTotal):
        placaVeiculo(placaVeiculo),cpfCliente(cpfCliente),dataLocacao(dataLocacao),dataDevolucao(dataDevolucao),id(),valorTotal(valorTotal),situacao(false){}

    QString getPlacaVeiculo()const{return placaVeiculo;}
    void setPlacaVeiculo(QString placaVeiculo){this->placaVeiculo=placaVeiculo;}

    QString getCpfCliente()const{return cpfCliente;}
    void setCpfCliente(QString cpfCliente){this->cpfCliente=cpfCliente;}

    Data getDataLocao()const{return dataLocacao;}
    void setDataLocao(Data dataLocacao){this->dataLocacao=dataLocacao;}

    Data getDataDevolucao()const{return dataDevolucao;}
    void setDataDevolucao(Data dataDevolucao){this->dataDevolucao=dataDevolucao;}

    Id getId()const{return id;}
    void setId(Id id){this->id=id;}
    void definirId(){this->id.definirId();}

    float getValorTotal()const{return valorTotal;}
    void setValorTotal(float valorTotal){this->valorTotal=valorTotal;}

    bool getSitucao()const{return situacao;}
    void setSitucao(bool situacao){this->situacao=situacao;}

    QString desmaterializar()const;
    void materializar(QString str);

    void calcularValorToal(float valor);

    bool operator<(Locacao objeto)const;
};

}


#endif // LOCACAO_H
