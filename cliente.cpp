#include "cliente.h"

namespace ar {
    Cliente::Cliente():
        nomeCompleto(""),
        telefone(),
        caminhoArquivoImagem(""),
        email(""),
        cpf(""),
        cnh("")
    {
    }

    Cliente::Cliente(QString nomeCompleto,Telefone telefone,QString email,QString arquivoImagem,QString cnh,QString cpf):
        nomeCompleto(nomeCompleto),
        telefone(telefone),
        caminhoArquivoImagem(arquivoImagem),
        email(email),
        cnh(cnh),
        cpf(cpf),
        tipoRelacionamento(tipoRelacionamento)
    {

    }
QString Cliente::desmaterializar()const{
    QString saida="";
    saida+=nomeCompleto;
    saida+=";";
    saida+=telefone.desmaterializar();
    saida+=";";
    saida+=email;
    saida+=";";
    saida+=caminhoArquivoImagem;
    saida+=";";
    saida+=cpf;
    saida+=";";
    saida+=cnh;
    saida+=";";
    saida+=getTipoRelacionamentoQString();
    return saida;
}
void Cliente::materializar(QString str)
  {
   QStringList dados=str.split(";");
   nomeCompleto=dados[0];
   telefone.setTelefone(dados[1].toInt(),dados[2].toInt(),dados[3].toInt());
   email=dados[4];
   caminhoArquivoImagem=dados[5];
   cpf=dados[6];
   cnh=dados[7];
   setTipoRelacionamento(dados[8]);
}

bool Cliente::operator <(Cliente objeto)const{
   return (this->nomeCompleto<objeto.nomeCompleto);
}

QString Cliente::getTipoRelacionamentoQString() const
{
    if  (tipoRelacionamento==TipoRelacionamento::Normal) return "Normal";
    if  (tipoRelacionamento==TipoRelacionamento::Premium) return "Premium";
    if  (tipoRelacionamento==TipoRelacionamento::VIP) return "VIP";
}

void Cliente::setTipoRelacionamento(QString tipoRelacionamento)
{
    if  (tipoRelacionamento=="Normal") this->tipoRelacionamento=TipoRelacionamento::Normal;
    if  (tipoRelacionamento=="Premium") this->tipoRelacionamento=TipoRelacionamento::Premium;
    if  (tipoRelacionamento=="VIP") this->tipoRelacionamento=TipoRelacionamento::VIP;
}


}
