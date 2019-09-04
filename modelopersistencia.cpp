#include "modelopersistencia.h"

namespace ar {

ModeloPersistencia::ModeloPersistencia(QString nomeDoArquivo):
    nomeDoArquivoNoDisco(nomeDoArquivo)
{
}

void ModeloPersistencia::incluir(Modelo &objeto,bool novo)const{
    std::ofstream arquivoAgenda;
    if(novo) objeto.definirId();
    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str(),std::ios::out | std::ios::app);

    if  (!arquivoAgenda.is_open()) throw QString("Arquivo Agenda não foi aberto para inclusão de Cliente.");

    arquivoAgenda<<objeto.desmaterializar().toStdString()+"\n";
    arquivoAgenda.close();
}

std::list<Modelo>* ModeloPersistencia::listagem()const
{
    try
    {
        std::ifstream arquivoAgenda;

        arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str());

        if(!arquivoAgenda.is_open()) throw QString("Arquivo de Agenda nao foi aberto.");

        std::list<Modelo>* lista=new std::list<Modelo>();
        std::string linha;

        getline(arquivoAgenda,linha);

        while(!arquivoAgenda.eof())
        {
            ar::Modelo objeto;
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
void ModeloPersistencia::apagarPorId(Id id) const
{

    std::list<ar::Modelo>* lista=0;
    lista=listagem();

    std::ofstream arquivoAgenda;

    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str());

    if  (!arquivoAgenda.is_open())  throw QString("Arquivo de Agenda nao foi aberto - Metodo.");


    for(int pos=0;!lista->empty();pos++)
    {
        ar::Modelo objeto=lista->front();
        lista->pop_front();

        if  (objeto.getId().getNumero()!=id.getNumero()) incluir(objeto,false);
    }

    arquivoAgenda.close();

    delete lista;
}
Modelo ModeloPersistencia::buscarPorId(Id id)const
{
    std::list<ar::Modelo>* listaModelo=0;
    try {
    listaModelo=listagem();

    } catch (...) {

    }

    std::list<ar::Modelo>::iterator it;
    Modelo cliente;
    bool achou=false;

    for (it=listaModelo->begin();listaModelo!=0 && it!=listaModelo->end();it++)
    {
        int idNaLista=(*it).getId().getNumero();

        if  (id.getNumero()==idNaLista)
        {
            cliente=(*it);
            achou=true;
        }
    }

    if  (!achou) throw QString("Número de ID inválido em buscarPorId(ModeloPesistencia).");
    if  (listaModelo!=0) delete listaModelo;
    return cliente;
}

Modelo ModeloPersistencia::buscarPorDescricao(QString descricao)const
{
    std::list<ar::Modelo>* listaModelo=0;
    try {
    listaModelo=listagem();

    } catch (...) {

    }
    std::list<ar::Modelo>::iterator it;
    Modelo modelo;
    bool achou=false;

    for (it=listaModelo->begin();listaModelo!=0 && it!=listaModelo->end();it++)
    {
        QString descricaoNaLista=(*it).getDescricao();

        if  (descricao==descricaoNaLista)
        {
            modelo=(*it);
            achou=true;
        }
    }

    if  (!achou) throw QString("Nome de modelo inválido em buscarPorDescricao(ModeloPesistencia).");
    if  (listaModelo!=0) delete listaModelo;
    return modelo;
}

}
