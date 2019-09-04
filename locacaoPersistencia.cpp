#include "locacaoPersistencia.h"

namespace ar
{

void LocacaoPersistencia::locar(Locacao &objeto)
{
    std::ofstream arquivoAgenda;

    objeto.definirId();
    objeto.setSitucao(true);

    ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");
    ar::Veiculo veiculo=arquivoVeiculo.buscarPorPlaca(objeto.getPlacaVeiculo());


    arquivoAgenda.open(caminhoArquivo.toStdString().c_str(),std::ios::out | std::ios::app);

    if  (!arquivoAgenda.is_open()) throw QString("Arquivo Locacao não foi aberto em locar(locacaoPersistencia.");

    veiculo.setSituacao(true);
    arquivoVeiculo.apagarPorPlaca(veiculo.getPlaca());
    arquivoVeiculo.incluir(veiculo);

    arquivoAgenda<<objeto.desmaterializar().toStdString()+"\n";
    arquivoAgenda.close();
}

void LocacaoPersistencia::devolver(Locacao &objeto)
{
    ar::VeiculoPersistencia arquivoVeiculo("Veiculo.txt");
    ar::Veiculo veiculo=arquivoVeiculo.buscarPorPlaca(objeto.getPlacaVeiculo());

    veiculo.setSituacao(false);
    arquivoVeiculo.apagarPorPlaca(veiculo.getPlaca());
    arquivoVeiculo.incluir(veiculo);

    apagarPorId(objeto.getId());
    objeto.setSitucao(false);
    incluirNovamente(objeto);
}

void LocacaoPersistencia::incluirNovamente(Locacao &objeto)
{
    std::ofstream arquivoAgenda;

    arquivoAgenda.open(caminhoArquivo.toStdString().c_str(),std::ios::out | std::ios::app);

    if  (!arquivoAgenda.is_open()) throw QString("Arquivo Locacao não foi aberto em incluirNovamente(locacaoPersistencia.");

    arquivoAgenda<<objeto.desmaterializar().toStdString()+"\n";
    arquivoAgenda.close();
}

void LocacaoPersistencia::apagarPorId(Id id)
{
    std::list<ar::Locacao>* lista=0;
    lista=listagem("",true);

    std::ofstream arquivoAgenda;

    arquivoAgenda.open(caminhoArquivo.toStdString().c_str());
    if  (!arquivoAgenda.is_open())  throw QString("Arquivo de Locacao nao foi aberto em apagarPorId(LocacaoPersistencia).");
    arquivoAgenda.close();


    for(int pos=0;!lista->empty();pos++)
    {
        ar::Locacao objeto=lista->front();
        lista->pop_front();

        if  (objeto.getId().getNumero()!=id.getNumero()) incluirNovamente(objeto);
    }



    delete lista;
}

std::list<Locacao>* LocacaoPersistencia::listagem(QString cpfCliente,bool todos)
{
    try
    {
        std::ifstream arquivoAgenda;

        arquivoAgenda.open(caminhoArquivo.toStdString().c_str());

        if(!arquivoAgenda.is_open()) throw QString("Arquivo de Locacao nao foi aberto em listagem(LocacaoPersistencia).");

        std::list<Locacao>* lista=new std::list<Locacao>;
        std::string linha;

        getline(arquivoAgenda,linha);

        while(!arquivoAgenda.eof())
        {
            ar::Locacao objeto;
            QString str=QString::fromStdString(linha);
            objeto.materializar(str);
            if  (todos) lista->push_back(objeto);
            else if(cpfCliente==objeto.getCpfCliente()) lista->push_back(objeto);
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

Locacao LocacaoPersistencia::buscarPorId(Id id)
{
    std::list<ar::Locacao>* listaLocacao=listagem("",true);
    std::list<ar::Locacao>::iterator it;
    Locacao locacao;
    bool achou=false;

    for (it=listaLocacao->begin();it!=listaLocacao->end();it++)
    {
        int idNaLista=(*it).getId().getNumero();

        if  (id.getNumero()==idNaLista)
        {
            locacao=(*it);
            achou=true;
        }
    }

    if  (!achou) throw QString("Número de ID inválido em buscarPorId(LocacaoPersistencia).");
    delete listaLocacao;
    return locacao;
}

}
