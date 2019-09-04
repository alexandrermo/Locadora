#include "veiculopersistencia.h"
namespace  ar
{
VeiculoPersistencia::VeiculoPersistencia(QString nomeDoArquivo):
    nomeDoArquivoNoDisco(nomeDoArquivo)
{
}

void VeiculoPersistencia::incluir(Veiculo &objeto,bool novo)const
{

    std::ofstream arquivoAgenda;

    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str(),std::ios::out | std::ios::app);

    if  (!arquivoAgenda.is_open()) throw QString("Arquivo Agenda não foi aberto para inclusão de Cliente.");

    arquivoAgenda<<objeto.desmaterializar().toStdString()+"\n";
    arquivoAgenda.close();
}

std::list<Veiculo>* VeiculoPersistencia::listagem()const
{
    try
    {
        std::ifstream arquivoAgenda;

        arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str());

        if(!arquivoAgenda.is_open()) throw QString("Arquivo de Agenda nao foi aberto.");

        std::list<Veiculo>* lista=new std::list<Veiculo>();
        std::string linha;

        getline(arquivoAgenda,linha);

        while(!arquivoAgenda.eof())
        {
            ar::Veiculo objeto;
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

void VeiculoPersistencia::apagarPorPlaca(QString placa) const
{

    std::list<ar::Veiculo>* lista=0;
    lista=listagem();

    std::ofstream arquivoAgenda;//PARA APAGAR ARQUIVO ANTIGO
    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str());
    if  (!arquivoAgenda.is_open())  throw QString("Arquivo de Veiculos nao foi aberto em apagarPorPlaca(VeiculoPersistencia)");
    arquivoAgenda.close();//PARA APAGAR ARQUIVO ANTIGO


    for(int pos=0;!lista->empty();pos++)
    {
        ar::Veiculo objeto=lista->front();
        lista->pop_front();

        if  (objeto.getPlaca()!=placa) incluir(objeto,false);
    }



    delete lista;
}

Veiculo VeiculoPersistencia::buscarPorPlaca(QString placa)const
{
    std::list<ar::Veiculo>* listaVeiculo=listagem();
    std::list<ar::Veiculo>::iterator it;
    Veiculo veiculo;
    bool achou=false;

    for (it=listaVeiculo->begin();it!=listaVeiculo->end();it++)
    {
        QString placaNaLista=(*it).getPlaca();

        if  (placa==placaNaLista)
        {
            veiculo=(*it);
            achou=true;
        }
    }

    if  (!achou) throw QString("Placa inválida em buscarPorPlaca(VeiculoPersistencia).");
    delete listaVeiculo;
    return veiculo;
}


}
