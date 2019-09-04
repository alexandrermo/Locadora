#include "marcapersistencia.h"
namespace ar {

MarcaPersistencia::MarcaPersistencia(QString nomeDoArquivo):
    nomeDoArquivoNoDisco(nomeDoArquivo)
{
}

void MarcaPersistencia::incluir(Marca &objeto,bool novo)const{
    std::ofstream arquivoAgenda;
    if(novo) objeto.definirId();
    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str(),std::ios::out | std::ios::app);

    if  (!arquivoAgenda.is_open()) throw QString("Arquivo Agenda não foi aberto para inclusão de Cliente.");

    arquivoAgenda<<objeto.desmaterializar().toStdString()+"\n";
    arquivoAgenda.close();
}

std::list<Marca>* MarcaPersistencia::listagem()const
{
    try
    {
        std::ifstream arquivoAgenda;

        arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str());

        if(!arquivoAgenda.is_open()) throw QString("Arquivo de Agenda nao foi aberto.");

        std::list<Marca>* lista=new std::list<Marca>();
        std::string linha;

        getline(arquivoAgenda,linha);

        while(!arquivoAgenda.eof())
        {
            ar::Marca objeto;
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
void MarcaPersistencia::apagarPorId(Id id) const
{

    std::list<ar::Marca>* lista=0;
    lista=listagem();

    std::ofstream arquivoAgenda;

    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str());

    if  (!arquivoAgenda.is_open())  throw QString("Arquivo de Agenda nao foi aberto - Metodo.");


    for(int pos=0;!lista->empty();pos++)
    {
        ar::Marca objeto=lista->front();
        lista->pop_front();

        if  (objeto.getId().getNumero()!=id.getNumero()) incluir(objeto,false);
    }

    arquivoAgenda.close();

    delete lista;
}
Marca MarcaPersistencia::buscarPorId(Id id)const
{
    std::list<ar::Marca>* listaCliente=listagem();
    std::list<ar::Marca>::iterator it;
    Marca cliente;
    bool achou=false;

    for (it=listaCliente->begin();it!=listaCliente->end();it++)
    {
        int idNaLista=(*it).getId().getNumero();

        if  (id.getNumero()==idNaLista)
        {
            cliente=(*it);
            achou=true;
        }
    }

    if  (!achou) throw QString("Número de Cpf inválido em buscarPorId(ClientePesistencia).");
    delete listaCliente;
    return cliente;
}


}
