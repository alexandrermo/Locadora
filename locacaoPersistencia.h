#ifndef LOCACAOPERSISTENCIA_H
#define LOCACAOPERSISTENCIA_H

#include<QString>
#include<locacao.h>
#include<list>
#include<veiculopersistencia.h>

namespace ar
{
class LocacaoPersistencia
{
private:
    QString caminhoArquivo;
public:
    LocacaoPersistencia(QString caminhoArquivo):caminhoArquivo(caminhoArquivo){}

    void locar(Locacao &objeto);
    void devolver(Locacao &objeto);
    void apagarPorId(Id id);
    std::list<Locacao>* listagem(QString cpfCliente,bool todos=false);
    Locacao buscarPorId(Id id);
    void incluirNovamente(Locacao &objeto);
};
}



#endif // LOCACAOPERSISTENCIA_H
