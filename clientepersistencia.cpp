#include "clientepersistencia.h"
namespace  ar
{
ClientePersistencia::ClientePersistencia(QString nomeDoArquivo):
    nomeDoArquivoNoDisco(nomeDoArquivo)
{
}

void ClientePersistencia::incluir(Cliente &objeto,bool novo)const
{

    std::ofstream arquivoAgenda;

    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str(),std::ios::out | std::ios::app);

    if  (!arquivoAgenda.is_open()) throw QString("Arquivo Agenda não foi aberto para inclusão de Cliente.");

    arquivoAgenda<<objeto.desmaterializar().toStdString()+"\n";
    arquivoAgenda.close();
}

std::list<Cliente>* ClientePersistencia::listagem()const
{
    try
    {
        std::ifstream arquivoAgenda;

        arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str());

        if(!arquivoAgenda.is_open()) throw QString("Arquivo de Agenda nao foi aberto.");

        std::list<Cliente>* lista=new std::list<Cliente>();
        std::string linha;

        getline(arquivoAgenda,linha);

        while(!arquivoAgenda.eof())
        {
            ar::Cliente objeto;
            QString str=QString::fromStdString(linha);
            objeto.materializar(str);
            lista->push_back(objeto);
            getline(arquivoAgenda,linha);
        }
        arquivoAgenda.close();
        lista->sort();
        return lista;

    } catch (QString &erro)
    {
        throw QString(erro);
    }
}

void ClientePersistencia::apagarPorCpf(QString cpf) const
{

    std::list<ar::Cliente>* lista=0;
    lista=listagem();

    std::ofstream arquivoAgenda;

    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str());

    if  (!arquivoAgenda.is_open())  throw QString("Arquivo de Agenda nao foi aberto - Metodo.");


    for(int pos=0;!lista->empty();pos++)
    {
        ar::Cliente objeto=lista->front();
        lista->pop_front();

        if  (objeto.getCpf()!=cpf) incluir(objeto,false);
    }

    arquivoAgenda.close();

    delete lista;
}

Cliente ClientePersistencia::buscarPorCpf(QString cpf)const
{
    std::list<ar::Cliente>* listaCliente=listagem();
    std::list<ar::Cliente>::iterator it;
    Cliente cliente;
    bool achou=false;

    for (it=listaCliente->begin();it!=listaCliente->end();it++)
    {
        QString cpfNaLista=(*it).getCpf();

        if  (cpf==cpfNaLista)
        {
            cliente=(*it);
            achou=true;
        }
    }

    if  (!achou) throw QString("Número de Cpf inválido em buscarPorCpf(ClientePesistencia).");
    delete listaCliente;
    return cliente;
}


}
