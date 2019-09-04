#ifndef CLIENTE_H
#define CLIENTE_H
#include<itransformardados.h>
#include<telefone.h>
#include<QStringList>
#include<tiporelacionamento.h>
namespace ar {


class Cliente :public ITransformarDados
{
private:
    QString nomeCompleto;
    Telefone telefone;
    QString caminhoArquivoImagem;
    QString email;
    QString cnh;
    QString cpf;
    enum TipoRelacionamento tipoRelacionamento;
public:
    Cliente();
    Cliente(QString nomeCompleto,Telefone telefone,QString email,QString arquivoImagem,QString cnh,QString cpf);

    QString getNomeCompleto()const{return nomeCompleto;}
    void setNomeCompleto(QString nomeCompleto){this->nomeCompleto=nomeCompleto;}

    QString getCaminhoArquivoImagem(){return caminhoArquivoImagem;}
    void setCaminhoArquivoImagem(QString caminhoArquivoImagem)
    {this->caminhoArquivoImagem=caminhoArquivoImagem;}

    QString getTelefone(){return telefone.getTelefone();}
    void setTelefone(int DDI,int DDD,int numero)
    {telefone.setTelefone(DDI,DDD,numero);}
    QString getDDD(){return telefone.getDDD();}
    QString getDDI(){return telefone.getDDI();}
    QString getNumero(){return telefone.getNumero();}

    QString getEmail(){return email;}
    void setEmail(QString email){this->email=email;}

    QString desmaterializar()const;
    void materializar(QString str);

    QString getCnh(){return cnh;}
    void setCnh(QString cnh){this->cnh=cnh;}

    QString getCpf(){return cpf;}
    void setCpf(QString cpf){this->cpf=cpf;}

    bool operator <(Cliente objeto)const;

    QString getTipoRelacionamentoQString()const;
    void setTipoRelacionamento(QString tipoRelacionamento);
    enum TipoRelacionamento getTipoRelacionamentoEnum()const{return tipoRelacionamento;}
};
}
#endif // CLIENTE_H
